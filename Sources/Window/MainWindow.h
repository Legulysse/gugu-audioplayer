#pragma once

#include <QtWidgets/QMainWindow>

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

    void OnControlPlay();
    void OnControlPause();
    void OnControlStop();
    void OnVolumeSliderMoved(int);
    void OnSeekSliderMoved(int);

private:

    virtual void dragEnterEvent(QDragEnterEvent* event);
    virtual void dragMoveEvent(QDragMoveEvent* event);
    virtual void dragLeaveEvent(QDragLeaveEvent* event);
    virtual void dropEvent(QDropEvent *event);

private:

    class QTabWidget* m_pCentralTabWidget;
    class QMenuBar* m_pMenuBar;

    class QListWidget* m_pListPlay;
    class QLabel* m_pCurrentTrackInfos;
    class QSlider* m_pSliderSeek;

    class QTimer* m_pTimerUpdateEngine;
};
