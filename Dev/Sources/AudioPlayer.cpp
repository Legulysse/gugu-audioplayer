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

#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_stdlib.h>

////////////////////////////////////////////////////////////////
// File Implementation

namespace gugu {
    
AudioPlayer::AudioPlayer()
    : m_resetPanels(false)
    , m_isTestPlaying(false)
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
                m_isTestPlaying = true;

                std::vector<FileInfo> files;
                GetFilesList(m_lastDirectory, files, true);

                std::vector<gugu::MusicParameters> vecPlaylist;
                for (size_t i = 0; i < files.size(); ++i)
                {
                    std::string resourceID = files[i].GetPathName();
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

                gugu::GetAudio()->PlayMusicList(vecPlaylist);

                //gugu::MusicInstance* pMusic = gugu::GetAudio()->GetCurrentMusicInstance(0);
                //if (pMusic)
                //{
                //    pMusic->Play();
                //}
            }
        }
        else
        {
            gugu::MusicInstance* pMusicInstance = gugu::GetAudio()->GetCurrentMusicInstance(0);
            if (pMusicInstance)
            {
                DeltaTime offset = pMusicInstance->GetPlayOffset();
                DeltaTime duration = pMusicInstance->GetDuration();

                ImGui::Text("Track : %s", pMusicInstance->GetMusic()->GetFileInfoRef().GetName().c_str());
                ImGui::Text(StringFormat("Time : {0} / {1}", (int)pMusicInstance->GetPlayOffset().s(), (int)pMusicInstance->GetDuration().s()).c_str());

                int seekPosition = offset.ms();
                if (ImGui::SliderInt("Seek", &seekPosition, 0, duration.ms()))
                {
                    pMusicInstance->SetPlayOffset(DeltaTime(seekPosition));
                }
            }

            ImGui::Spacing();
            if (ImGui::Button("Next Track"))
            {
                gugu::MusicInstance* pMusic = gugu::GetAudio()->GetCurrentMusicInstance(0);
                if (pMusic)
                {
                    pMusic->Stop();
                }
            }

            ImGui::SameLine();
            if (ImGui::Button("Stop Playlist"))
            {
                m_isTestPlaying = false;

                gugu::GetAudio()->StopMusic(0.f);
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
