#include "Dialog/DialogAbout.h"

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

    QLabel* pTextVersionEditor = new QLabel("Gugu::Editor version 0.1", this);
    pTextVersionEditor->setTextInteractionFlags(Qt::TextBrowserInteraction);
    pLayout->addWidget(pTextVersionEditor);

    QLabel* pTextVersionQt = new QLabel("Qt version " + QString(qVersion()), this);
    pTextVersionQt->setTextInteractionFlags(Qt::TextBrowserInteraction);
    pLayout->addWidget(pTextVersionQt);
}
