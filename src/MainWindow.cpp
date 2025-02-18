//
// Created by cww on 25-2-13.
//

#include <QApplication>
#include <QAudioOutput>
#include <QCheckBox>
#include <QComboBox>
#include <QSystemTrayIcon>
#include <QCloseEvent>
#include <QMessageBox>
#include <QPushButton>
#include <QLabel>

#include "MainWindow.h"
#include "TrayUI.h"
#include "Player.h"

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
    m_gui->labelMusicFileName->setText(m_player->currentMusic());
    m_gui->pushButtonPlay->setEnabled(true);
    m_gui->pushButtonNext->setEnabled(true);
    m_gui->pushButtonPre->setEnabled(true);
    this->setWindowIcon(QIcon(TrayUI::trayIconSVG));
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
    connect(m_gui->volumeSlider, &QSlider::valueChanged, m_player, &Player::setVolume);
    connect(m_player, &Player::volumeChanged, this, [this](const int v) {
        if (v != 0) {
            this->m_gui->volumeCtrlButton->setIcon(QIcon(TrayUI::volumeSVG));
        }
        else {
            this->m_gui->volumeCtrlButton->setIcon(QIcon(TrayUI::volumeMuteSVG));
        }
    });
    connect(m_gui->volumeCtrlButton, &QPushButton::clicked, this, [this]() {
        if (m_player->getVolume() == 0) {
            m_player->setVolume(m_gui->volumeSlider->value());
        }
        else {
            m_player->setVolume(0);
        }
    });

    connect(m_gui->pushButtonLoadFile, &QPushButton::clicked, this, [this]() {
        QPoint pos = m_gui->volumeCtrlButton->pos() + QPoint(m_gui->volumeCtrlButton->width(), 0);
        m_gui->volumeControlWidget->move(pos);
        m_gui->volumeControlWidget->show();
        // 不可信，控件不能随着主窗口移动
    });
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

void MainWindow::setPlayButtonIcon(const bool play) {
    if (play) {
        m_gui->pushButtonPlay->setIcon(QIcon(TrayUI::pauseIconSVG));
    }
    else {
        m_gui->pushButtonPlay->setIcon(QIcon(TrayUI::playIconSVG));
    }
}

void MainWindow::changeMusicLabelName(const QString& name) {
    if (!name.isEmpty()) {
        const auto label = name.right(name.size() - name.lastIndexOf('/') - 1);
        m_gui->labelMusicFileName->setText(label);
    }
}

// void MainWindow::mouseMoveEvent(QMouseEvent *event) {
//     if (m_gui->volumeCtrlButton->geometry().contains(event->pos())) {
//         QPoint pos = m_gui->volumeCtrlButton->pos() + QPoint(m_gui->volumeCtrlButton->width(), 0);
//         m_gui->volumeControlWidget->move(pos);
//         m_gui->volumeControlWidget->show();
//     }
// }
//
// void MainWindow::mouseLeaveEvent(QMouseEvent *event) {
//     if (!m_gui->volumeCtrlButton->geometry().contains(event->pos())) {
//         m_gui->volumeControlWidget->hide();
//     }
// }

