#include <QtWidgets/QApplication>
#include "Window/MainWindow.h"


int main(int argc, char *argv[])
{
    int iExecReturn = 0;

    //Init UI
    QApplication a(argc, argv);
    {
        MainWindow* w = new MainWindow;
        w->show();

        //Start loop
        iExecReturn = a.exec(); //MainWindow will delete itself once closed
    }

    //Exit
    return iExecReturn;
}
