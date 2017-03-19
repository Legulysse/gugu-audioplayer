#include <QtWidgets/QApplication>
#include "Window/MainWindow.h"

#include "Gugu/Engine.h"


int main(int argc, char *argv[])
{
    int iExecReturn = 0;

    //Init engine
    gugu::EngineInit oConfig;
    oConfig.NameApplication     = "";
    oConfig.PathAssets          = "Assets";
    oConfig.PathScreenshots     = "Screenshots";
    oConfig.GameWindowType		= gugu::EGameWindow::None;
    oConfig.UseAssetsFullPaths  = true;

    gugu::GetEngine()->Init(oConfig);

    //Init UI
    QApplication a(argc, argv);
    {
        MainWindow* w = new MainWindow;
        w->show();

        //Start loop
        iExecReturn = a.exec(); //MainWindow will delete itself once closed
    }

    gugu::GetEngine()->Release();

    //Exit
    return iExecReturn;
}
