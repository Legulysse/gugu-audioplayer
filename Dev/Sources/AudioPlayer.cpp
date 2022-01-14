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

#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_stdlib.h>

////////////////////////////////////////////////////////////////
// File Implementation

namespace gugu {
    
AudioPlayer::AudioPlayer()
    : m_resetPanels(false)
    , m_isTestPlaying(false)
    , m_currentAlbumDirectory((size_t)-1)
{
}

AudioPlayer::~AudioPlayer()
{
}

void AudioPlayer::AppStart()
{
    RegisterHandlerEvents(GetGameWindow());

    gugu::GetAudio()->SetVolumeMaster(0.3f);

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
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Application"))
        {
            if (ImGui::MenuItem("Quit", "Alt+F4"))
            {
                GetEngine()->StopMainLoop();
            }

            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
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
    bool resetDocuments = false;
    if (ImGui::DockBuilderGetNode(dockspace_id) == NULL || m_resetPanels)
    {
        resetDocuments = true;
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
        ImGui::DockBuilderFinish(dockspace_id);
    }

    ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);

    //----------------------------------------------

    // Update Play Controls panel.
    if (ImGui::Begin("Play Controls", false))
    {
        ImGui::InputText("Directory", &m_lastDirectory);

        float volume = GetAudio()->GetVolumeMaster();
        if (ImGui::SliderFloat("Volume", &volume, 0.f, 2.f))
        {
            GetAudio()->SetVolumeMaster(volume);
        }

        ImGui::Spacing();

        if (!m_isTestPlaying)
        {
            if (ImGui::Button("Start Playlist"))
            {
                m_isTestPlaying = false;
                m_albumDirectories.clear();
                m_currentAlbumDirectory = (size_t)-1;

                // Discover album directories.
                std::vector<FileInfo> files;
                GetFilesList(m_lastDirectory, files, true);

                std::map<std::string, size_t> existingDirectories;
                for (size_t i = 0; i < files.size(); ++i)
                {
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
                    }
                    else
                    {
                        directoryIndex = it->second;
                    }

                    m_albumDirectories[directoryIndex].files.push_back(files[i].GetPathName());
                }

                if (!m_albumDirectories.empty())
                {
                    m_currentAlbumDirectory = GetRandom(m_albumDirectories.size());

                    std::vector<gugu::MusicParameters> vecPlaylist;
                    for (size_t i = 0; i < m_albumDirectories[m_currentAlbumDirectory].files.size(); ++i)
                    {
                        std::string resourceID = m_albumDirectories[m_currentAlbumDirectory].files[i];
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

                    m_isTestPlaying = true;
                    gugu::GetAudio()->PlayMusicList(vecPlaylist);
                }
            }
        }
        else
        {
            gugu::MusicInstance* musicInstance = gugu::GetAudio()->GetCurrentMusicInstance(0);
            if (musicInstance)
            {
                DeltaTime offset = musicInstance->GetPlayOffset();
                DeltaTime duration = musicInstance->GetDuration();

                ImGui::Text("Album : %s", m_albumDirectories[m_currentAlbumDirectory].directoryName.c_str());
                ImGui::Text("Track : %s", musicInstance->GetMusic()->GetFileInfoRef().GetName().c_str());
                ImGui::Text(StringFormat("Time : {0} / {1}s", (int)musicInstance->GetPlayOffset().s(), (int)musicInstance->GetDuration().s()).c_str());

                int seekPosition = offset.ms();
                if (ImGui::SliderInt("Seek", &seekPosition, 0, duration.ms()))
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
            }

            ImGui::SameLine();
            if (ImGui::Button("Stop Playlist"))
            {
                gugu::GetAudio()->StopMusic(0.f);

                m_isTestPlaying = false;
                m_albumDirectories.clear();
                m_currentAlbumDirectory = (size_t)-1;
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

}   //namespace gugu
