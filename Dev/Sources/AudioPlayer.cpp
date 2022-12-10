////////////////////////////////////////////////////////////////
// Header

#include "Gugu/Common.h"
#include "AudioPlayer.h"

////////////////////////////////////////////////////////////////
// Includes

#include "Gugu/EngineVersion.h"
#include "Gugu/Engine.h"
#include "Gugu/Window/Window.h"
#include "Gugu/Resources/ManagerResources.h"
#include "Gugu/Resources/Music.h"
#include "Gugu/Audio/ManagerAudio.h"
#include "Gugu/Audio/MusicInstance.h"
#include "Gugu/System/SystemUtility.h"
#include "Gugu/Math/Random.h"
#include "Gugu/External/PugiXmlUtility.h"
#include "Gugu/External/ImGuiUtility.h"

#include <SFML/System/String.hpp>

////////////////////////////////////////////////////////////////
// File Implementation

namespace gugu {
    
AudioPlayer::AudioPlayer()
    : m_resetPanels(false)
    , m_isRunningPlaylist(false)
    , m_loopAlbum(false)
    , m_currentAlbumIndex((size_t)-1)
{
}

AudioPlayer::~AudioPlayer()
{
}

void AudioPlayer::AppStart()
{
    RegisterEventHandler(GetGameWindow());

    gugu::GetAudio()->SetVolumeMaster(0.1f);

    // Additional ImGui Setup.
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    //io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;   // TODO: Does not seem supported by the SFML backend.
    io.ConfigWindowsResizeFromEdges = true;

    LoadUserSettings();
}

void AudioPlayer::AppStop()
{
}

void AudioPlayer::LoadUserSettings()
{
    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file("User/Settings.xml");
    if (!result)
        return;

    pugi::xml_node nodeRoot = document.child("Settings");
    if (!nodeRoot)
        return;

    pugi::xml_node nodeLibrary = nodeRoot.child("Library");
    if (!nodeLibrary)
        return;

    m_libraryDirectory = nodeLibrary.attribute("path").value();
}

void AudioPlayer::SaveUserSettings()
{
    //TODO
}

void AudioPlayer::AppUpdate(const DeltaTime& dt)
{
    // Main menu bar.
    bool openModalAbout = false;
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Application"))
        {
            if (ImGui::MenuItem("About"))
            {
                openModalAbout = true;
            }

            if (ImGui::MenuItem("Reset UI"))
            {
                m_resetPanels = true;
            }

            if (ImGui::MenuItem("Quit", "Alt+F4"))
            {
                GetEngine()->StopMainLoop();
            }

            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }

    if (openModalAbout)
    {
        ImGui::OpenPopup("About");
    }

    bool unused_open = true;
    if (ImGui::BeginPopupModal("About", &unused_open, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings))
    {
        ImGui::Text("gugu::AudioPlayer %s", "0.2");
        ImGui::Spacing();
        ImGui::Text("author: Legulysse");
        ImGui::Spacing();
        ImGui::Text("using gugu::Engine %s", GUGU_ENGINE_VERSION);

        ImGui::Spacing();
        if (ImGui::Button("Close"))
            ImGui::CloseCurrentPopup();

        ImGui::EndPopup();
    }

    // Docking panels ids.
    const char* dockspaceWindowName = "AudioPlayerDockSpace Window";
    const ImGuiID dockspace_id = ImGui::GetID("AudioPlayerDockSpace");

    // Begin Dockspace Window.
    ImGuiWindowFlags window_flags = /*ImGuiWindowFlags_MenuBar |*/ ImGuiWindowFlags_NoDocking;
    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin(dockspaceWindowName, false, window_flags);
    ImGui::PopStyleVar(3);

    // Editor panels preset.
    if (ImGui::DockBuilderGetNode(dockspace_id) == NULL || m_resetPanels)
    {
        m_resetPanels = false;

        ImGui::DockBuilderRemoveNode(dockspace_id); // Clear out existing layout
        ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_DockSpace); // Add empty node
        ImGui::DockBuilderSetNodeSize(dockspace_id, viewport->Size);

        ImGuiID dock_main_id = dockspace_id; // This variable will track the document node, however we are not using it here as we aren't docking anything into it.
        ImGuiID dock_id_left = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Left, 0.20f, NULL, &dock_main_id);
        ImGuiID dock_id_right = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Right, 0.20f, NULL, &dock_main_id);
        //ImGuiID dock_id_up = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Up, 0.20f, NULL, &dock_main_id);
        ImGuiID dock_id_down = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Down, 0.20f, NULL, &dock_main_id);

        ImGui::DockBuilderDockWindow("Play Controls", dock_id_down);
        ImGui::DockBuilderDockWindow("History", dock_id_right);
        ImGui::DockBuilderDockWindow("Library", dock_main_id);
        ImGui::DockBuilderDockWindow("Album", dock_main_id);
        ImGui::DockBuilderFinish(dockspace_id);
    }

    ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);

    //----------------------------------------------

    UpdateLibrary();
    UpdateHistory();
    UpdateCurrentAlbum();
    UpdatePlayControls();

    // End Dockspace Window.
    ImGui::End();
}

void AudioPlayer::UpdateLibrary()
{
    if (ImGui::Begin("Library", false))
    {
        ImGui::InputText("Directory", &m_libraryDirectory);

        if (ImGui::Button("Parse and Run Playlist"))
        {
            ParseAndRunPlaylist();
        }

        ImGui::SameLine();
        if (ImGui::Button("Stop Playlist"))
        {
            gugu::GetAudio()->StopMusic(0.f);

            m_isRunningPlaylist = false;
            m_albumDirectories.clear();
            m_nextAlbumIndexes.clear();
            m_lastAlbumIndexes.clear();
            m_currentAlbumIndex = (size_t)-1;
        }

        ImGui::SameLine();
        if (ImGui::Button("Open in Explorer"))
        {
            OpenFileExplorer(m_libraryDirectory);
        }

        ImGuiTableFlags flags = ImGuiTableFlags_Borders | ImGuiTableFlags_Resizable | ImGuiTableFlags_ScrollY /* | ImGuiTableFlags_NoPadInnerX */;
        if (ImGui::BeginTable("Albums Table", 2, flags))
        {
            ImGui::TableSetupColumn("#", ImGuiTableColumnFlags_WidthFixed, 30.f);
            ImGui::TableSetupColumn("album", ImGuiTableColumnFlags_WidthStretch, 0.f);
            ImGui::TableSetupScrollFreeze(0, 1);
            ImGui::TableHeadersRow();

            // TODO: handle sort (ImGuiTableSortSpecs).
            ImGuiListClipper clipper;
            clipper.Begin((int)m_albumDirectories.size());
            while (clipper.Step())
            {
                for (int rowIndex = clipper.DisplayStart; rowIndex < clipper.DisplayEnd; rowIndex++)
                {
                    ImGui::PushID(rowIndex);

                    float row_min_height = 0.f;
                    ImGui::TableNextRow(ImGuiTableRowFlags_None, row_min_height);

                    if (rowIndex == clipper.DisplayStart)
                    {
                        // Setup ItemWidth once.
                        int headerIndex = 0;

                        ImGui::TableSetColumnIndex(headerIndex++);
                        ImGui::PushItemWidth(-1);
                        ImGui::TableSetColumnIndex(headerIndex++);
                        ImGui::PushItemWidth(-1);
                    }

                    int columnIndex = 0;
                    ImGui::TableSetColumnIndex(columnIndex++);

                    char label[32];
                    sprintf(label, "%04d", rowIndex);
                    ImGui::Text(label);

                    ImGui::TableSetColumnIndex(columnIndex++);
                    ImGui::Text("%s", m_albumDirectories[rowIndex].directoryName_utf8.c_str());

                    ImGui::PopID();
                }
            }

            ImGui::EndTable();
        }
    }
    ImGui::End();
}

void AudioPlayer::UpdateHistory()
{
    if (ImGui::Begin("History", false))
    {
        ImGuiTableFlags flags = ImGuiTableFlags_Borders | ImGuiTableFlags_Resizable | ImGuiTableFlags_ScrollY /* | ImGuiTableFlags_NoPadInnerX */;
        if (ImGui::BeginTable("Albums Table", 2, flags))
        {
            ImGui::TableSetupColumn("#", ImGuiTableColumnFlags_WidthFixed, 30.f);
            ImGui::TableSetupColumn("album", ImGuiTableColumnFlags_WidthStretch, 0.f);
            ImGui::TableSetupScrollFreeze(0, 1);
            ImGui::TableHeadersRow();

            ImGuiListClipper clipper;
            clipper.Begin((int)m_lastAlbumIndexes.size());
            while (clipper.Step())
            {
                for (int rowIndex = clipper.DisplayStart; rowIndex < clipper.DisplayEnd; rowIndex++)
                {
                    ImGui::PushID(rowIndex);

                    float row_min_height = 0.f;
                    ImGui::TableNextRow(ImGuiTableRowFlags_None, row_min_height);

                    if (rowIndex == clipper.DisplayStart)
                    {
                        // Setup ItemWidth once.
                        int headerIndex = 0;

                        ImGui::TableSetColumnIndex(headerIndex++);
                        ImGui::PushItemWidth(-1);
                        ImGui::TableSetColumnIndex(headerIndex++);
                        ImGui::PushItemWidth(-1);
                    }

                    int columnIndex = 0;
                    ImGui::TableSetColumnIndex(columnIndex++);

                    char label[32];
                    sprintf(label, "%04d", rowIndex);
                    ImGui::Text(label);

                    ImGui::TableSetColumnIndex(columnIndex++);
                    ImGui::Text("%s", m_albumDirectories[m_lastAlbumIndexes[rowIndex]].directoryName_utf8.c_str());

                    ImGui::PopID();
                }
            }

            ImGui::EndTable();
        }
    }
    ImGui::End();
}

void AudioPlayer::UpdateCurrentAlbum()
{
    if (ImGui::Begin("Album", false))
    {
        if (m_currentAlbumIndex != (size_t)-1)
        {
            ImGui::Text("Album : %s", m_albumDirectories[m_currentAlbumIndex].directoryName_utf8.c_str());
            ImGui::Spacing();

            ImGuiTableFlags flags = ImGuiTableFlags_Borders | ImGuiTableFlags_Resizable | ImGuiTableFlags_ScrollY /* | ImGuiTableFlags_NoPadInnerX */;
            if (ImGui::BeginTable("Album Tracks Table", 2, flags))
            {
                ImGui::TableSetupColumn("#", ImGuiTableColumnFlags_WidthFixed, 30.f);
                ImGui::TableSetupColumn("track", ImGuiTableColumnFlags_WidthStretch, 0.f);
                ImGui::TableSetupScrollFreeze(0, 1);
                ImGui::TableHeadersRow();

                for (size_t rowIndex = 0; rowIndex < m_albumDirectories[m_currentAlbumIndex].files.size(); ++rowIndex)
                {
                    ImGui::PushID((int)rowIndex);

                    float row_min_height = 0.f;
                    ImGui::TableNextRow(ImGuiTableRowFlags_None, row_min_height);

                    if (rowIndex == 0)
                    {
                        // Setup ItemWidth once.
                        int headerIndex = 0;

                        ImGui::TableSetColumnIndex(headerIndex++);
                        ImGui::PushItemWidth(-1);
                        ImGui::TableSetColumnIndex(headerIndex++);
                        ImGui::PushItemWidth(-1);
                    }

                    int columnIndex = 0;
                    ImGui::TableSetColumnIndex(columnIndex++);

                    char label[32];
                    sprintf(label, "%04zu", rowIndex);
                    ImGui::Text(label);

                    ImGui::TableSetColumnIndex(columnIndex++);
                    ImGui::Text("%s", m_albumDirectories[m_currentAlbumIndex].fileNames_utf8[rowIndex].c_str());

                    ImGui::PopID();
                }

                ImGui::EndTable();
            }
        }
    }
    ImGui::End();
}

void AudioPlayer::UpdatePlayControls()
{
    if (ImGui::Begin("Play Controls", false))
    {
        float volume = GetAudio()->GetVolumeMaster();
        if (ImGui::SliderFloat("Volume", &volume, 0.f, 2.f))
        {
            GetAudio()->SetVolumeMaster(volume);
        }

        ImGui::Spacing();

        if (m_isRunningPlaylist)
        {
            // Handle album transition when running album ends.
            gugu::MusicInstance* musicInstance = gugu::GetAudio()->GetCurrentMusicInstance(0);
            if (!musicInstance)
            {
                if (m_loopAlbum)
                {
                    PlayCurrentAlbum();
                }
                else
                {
                    RunNextPlaylistAlbum();
                }

                musicInstance = gugu::GetAudio()->GetCurrentMusicInstance(0);
            }

            // Default Track/Album controls.
            if (musicInstance)
            {
                sf::Time offset = musicInstance->GetPlayOffset();
                sf::Time duration = musicInstance->GetDuration();

                ImGui::Text("Album : %s", m_albumDirectories[m_currentAlbumIndex].directoryName_utf8.c_str());

                //TODO: find a way to retrieve playlist index, to use the filenames cache.
                ImGui::Text("Track : %s", sf::String(musicInstance->GetMusic()->GetFileInfo().GetPrettyName()).toUtf8().c_str());

                ImGui::Text(StringFormat("Time : {0} / {1}s", (int)offset.asSeconds(), (int)duration.asSeconds()).c_str());

                int seekPosition = offset.asMilliseconds();
                if (ImGui::SliderInt("Seek", &seekPosition, 0, duration.asMilliseconds(), ""))
                {
                    musicInstance->SetPlayOffset(sf::milliseconds(seekPosition));
                }

                ImGui::Spacing();

                if (musicInstance->IsPaused())
                {
                    if (ImGui::Button("Resume Track"))
                    {
                        musicInstance->Play();
                    }
                }
                else
                {
                    if (ImGui::Button("Pause Track"))
                    {
                        musicInstance->Pause();
                    }
                }

                ImGui::SameLine();
                if (ImGui::Button("Next Track"))
                {
                    musicInstance->Stop();
                }

                ImGui::SameLine();
                if (ImGui::Button("Next Album"))
                {
                    gugu::GetAudio()->StopMusic(0.f);

                    RunNextPlaylistAlbum();
                }

                ImGui::SameLine();
                ImGui::Checkbox("Loop Album", &m_loopAlbum);
            }
        }
    }
    ImGui::End();
}

bool AudioPlayer::OnSFEvent(const sf::Event& event)
{
    if (!EventListener::OnSFEvent(event))
        return false;

    return true;
}

void AudioPlayer::ParseAndRunPlaylist()
{
    gugu::GetAudio()->StopMusic(0.f);

    m_isRunningPlaylist = false;
    m_albumDirectories.clear();
    m_nextAlbumIndexes.clear();
    m_lastAlbumIndexes.clear();
    m_currentAlbumIndex = (size_t)-1;

    // Discover album directories.
    sf::String stringConversion = sf::String::fromUtf8(m_libraryDirectory.begin(), m_libraryDirectory.end());
    std::string parseDirectory = stringConversion.toAnsiString();

    std::vector<FileInfo> files;
    GetFiles(parseDirectory, files, true);

    std::set<std::string> validExtensions{ "wav", "ogg", "flac", "mp3" };
    std::map<std::string, size_t> existingDirectories;
    for (size_t i = 0; i < files.size(); ++i)
    {
        if (validExtensions.find(files[i].GetExtension()) != validExtensions.end())
        {
            std::string filePathName = files[i].GetFilePath();
            std::string directoryPath = files[i].GetDirectoryPath();
            size_t directoryIndex = (size_t)-1;

            auto it = existingDirectories.find(directoryPath);
            if (it == existingDirectories.end())
            {
                directoryIndex = m_albumDirectories.size();
                existingDirectories.insert(it, std::make_pair(directoryPath, directoryIndex));

                AlbumDirectory newAlbumDirectory;
                newAlbumDirectory.directoryName = directoryPath;

                m_albumDirectories.push_back(newAlbumDirectory);
                m_nextAlbumIndexes.push_back(directoryIndex);
            }
            else
            {
                directoryIndex = it->second;
            }

            m_albumDirectories[directoryIndex].files.push_back(filePathName);
        }
    }

    // Cache some data
    for (size_t i = 0; i < m_albumDirectories.size(); ++i)
    {
        m_albumDirectories[i].directoryName_utf8 = sf::String(m_albumDirectories[i].directoryName).toUtf8();

        m_albumDirectories[i].fileNames_utf8.resize(m_albumDirectories[i].files.size());

        for (size_t ii = 0; ii < m_albumDirectories[i].files.size(); ++ii)
        {
            std::string fileName;
            NamePartFromPath(m_albumDirectories[i].files[ii], fileName);

            m_albumDirectories[i].fileNames_utf8[ii] = sf::String(fileName).toUtf8();
        }
    }

    RunNextPlaylistAlbum();
}

void AudioPlayer::RunNextPlaylistAlbum()
{
    if (!m_albumDirectories.empty())
    {
        // Select the next album index.
        if (m_nextAlbumIndexes.empty())
        {
            for (size_t index = 0; index < m_albumDirectories.size(); ++index)
            {
                m_nextAlbumIndexes.push_back(index);
            }
        }

        size_t randomIndex = GetRandom(m_nextAlbumIndexes.size());
        size_t nextIndex = m_nextAlbumIndexes[randomIndex];

        bool isReset = m_nextAlbumIndexes.size() == m_albumDirectories.size();
        if (isReset && m_nextAlbumIndexes.size() > 1 && nextIndex == m_currentAlbumIndex)
        {
            // If we are starting a new loop of a list of albums, ensure we dont replay the very last album played.
            randomIndex = randomIndex + 1 < m_nextAlbumIndexes.size() ? randomIndex + 1 : 0;
            nextIndex = m_nextAlbumIndexes[randomIndex];
        }

        m_currentAlbumIndex = nextIndex;
        StdVectorRemoveAt(m_nextAlbumIndexes, randomIndex);

        if (m_lastAlbumIndexes.empty() || m_lastAlbumIndexes.back() != nextIndex)
        {
            m_lastAlbumIndexes.push_back(nextIndex);
        }

        // Load the new album.
        PlayCurrentAlbum();
    }
}

void AudioPlayer::PlayCurrentAlbum()
{
    if (!m_albumDirectories.empty() && m_currentAlbumIndex >= 0 && m_currentAlbumIndex < m_albumDirectories.size())
    {
        std::vector<gugu::MusicParameters> vecPlaylist;
        for (size_t i = 0; i < m_albumDirectories[m_currentAlbumIndex].files.size(); ++i)
        {
            std::string resourceID = m_albumDirectories[m_currentAlbumIndex].files[i];
            gugu::FileInfo fileInfo(resourceID);

            //TODO: test already existing ressource.
            //TODO: handle files outside of ressources ? Wait for similar update in Editor to see how to do this.
            gugu::GetResources()->RegisterResourceInfo(resourceID, fileInfo);
            gugu::Music* music = gugu::GetResources()->GetMusic(resourceID);

            gugu::MusicParameters params;
            params.musicID = resourceID;
            params.fadeIn = 0.0f;
            params.fadeOut = 0.0f;
            vecPlaylist.push_back(params);
        }

        if (!vecPlaylist.empty())
        {
            m_isRunningPlaylist = true;
            gugu::GetAudio()->PlayMusicList(vecPlaylist, false, 0);
        }
    }
}

}   //namespace gugu
