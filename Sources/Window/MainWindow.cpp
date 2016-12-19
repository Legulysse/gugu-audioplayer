#include "Window/MainWindow.h"

#include "Dialog/DialogAbout.h"

#include <QtCore/QTimer>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QAction>


MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent)
{
    setAttribute(Qt::WA_DeleteOnClose);

    //Main UI
    setWindowTitle("Gugu::Editor");
    setWindowIcon(QIcon("Icons/application2.png"));
    //setWindowIcon(QIcon("Icons/smiley_cool.png"));

    resize(1024, 768);
    setMinimumSize(QSize(800, 600));

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

    RefreshMenu();
}

MainWindow::~MainWindow()
{
    qDebug("Release MainWindow");
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

    QObject::connect(pActionSaveAll, SIGNAL(triggered()), this, SLOT(OnSaveAll()));

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

