#include "Window/MainWindow.h"

#include "Dialog/DialogAbout.h"

#include <QtCore/QTimer>
#include <QtCore/QMimeData>
#include <QtGui/QtEvents>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QAction>
#include <QtWidgets/QSlider>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QListWidget>
#include <QtDebug>

#include "Gugu/Engine.h"
#include "Gugu/Manager/ManagerAudio.h"
#include "Gugu/Manager/ManagerResources.h"
#include "Gugu/Resources/ResourceInfo.h"


#define PLAYER_UI_VOLUMEUNIT 100


MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent)
{
    setAttribute(Qt::WA_DeleteOnClose);

    // Main UI
    setWindowTitle("Gugu::AudioPlayer");    //TODO: Ability to get the engine config title, to apply here and in the About dialog
    setWindowIcon(QIcon("Icons/application2.png"));
    //setWindowIcon(QIcon("Icons/smiley_cool.png"));

    resize(400, 300);
    setMinimumSize(QSize(200, 100));

    m_pMenuBar = new QMenuBar(this);
    m_pMenuBar->setGeometry(QRect(0, 0, 1024, 20));
    setMenuBar(m_pMenuBar);

    QStatusBar* pStatusBar = new QStatusBar(this);
    pStatusBar->setObjectName(QString::fromUtf8("statusBar"));
    setStatusBar(pStatusBar);

    // Main Widget
    QWidget* pCentralWidget = new QWidget();
    setCentralWidget(pCentralWidget);

    // Main Layout
    QVBoxLayout* pCentralLayout = new QVBoxLayout();
    pCentralLayout->setSpacing(6);
    pCentralLayout->setContentsMargins(1, 1, 1, 1);
    pCentralWidget->setLayout(pCentralLayout);

    // Actual Central Widget (to fill the space)
    //m_pCentralTabWidget = new QTabWidget();
    //m_pCentralTabWidget->setTabShape(QTabWidget::Rounded);
    //pCentralLayout->addWidget(m_pCentralTabWidget);

    // Play List
    {
        m_pListPlay = new QListWidget();
        pCentralLayout->addWidget(m_pListPlay);
    }

    // Seek Control
    {
        m_pSliderSeek = new QSlider();
        m_pSliderSeek->setToolTip("Seek");
        m_pSliderSeek->setObjectName(QString::fromUtf8("horizontalSlider"));
        m_pSliderSeek->setOrientation(Qt::Horizontal);
        m_pSliderSeek->setRange(0, 1);
        m_pSliderSeek->setSliderPosition(0);
        m_pSliderSeek->setSingleStep(1);
        m_pSliderSeek->setMinimumWidth(20);
        //m_pSliderSeek->setMaximumWidth(200);
        m_pSliderSeek->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
        connect(m_pSliderSeek, SIGNAL(valueChanged(int)), this, SLOT(OnSeekSliderMoved(int)));

        pCentralLayout->addWidget(m_pSliderSeek);
    }

    // Play Control Layout
    {
        QHBoxLayout* pPlayControlLayout = new QHBoxLayout();
        pCentralLayout->addLayout(pPlayControlLayout);

        // Play Control
        {
            QToolButton* pButton = new QToolButton();
            pButton->setToolTip("Play");
            pButton->setIcon(QIcon("Icons/control_play.png"));
            pButton->setAutoRaise(true);
            pPlayControlLayout->addWidget(pButton);
            connect(pButton, SIGNAL(clicked()), this, SLOT(OnControlPlay()));
        }

        // Pause Control
        {
            QToolButton* pButton = new QToolButton();
            pButton->setToolTip("Pause");
            pButton->setIcon(QIcon("Icons/control_pause.png"));
            pButton->setAutoRaise(true);
            pPlayControlLayout->addWidget(pButton);
            connect(pButton, SIGNAL(clicked()), this, SLOT(OnControlPause()));
        }

        // Stop Control
        {
            QToolButton* pButton = new QToolButton();
            pButton->setToolTip("Stop");
            pButton->setIcon(QIcon("Icons/control_stop.png"));
            pButton->setAutoRaise(true);
            pPlayControlLayout->addWidget(pButton);
            connect(pButton, SIGNAL(clicked()), this, SLOT(OnControlStop()));
        }

        // Volume Control
        {
            QSlider* pSliderVolume = new QSlider();
            pSliderVolume->setToolTip("Volume");
            pSliderVolume->setObjectName(QString::fromUtf8("horizontalSlider"));
            pSliderVolume->setOrientation(Qt::Horizontal);
            pSliderVolume->setRange(0, PLAYER_UI_VOLUMEUNIT * 2);
            pSliderVolume->setSliderPosition(PLAYER_UI_VOLUMEUNIT);
            pSliderVolume->setSingleStep(1);
            pSliderVolume->setMinimumWidth(20);
            pSliderVolume->setMaximumWidth(100);
            pSliderVolume->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
            pPlayControlLayout->addWidget(pSliderVolume);
            connect(pSliderVolume, SIGNAL(valueChanged(int)), this, SLOT(OnVolumeSliderMoved(int)));
        }
    }

    // Handle Files drop
    //QObject::connect(this, SIGNAL(dropEvent()), this, SLOT(OnDropEvent()));
    setAcceptDrops(true);

    // Finalize
    RefreshMenu();

    //Engine Update
    m_pTimerUpdateEngine = new QTimer(this);
    m_pTimerUpdateEngine->setSingleShot(false);
    connect(m_pTimerUpdateEngine, SIGNAL(timeout()), this, SLOT(OnUpdateEngine()));
    m_pTimerUpdateEngine->start(20);
}

MainWindow::~MainWindow()
{
    //Stop Engine Update
    m_pTimerUpdateEngine->stop();

    qDebug("Release MainWindow");
}

void MainWindow::dragEnterEvent(QDragEnterEvent* event)
{
    event->acceptProposedAction();
}

void MainWindow::dragMoveEvent(QDragMoveEvent* event)
{
    event->acceptProposedAction();
}

void MainWindow::dragLeaveEvent(QDragLeaveEvent* event)
{
    event->accept();
}

void MainWindow::dropEvent(QDropEvent* event)
{
    OnDropEvent(event);
}

void MainWindow::OnDropEvent(class QDropEvent* event)
{
    const QMimeData* mimeData = event->mimeData();
    if (mimeData->hasUrls())
    {
        QList<QUrl> urlList = mimeData->urls();

        // Update UI
        m_pListPlay->clear();

        std::vector<gugu::MusicParameters> vecPlaylist;
        for (int i = 0; i < urlList.size() && i < 32; ++i)
        {
            QString strPath = urlList.at(i).toLocalFile();

            // Originally used pathList[i].toStdString(), but since it uses toUtf8, it breaks some of my paths
            // toLatin1() gives similar result to toLocal8Bit()
            //TODO: investigate the need to update this >> https://bugreports.qt.io/browse/QTBUG-39086
            std::string resourceID = strPath.toLocal8Bit().toStdString();
            gugu::FileInfo fileInfo(resourceID);

            gugu::GetResources()->AddResourceInfo(resourceID, fileInfo);

            gugu::MusicParameters params;
            params.m_strFile = resourceID;
            params.m_fFadeIn = 0.0f;
            params.m_fFadeOut = 0.0f;
            vecPlaylist.push_back(params);

            // Update UI
            m_pListPlay->addItem(QString::fromStdString(resourceID));
        }

        gugu::GetAudio()->PlayMusicList(vecPlaylist);
    }
}

void MainWindow::RefreshMenu()
{
    m_pMenuBar->clear();

    //Menu Editor
    QMenu* pMenuEditor = new QMenu(m_pMenuBar);
    pMenuEditor->setTitle("Player");
    m_pMenuBar->addMenu(pMenuEditor);

    QAction* pActionClose = new QAction(pMenuEditor);
    pActionClose->setText("Close");
    pMenuEditor->addAction(pActionClose);

    QObject::connect(pActionClose, SIGNAL(triggered()), this, SLOT(close()));

    //Menu About
    QMenu* pMenuAbout = new QMenu(m_pMenuBar);
    pMenuAbout->setTitle("?");
    m_pMenuBar->addMenu(pMenuAbout);

    QAction* pActionAbout = new QAction(pMenuAbout);
    pActionAbout->setText("About...");
    pMenuAbout->addAction(pActionAbout);

    QObject::connect(pActionAbout, SIGNAL(triggered()), this, SLOT(OnOpenAbout()));
}

void MainWindow::OnOpenAbout()
{
    DialogAbout oDialog;
    oDialog.exec();
}

void MainWindow::OnUpdateEngine()
{
    gugu::GetEngine()->Step(gugu::DeltaTime(m_pTimerUpdateEngine->interval()));

    gugu::MusicInstance* pMusic = gugu::GetAudio()->GetCurrentMusicInstance();
    if (pMusic)
    {
        m_pSliderSeek->blockSignals(true);
        m_pSliderSeek->setRange(0, pMusic->GetDuration().GetMilliseconds());
        m_pSliderSeek->setSliderPosition(pMusic->GetPlayOffset().GetMilliseconds());
        m_pSliderSeek->blockSignals(false);
    }
}

void MainWindow::OnControlPlay()
{
    gugu::MusicInstance* pMusic = gugu::GetAudio()->GetCurrentMusicInstance();
    if (pMusic)
    {
        pMusic->Play();
    }
}

void MainWindow::OnControlPause()
{
    gugu::MusicInstance* pMusic = gugu::GetAudio()->GetCurrentMusicInstance();
    if (pMusic)
    {
        pMusic->Pause();
    }
}

void MainWindow::OnControlStop()
{
    gugu::MusicInstance* pMusic = gugu::GetAudio()->GetCurrentMusicInstance();
    if (pMusic)
    {
        pMusic->Stop();
    }
}

void MainWindow::OnVolumeSliderMoved(int value)
{
    gugu::GetAudio()->SetVolumeMaster(((float)value) / (float)PLAYER_UI_VOLUMEUNIT);
}

void MainWindow::OnSeekSliderMoved(int value)
{
    gugu::MusicInstance* pMusic = gugu::GetAudio()->GetCurrentMusicInstance();
    if (pMusic)
    {
        pMusic->SetPlayOffset(gugu::DeltaTime(value));
    }
}
