#pragma once

////////////////////////////////////////////////////////////////
// Includes

#include "Gugu/Core/Application.h"
#include "Gugu/Events/EventListener.h"

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
};

}   //namespace gugu
