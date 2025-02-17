//
// Created by cww on 25-2-13.
//

#include "MainWindow.h"
#include <QApplication>
#include <QAudioOutput>
#include <QCheckBox>
#include <QComboBox>
#include <QSystemTrayIcon>
#include <QCloseEvent>
#include <QMessageBox>
#include <QFileDialog>
#include <QPushButton>
#include <QLabel>
#include "TrayUI.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_centralWidget(new QWidget(this))
      , m_gui(new TrayUI)
{
    initMainApplication();
}

MainWindow::~MainWindow() {
    delete m_gui;
    delete m_player;
}

void MainWindow::loadSettings() {
    QStringList musicPathList;
    musicPathList.append("C:/Users/cww/Music/lostgrace");
    m_player = new Player(musicPathList);
}


void MainWindow::initMainApplication() {
    loadSettings();
    setCentralWidget(m_centralWidget);
    m_gui->setupUI(this);
    createConnect();
    m_gui->systemTrayIcon->show();
    m_gui->labelSongName->setText(m_player->currentMusic());
    m_gui->pushButtonPlay->setEnabled(true);
    m_gui->pushButtonNext->setEnabled(true);
    m_gui->pushButtonPre->setEnabled(true);
    this->setWindowIcon(QIcon(":/images/icon.svg"));
}

void MainWindow::createConnect() {
    // quit the application
    connect(m_gui->quitAction, &QAction::triggered, qApp, &QApplication::quit);

    // resize the main window
    connect(m_gui->maximizeAction, &QAction::triggered, this, &MainWindow::showMaximized);
    connect(m_gui->minimizeAction, &QAction::triggered, this, &MainWindow::hide);
    connect(m_gui->restoreAction, &QAction::triggered, this, &MainWindow::showNormal);

    connect(m_gui->showIconCheckBox, &QCheckBox::toggled, m_gui->systemTrayIcon, &QSystemTrayIcon::setVisible);

    // play music
    // connect(m_gui->pushButtonLoadFile, &QPushButton::clicked, this, [this]() {
    //     if (const QString fileName = QFileDialog::getOpenFileName(this, tr("Open Mp3"),"", tr("Mp3 Files (*.mp3)")); fileName.isEmpty()) {
    //         return;
    //     }
    //     else {
    //         m_player->loadMusic(QUrl::fromLocalFile(fileName));
    //         m_gui->labelSongName->setText(fileName);
    //     }
    // });

    connect(m_gui->pushButtonNext, &QPushButton::clicked, m_player, &Player::nextMusic);
    connect(m_gui->pushButtonPre, &QPushButton::clicked, m_player, &Player::previousMusic);

    connect(m_gui->pushButtonPlay, &QPushButton::clicked, this, [this]() {
        m_player->playToggle();
    });

    connect(m_player, &Player::playStatusChanged, this, &MainWindow::setPlayButtonIcon);

    connect(m_player, &Player::currentMusicChanged, this, &MainWindow::changeMusicLabelName);
}

void MainWindow::closeEvent(QCloseEvent *event) {
    if (!event->spontaneous() || !isVisible())
        return;
    if (m_gui->systemTrayIcon->isVisible()) {
        QMessageBox::information(this, tr("Tray"), tr(
                                     "The program will keep running in the "
                                     "system tray. To terminate the program, "
                                     "choose <b>Quit</b> in the context menu "
                                     "of the system tray entry."));
        this->hide();
        event->ignore();
    }
}

void MainWindow::setVisible(const bool visible) {
    m_gui->restoreAction->setEnabled(isMaximized() || !visible);
    m_gui->minimizeAction->setEnabled(visible);
    m_gui->maximizeAction->setEnabled(!isMaximized());
    QMainWindow::setVisible(visible);
}

void MainWindow::setPlayButtonIcon(bool play) {
    if (play) {
        m_gui->pushButtonPlay->setIcon(QIcon(m_gui->pauseIconSVG));
    }
    else {
        m_gui->pushButtonPlay->setIcon(QIcon(m_gui->playIconSVG));
    }
}

void MainWindow::changeMusicLabelName(const QString& name) {
    if (!name.isEmpty()) {
        m_gui->labelSongName->setText(name);
    }
}

