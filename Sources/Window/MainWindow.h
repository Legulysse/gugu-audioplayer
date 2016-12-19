#ifndef GUGU_MAINWINDOW_H
#define GUGU_MAINWINDOW_H


#include <QtWidgets/QMainWindow>


class QTabWidget;
class QMenuBar;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

            MainWindow  (QWidget *parent = 0);
    virtual ~MainWindow ();

    void RefreshMenu        ();

private slots:

    void OnOpenAbout();

private:

    QTabWidget* m_pCentralTabWidget;
    QMenuBar*   m_pMenuBar;
};


#endif
