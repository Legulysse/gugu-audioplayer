#pragma once

////////////////////////////////////////////////////////////////
// Includes

#include "Gugu/Core/Application.h"
#include "Gugu/Events/EventListener.h"

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

private:

    bool m_resetPanels;

    std::string m_libraryDirectory;
    bool m_isRunningPlaylist;
    bool m_loopAlbum;

    struct AlbumDirectory
    {
        std::string directoryName;
        std::basic_string<gugu::uint8> directoryName_utf8;

        std::vector<std::string> files;
        std::vector<std::basic_string<gugu::uint8>> fileNames_utf8;
    };
    std::vector<AlbumDirectory> m_albumDirectories;
    std::vector<size_t> m_nextAlbumIndexes;
    std::vector<size_t> m_lastAlbumIndexes;
    size_t m_currentAlbumIndex;
};

}   //namespace gugu
