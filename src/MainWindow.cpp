//
// Created by cww on 25-2-13.
//

#include <QApplication>
#include <QAudioOutput>
#include <QCheckBox>
#include <QCloseEvent>
#include <QComboBox>
#include <QMenu>
#include <QMessageBox>
#include <QSystemTrayIcon>
#include "MainWindow.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include "Player.h"
#include "Assets.h"
#include "IconWidget.h"
#include "PlayerWidget.h"
#include <QGroupBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), m_centralWidget(new QWidget(this)) {
    initMainApplication();
}

MainWindow::~MainWindow() {
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
    initTray();
    m_iconWidget = new IconWidget(m_centralWidget);
    m_playerWidget = new PlayerWidget(m_centralWidget);

    QGroupBox *iconBox = new QGroupBox(this);
    QGroupBox *playerBox = new QGroupBox(this);
    auto iconLayout = new QVBoxLayout;
    iconLayout->addWidget(m_iconWidget);
    iconBox->setLayout(iconLayout);
    auto playerLayout = new QGridLayout;
    playerLayout->addWidget(m_playerWidget);
    playerBox->setLayout(playerLayout);

    createConnect();
    m_playerWidget->changeMusicName(m_player->currentMusic());
    m_playerWidget->setButtonVisible(true);
    const auto layout = new QVBoxLayout;
    layout->addWidget(iconBox);
    layout->addWidget(playerBox);
    playerBox->setFixedHeight(100);
    m_centralWidget->setLayout(layout);
    this->setWindowIcon(QIcon(Res::trayIconSVG));
}

void MainWindow::createConnect() {
    // quit the application
    connect(quitAction, &QAction::triggered, qApp, &QApplication::quit);

    // resize the main window
    connect(maximizeAction, &QAction::triggered, this, &MainWindow::showMaximized);

    connect(minimizeAction, &QAction::triggered, this, &MainWindow::hide);

    connect(restoreAction, &QAction::triggered, this, &MainWindow::showNormal);

    connect(m_iconWidget->showIconCheckBox, &QCheckBox::toggled, systemTrayIcon, &QSystemTrayIcon::setVisible);

    // play music
    // connect(m_gui->pushButtonLoadFile, &QPushButton::clicked, this, [this]() {
    //     if (const QString fileName = QFileDialog::getOpenFileName(this,
    //     tr("Open Mp3"),"", tr("Mp3 Files (*.mp3)")); fileName.isEmpty()) {
    //         return;
    //     }
    //     else {
    //         m_player->loadMusic(QUrl::fromLocalFile(fileName));
    //         m_gui->labelSongName->setText(fileName);
    //     }
    // });

    connect(m_playerWidget->pushButtonNext, &QPushButton::clicked, m_player,
            &Player::nextMusic);

    connect(m_playerWidget->pushButtonPre, &QPushButton::clicked, m_player,
            &Player::previousMusic);

    connect(m_playerWidget->pushButtonPlay, &QPushButton::clicked, m_player, &Player::playToggle);

    connect(m_player, &Player::playStatusChanged, m_playerWidget, &PlayerWidget::setPlayButtonIcon);

    connect(m_player, &Player::currentMusicChanged, this, &MainWindow::changeMusicLabelName);

    connect(m_playerWidget->volumeWidget->sliderV, &QSlider::valueChanged, m_player, &Player::setVolume);

    connect(m_player, &Player::volumeChanged, m_playerWidget, &PlayerWidget::setVolumeCtrlButtonIcon);

    connect(m_playerWidget->volumeWidget->buttonMute, &QPushButton::clicked, this, [this]() {
        if (m_player->getVolume() == 0) {
            m_player->setVolume(m_playerWidget->volumeWidget->sliderV->value());
        } else {
            m_player->setVolume(0);
        }
    });

    // connect(m_iconWidget->pushButtonLoadFile, &QPushButton::clicked, this, [this]() {
    //     m_playerWidget->widget->setWindowFlags(Qt::Popup | Qt::FramelessWindowHint);
    //     m_playerWidget->widget->show();
    // });
}

void MainWindow::closeEvent(QCloseEvent *event) {
    if (!event->spontaneous() || !isVisible())
        return;
    if (systemTrayIcon->isVisible()) {
        QMessageBox::information(this, tr("Tray"),
                                 tr("The program will keep running in the "
                                     "system tray. To terminate the program, "
                                     "choose <b>Quit</b> in the context menu "
                                     "of the system tray entry."));
        this->hide();
        event->ignore();
    }
}

void MainWindow::setVisible(const bool visible) {
    restoreAction->setEnabled(isMaximized() || !visible);
    minimizeAction->setEnabled(visible);
    maximizeAction->setEnabled(!isMaximized());
    QMainWindow::setVisible(visible);
}


void MainWindow::changeMusicLabelName(const QString &name) {
    if (!name.isEmpty()) {
        const auto label = name.right(name.size() - name.lastIndexOf('/') - 1);
        m_playerWidget->labelMusicFileName->setText(label);
    }
}

void MainWindow::initTray() {
    trayIconMenu = new QMenu(this);
    systemTrayIcon = new QSystemTrayIcon(this);
    minimizeAction = new QAction(QCoreApplication::translate("TrayUI", "Minimize"), this);
    maximizeAction = new QAction(QCoreApplication::translate("TrayUI", "Maximize"), this);
    restoreAction = new QAction(QCoreApplication::translate("TrayUI", "Restore"), this);
    quitAction = new QAction(QCoreApplication::translate("TrayUI", "Quit"), this);
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(maximizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);
    systemTrayIcon->setContextMenu(trayIconMenu);
    const auto icon = QIcon(Res::trayIconSVG);
    systemTrayIcon->setIcon(icon);
    this->setWindowIcon(icon);
    systemTrayIcon->setToolTip("Tray Music");
    systemTrayIcon->show();
}
