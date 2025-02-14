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
#include <QMediaPlayer>
#include <QAudioOutput>


TrayUI::TrayUI() {
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
    QWidget* parentPtr = parent->centralWidget();
    if (parentPtr != nullptr) {
        parentPtr->setLayout(mainLayout);
    }
}


void TrayUI::createIconGroupBox() {
    iconGroupBox = new QGroupBox(QCoreApplication::translate("TrayUI", ("Tray Icon")));

    iconLabel = new QLabel(QCoreApplication::translate("TrayUI", ("Icon:")));
    iconComboBox = new QComboBox;
    iconComboBox->addItem(QIcon(":/images/bad.png"), QCoreApplication::translate("TrayUI", ("Bad")));
    iconComboBox->addItem(QIcon(":/images/heart.png"), QCoreApplication::translate("TrayUI", ("Heart")));
    iconComboBox->addItem(QIcon(":/images/trash.png"), QCoreApplication::translate("TrayUI", ("Trash")));
    showIconCheckBox = new QCheckBox(QCoreApplication::translate("TrayUI", "Show icon"));
    showIconCheckBox->setChecked(true);

    QHBoxLayout *iconLayout = new QHBoxLayout;
    iconLayout->addWidget(iconLabel);
    iconLayout->addWidget(iconComboBox);
    iconLayout->addStretch();
    iconLayout->addWidget(showIconCheckBox);
    iconGroupBox->setLayout(iconLayout);
}

void TrayUI::createMusicPlayerGroupBox() {
    musicPlayerGroupBox = new QGroupBox(QCoreApplication::translate("TrayUI", "Music Player"));
    pushButtonPlay = new QPushButton(QCoreApplication::translate("TrayUI", "Play"));
    pushButtonPlay->setCheckable(true);
    pushButtonPlay->setAutoExclusive(true);
    labelSongName = new QLabel(QCoreApplication::translate("TrayUI", "Song Name"));
    pushButtonLoadFile = new QPushButton(QCoreApplication::translate("TrayUI", "Load File"));
    QGridLayout *Layout = new QGridLayout;
    Layout->addWidget(pushButtonLoadFile, 0, 0, 1, 1);
    Layout->addWidget(pushButtonPlay, 0, 1, 1, 1);
    Layout->addWidget(labelSongName, 1, 0, 1, 2);
    musicPlayerGroupBox->setLayout(Layout);
}

void TrayUI::createActions(QWidget* parent) {
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

    const auto icon = iconComboBox->itemIcon(iconComboBox->currentIndex());
    systemTrayIcon->setIcon(icon);
    parent->setWindowIcon(icon);
    systemTrayIcon->setToolTip(iconComboBox->itemText(iconComboBox->currentIndex()));
}


