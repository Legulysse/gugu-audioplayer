////////////////////////////////////////////////////////////////
// Includes

#include "Gugu/Common.h"
#include "AudioPlayer.h"

#include "Gugu/Engine.h"

using namespace gugu;

////////////////////////////////////////////////////////////////
// File Implementation

int main(int argc, char* argv[])
{
#if defined(GUGU_ENV_VISUAL )

    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

#endif

    //----------------------------------------------

    setlocale(LC_ALL, ".UTF8");

    //----------------------------------------------
    // Init engine

    EngineConfig config;
    config.applicationName = "Gugu::AudioPlayer";
    config.pathAssets = "Assets";
    config.applicationIcon = "music_beam.png";
    config.defaultFont = "Spaceranger.ttf";
    config.debugFont = "Roboto-Regular.ttf";
    config.gameWindow = EGameWindow::Sfml;
    config.windowWidth = 800;
    config.windowHeight = 600;
    config.backgroundColor = sf::Color(128, 128, 128, 255);
    config.showImGui = true;
    config.maximizeWindow = true;
    
    GetEngine()->Init(config);

    //----------------------------------------------

    GetEngine()->RunApplication(new AudioPlayer);

    return 0;
}
