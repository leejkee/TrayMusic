#include "TrayUI.h"
#include "QMainWindow"
#include <QCheckBox>
#include <QComboBox>
#include <QCoreApplication>
#include <QGroupBox>
#include <QLabel>
#include <QMenu>
#include <QPushButton>
#include <QSystemTrayIcon>
#include <QVBoxLayout>


TrayUI::TrayUI()
    : trayIconSVG(":images/icon.svg")
    , playIconSVG(":/images/play.svg")
    , pauseIconSVG(":/images/pause.svg")
    , preIconSVG(":/images/pre.svg")
    , nextIconSVG(":/images/next.svg")
{
}

/// You should call the function QMainWindow::setCentralWidget() before you use this function
/// @param parent the pointer to MainWindow
void TrayUI::setupUI(QMainWindow *parent) {
    createIconGroupBox();
    createMusicPlayerGroupBox();
    createActions(parent);
    createTrayIconMenu(parent);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(iconGroupBox);
    mainLayout->addWidget(musicPlayerGroupBox);
    QWidget *parentPtr = parent->centralWidget();
    if (parentPtr != nullptr) {
        parentPtr->setLayout(mainLayout);
    }
}


void TrayUI::createIconGroupBox() {
    iconGroupBox = new QGroupBox(QCoreApplication::translate("TrayUI", ("Tray Icon")));
    showIconCheckBox = new QCheckBox(QCoreApplication::translate("TrayUI", "Show icon"));
    showIconCheckBox->setChecked(true);
    pushButtonLoadFile = new QPushButton(QCoreApplication::translate("TrayUI", "Load File"));

    QHBoxLayout *iconLayout = new QHBoxLayout;
    iconLayout->addWidget(showIconCheckBox);
    iconLayout->addStretch();
    iconLayout->addWidget(pushButtonLoadFile);
    iconGroupBox->setLayout(iconLayout);
}

void TrayUI::createMusicPlayerGroupBox() {
    musicPlayerGroupBox = new QGroupBox(QCoreApplication::translate("TrayUI", "Music Player"));
    pushButtonPlay = new QPushButton(QIcon(playIconSVG), "");
    labelSongName = new QLabel(QCoreApplication::translate("TrayUI", "Song Name"));
    pushButtonPre = new QPushButton(QIcon(preIconSVG), "");
    pushButtonNext = new QPushButton(QIcon(nextIconSVG), "");
    pushButtonPlay->setEnabled(false);
    pushButtonNext->setEnabled(false);
    pushButtonPre->setEnabled(false);

    QGridLayout *Layout = new QGridLayout;
    Layout->addWidget(labelSongName, 0, 0, 1, 3);
    Layout->addWidget(pushButtonPlay, 1, 1, 1, 1);
    Layout->addWidget(pushButtonNext, 1, 2, 1, 1);
    Layout->addWidget(pushButtonPre, 1, 0, 1, 1);
    musicPlayerGroupBox->setLayout(Layout);
}

void TrayUI::createActions(QWidget *parent) {
    minimizeAction = new QAction(QCoreApplication::translate("TrayUI", "Minimize"), parent);
    maximizeAction = new QAction(QCoreApplication::translate("TrayUI", "Maximize"), parent);
    restoreAction = new QAction(QCoreApplication::translate("TrayUI", "Restore"), parent);
    quitAction = new QAction(QCoreApplication::translate("TrayUI", "Quit"), parent);
}

void TrayUI::createTrayIconMenu(QWidget *parent) {
    trayIconMenu = new QMenu(parent);
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(maximizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    systemTrayIcon = new QSystemTrayIcon(parent);
    systemTrayIcon->setContextMenu(trayIconMenu);

    const auto icon = QIcon(trayIconSVG);
    systemTrayIcon->setIcon(icon);
    parent->setWindowIcon(icon);
    systemTrayIcon->setToolTip("Tray Music");
}
