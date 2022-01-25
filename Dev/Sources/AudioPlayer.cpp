////////////////////////////////////////////////////////////////
// Header

#include "Gugu/Common.h"
#include "AudioPlayer.h"

////////////////////////////////////////////////////////////////
// Includes

#include "Gugu/Engine.h"
#include "Gugu/Window/Window.h"
#include "Gugu/Resources/ManagerResources.h"
#include "Gugu/Resources/Music.h"
#include "Gugu/Audio/ManagerAudio.h"
#include "Gugu/Audio/MusicInstance.h"
#include "Gugu/System/SystemUtility.h"
#include "Gugu/Math/Random.h"
#include "Gugu/Version.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_stdlib.h>

////////////////////////////////////////////////////////////////
// File Implementation

namespace gugu {
    
AudioPlayer::AudioPlayer()
    : m_resetPanels(false)
    , m_isRunningPlaylist(false)
    , m_currentAlbumIndex((size_t)-1)
{
}

AudioPlayer::~AudioPlayer()
{
}

void AudioPlayer::AppStart()
{
    RegisterHandlerEvents(GetGameWindow());

    gugu::GetAudio()->SetVolumeMaster(0.1f);

    // Additional ImGui Setup.
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    //io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;   // TODO: Does not seem supported by the SFML backend.
    io.ConfigWindowsResizeFromEdges = true;
}

void AudioPlayer::AppStop()
{
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
        ImGui::Text("using gugu::Engine %s", GUGU_VERSION);

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
        ImGui::DockBuilderDockWindow("Playlist", dock_main_id);
        ImGui::DockBuilderFinish(dockspace_id);
    }

    ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);

    //----------------------------------------------

    // Update Playlist
    if (ImGui::Begin("Playlist", false))
    {
        ImGui::InputText("Directory", &m_lastDirectory);

        if (ImGui::Button("Parse and Run Playlist"))
        {
            ParseAndRunPlaylist();
        }

        ImGuiTableFlags flags = ImGuiTableFlags_Borders | ImGuiTableFlags_Resizable | ImGuiTableFlags_ScrollY /* | ImGuiTableFlags_NoPadInnerX */;
        if (ImGui::BeginTable("Albums Table", 2, flags))
        {
            ImGui::TableSetupColumn("#", ImGuiTableColumnFlags_WidthFixed, 30.f);
            ImGui::TableSetupColumn("album", ImGuiTableColumnFlags_WidthStretch, 0.f);
            ImGui::TableSetupScrollFreeze(0, 1);
            ImGui::TableHeadersRow();

            // TODO: handle sort (ImGuiTableSortSpecs).
            // TODO: handle big list (ImGuiListClipper).
            for (size_t rowIndex = 0; rowIndex < m_albumDirectories.size(); ++rowIndex)
            {
                ImGui::PushID(rowIndex);

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
                sprintf(label, "%04d", rowIndex);
                ImGui::Text(label);

                {
                    ImGui::TableSetColumnIndex(columnIndex++);

                    sf::String stringConversion = m_albumDirectories[rowIndex].directoryName;
                    std::basic_string<sf::Uint8> stringAsUtf8 = stringConversion.toUtf8();
                    ImGui::Text("%s", stringAsUtf8.c_str());
                }

                ImGui::PopID();
            }

            ImGui::EndTable();
        }
    }
    ImGui::End();

    // Update Play Controls panel.
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
                RunNextPlaylistAlbum();

                musicInstance = gugu::GetAudio()->GetCurrentMusicInstance(0);
            }

            // Default Track/Album controls.
            if (musicInstance)
            {
                DeltaTime offset = musicInstance->GetPlayOffset();
                DeltaTime duration = musicInstance->GetDuration();

                {
                    sf::String stringConversion = m_albumDirectories[m_currentAlbumIndex].directoryName;
                    std::basic_string<sf::Uint8> stringAsUtf8 = stringConversion.toUtf8();
                    ImGui::Text("Album : %s", stringAsUtf8.c_str());
                }

                {
                    sf::String stringConversion = musicInstance->GetMusic()->GetFileInfoRef().GetName();
                    std::basic_string<sf::Uint8> stringAsUtf8 = stringConversion.toUtf8();
                    ImGui::Text("Track : %s", stringAsUtf8.c_str());
                }

                ImGui::Text(StringFormat("Time : {0} / {1}s", (int)musicInstance->GetPlayOffset().s(), (int)musicInstance->GetDuration().s()).c_str());

                int seekPosition = offset.ms();
                if (ImGui::SliderInt("Seek", &seekPosition, 0, duration.ms(), ""))
                {
                    musicInstance->SetPlayOffset(DeltaTime(seekPosition));
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
            }

            ImGui::SameLine();
            if (ImGui::Button("Stop Playlist"))
            {
                gugu::GetAudio()->StopMusic(0.f);

                m_isRunningPlaylist = false;
                m_albumDirectories.clear();
                m_nextAlbumIndexes.clear();
                m_currentAlbumIndex = (size_t)-1;
            }
        }
    }
    ImGui::End();

    //----------------------------------------------

    // End Dockspace Window.
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
    m_currentAlbumIndex = (size_t)-1;

    // Discover album directories.
    sf::String stringConversion = sf::String::fromUtf8(m_lastDirectory.begin(), m_lastDirectory.end());
    std::string parseDirectory = stringConversion.toAnsiString();

    std::vector<FileInfo> files;
    GetFilesList(parseDirectory, files, true);

    std::set<std::string> validExtensions{ "wav", "ogg", "flac" };
    std::map<std::string, size_t> existingDirectories;
    for (size_t i = 0; i < files.size(); ++i)
    {
        if (validExtensions.find(files[i].GetExtension()) != validExtensions.end())
        {
            std::string filePathName = files[i].GetPathName();
            std::string directoryPath = files[i].GetPath();
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

        // Load the new album.
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
