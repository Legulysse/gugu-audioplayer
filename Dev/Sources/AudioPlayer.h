#pragma once

////////////////////////////////////////////////////////////////
// Includes

#include "Gugu/Core/Application.h"
#include "Gugu/Events/EventListener.h"
#include "Gugu/System/FileInfo.h"

#include <vector>

////////////////////////////////////////////////////////////////
// File Declarations

namespace gugu {

class AudioPlayer : public gugu::Application, public gugu::EventListener
{
public:

    AudioPlayer();
    virtual ~AudioPlayer();

    virtual void AppStart() override;
    virtual void AppStop() override;

    virtual void AppUpdate(const gugu::DeltaTime& dt) override;

    virtual bool OnSFEvent(const sf::Event& event) override;

private:

    void LoadUserSettings();
    void SaveUserSettings();

    void UpdateLibrary();
    void UpdateHistory();
    void UpdateCurrentAlbum();
    void UpdatePlayControls();

    void ParseAndRunPlaylist();
    void RunNextPlaylistAlbum();
    void PlayCurrentAlbum();
    void PlayNextAlbumTrack();
    void PlayAlbumTrack(size_t trackIndex);

private:

    bool m_resetPanels;

    std::string m_libraryDirectory;
    bool m_isRunningPlaylist;
    bool m_loopTrack;
    bool m_loopAlbum;

    struct AlbumDirectory
    {
        std::string directoryName_utf8;
        std::vector<std::string> fileNames_utf8;
        std::vector<gugu::FileInfo> files;
    };
    std::vector<AlbumDirectory> m_albumDirectories;
    std::vector<size_t> m_nextAlbumIndexes;
    std::vector<size_t> m_lastAlbumIndexes;
    size_t m_currentAlbumIndex;
    size_t m_currentTrackIndex;
};

}   //namespace gugu
