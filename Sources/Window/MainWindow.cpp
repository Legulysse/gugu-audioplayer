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
#include <QtDebug>

#include "Gugu/Engine.h"
#include "Gugu/Manager/ManagerAudio.h"
#include "Gugu/Manager/ManagerResources.h"
#include "Gugu/Resources/ResourceInfo.h"


MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent)
{
    setAttribute(Qt::WA_DeleteOnClose);

    //Main UI
    setWindowTitle("Gugu::AudioPlayer");
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

    //Central Widget
    QWidget* pCentralWidget = new QWidget(this);
    setCentralWidget(pCentralWidget);

    QVBoxLayout* pCentralLayout = new QVBoxLayout(pCentralWidget);
    pCentralLayout->setSpacing(6);
    pCentralLayout->setContentsMargins(1, 1, 1, 1);
    pCentralWidget->setLayout(pCentralLayout);

    m_pCentralTabWidget = new QTabWidget(pCentralWidget);
    m_pCentralTabWidget->setTabShape(QTabWidget::Rounded);
    pCentralLayout->addWidget(m_pCentralTabWidget);

    // Handle Files drop
    //QObject::connect(this, SIGNAL(dropEvent()), this, SLOT(OnDropEvent()));
    setAcceptDrops(true);

    qDebug("Hello");

    // Finalize
    RefreshMenu();

    //Engine Update
    m_pTimerUpdateEngine = new QTimer(this);
    m_pTimerUpdateEngine->setSingleShot(false);
    connect(m_pTimerUpdateEngine, SIGNAL(timeout()), this, SLOT(UpdateEngine()));
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

    // check for our needed mime type, here a file or a list of files
    if (mimeData->hasUrls())
    {
        QStringList pathList;
        QList<QUrl> urlList = mimeData->urls();

        // extract the local paths of the files
        for (int i = 0; i < urlList.size() && i < 32; ++i)
        {
            pathList.append(urlList.at(i).toLocalFile());
            qDebug() << pathList[i];

            std::string resourceID = pathList[i].toStdString();
            gugu::FileInfo fileInfo(resourceID);

            gugu::GetResources()->AddResourceInfo(resourceID, fileInfo);

            gugu::MusicParameters params;
            params.m_strFile = resourceID;
            params.m_fFadeIn = 0.0f;
            params.m_fFadeOut = 0.0f;
            if (gugu::GetAudio()->PlayMusic(params))
                qDebug("Play success");
            else
                qDebug("Play failed");
        }
    }
}

void MainWindow::RefreshMenu()
{
    m_pMenuBar->clear();

    //Menu Editor
    QMenu* pMenuEditor = new QMenu(m_pMenuBar);
    pMenuEditor->setTitle("Editor");
    m_pMenuBar->addMenu(pMenuEditor);

    QAction* pActionSaveAll = new QAction(pMenuEditor);
    pActionSaveAll->setText("Save All");
    pMenuEditor->addAction(pActionSaveAll);

    pMenuEditor->addSeparator();

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

void MainWindow::UpdateEngine()
{
    gugu::GetEngine()->Step(gugu::DeltaTime(m_pTimerUpdateEngine->interval()));
}

