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

    bool m_resetPanels;

    std::string m_lastDirectory;
    bool m_isTestPlaying;

    struct AlbumDirectory
    {
        std::string directoryName;
        std::vector<std::string> files;
    };
    std::vector<AlbumDirectory> m_albumDirectories;
    size_t m_currentAlbumDirectory;
};

}   //namespace gugu
