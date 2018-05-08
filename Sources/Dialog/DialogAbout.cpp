#include "Dialog/DialogAbout.h"

#include "Gugu/Version.h"

#include <QIcon>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>


DialogAbout::DialogAbout()
: QDialog()
{
    setWindowTitle("About");
    setWindowIcon(QIcon("Icons/help.png"));
    setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);

    QVBoxLayout* pLayout = new QVBoxLayout;
    pLayout->setMargin(20);
    setLayout(pLayout);

    QLabel* pTextVersionApplication = new QLabel("Gugu::AudioPlayer 0.1", this);
    pTextVersionApplication->setTextInteractionFlags(Qt::TextBrowserInteraction);
    pLayout->addWidget(pTextVersionApplication);

    QLabel* pTextVersionEngine = new QLabel("Gugu::Engine " + QString(GUGU_VERSION), this);
    pTextVersionEngine->setTextInteractionFlags(Qt::TextBrowserInteraction);
    pLayout->addWidget(pTextVersionEngine);

    QLabel* pTextVersionQt = new QLabel("Qt " + QString(qVersion()), this);
    pTextVersionQt->setTextInteractionFlags(Qt::TextBrowserInteraction);
    pLayout->addWidget(pTextVersionQt);
}
