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

    void OnDropEvent(class QDropEvent* event);
    void OnOpenAbout();

    void OnUpdateEngine();

    void OnVolumeSliderMoved(int);

private:

    virtual void dragEnterEvent(QDragEnterEvent* event);
    virtual void dragMoveEvent(QDragMoveEvent* event);
    virtual void dragLeaveEvent(QDragLeaveEvent* event);
    virtual void dropEvent(QDropEvent *event);

private:

    QTabWidget* m_pCentralTabWidget;
    QMenuBar*   m_pMenuBar;

    QTimer* m_pTimerUpdateEngine;
};


#endif
