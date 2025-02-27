//
// Created by cww on 25-2-13.
//

#include <QApplication>
#include <QAudioOutput>
#include <QCloseEvent>
#include <QComboBox>
#include <QMenu>
#include <QMessageBox>
#include <QSystemTrayIcon>
#include "MainWindow.h"
#include <QLabel>
#include <QListView>
#include <QPushButton>
#include "Player.h"
#include "Assets.h"
#include "ViewWidget.h"
#include "PlayerWidget.h"
#include "WindowManager.h"
#include "PlayList.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    initMainApplication();
}

MainWindow::~MainWindow() {
}

void MainWindow::initMainApplication() {
    createTrayIcon();
    m_iconWidget = new ViewWidget("C:/Users/cww/Music/lostgrace", this);
    m_player = new Player();
    m_playerWidget = new PlayerWidget(this);
    m_playerWidget->changeMusicName(PlayList::instance()->getCurrentMusicName());
    m_playerWidget->setButtonVisible(true);

    m_windowManager = new WindowManager(m_iconWidget);
    m_windowManager->setBottomWidget(m_playerWidget);
    createConnect();
    setCentralWidget(m_windowManager);
}

void MainWindow::createConnect() {
    // quit the application
    connect(m_quitAction, &QAction::triggered, qApp, &QApplication::quit);

    // resize the main window
    connect(m_maximizeAction, &QAction::triggered, this, &MainWindow::showMaximized);

    connect(m_minimizeAction, &QAction::triggered, this, &MainWindow::hide);

    connect(m_restoreAction, &QAction::triggered, this, &MainWindow::showNormal);

    connect(m_playerWidget->m_pushButtonNext, &QPushButton::clicked, PlayList::instance(), &PlayList::nextMusic);

    connect(m_playerWidget->m_pushButtonPre, &QPushButton::clicked, PlayList::instance(), &PlayList::previousMusic);

    connect(m_playerWidget->m_pushButtonPlay, &QPushButton::clicked, m_player, &Player::playToggle);

    connect(m_player, &Player::playStatusChanged, m_playerWidget, &PlayerWidget::setPlayButtonIcon);

    connect(PlayList::instance(), &PlayList::currentMusicNameChanged, this, &MainWindow::changeMusicLabelName);

    connect(PlayList::instance(), &PlayList::currentMusicIndexChanged, m_player, &Player::changeSource);

    connect(m_playerWidget->m_volumeWidget->m_sliderV, &QSlider::valueChanged, m_player, &Player::setVolume);

    connect(m_player, &Player::volumeChanged, m_playerWidget, &PlayerWidget::setVolumeCtrlButtonIcon);

    connect(m_playerWidget->m_volumeWidget->m_buttonMute, &QPushButton::clicked, this, [this]() {
        if (m_player->getVolume() == 0) {
            m_player->setVolume(m_playerWidget->m_volumeWidget->m_sliderV->value());
        } else {
            m_player->setVolume(0);
        }
    });

 }

void MainWindow::closeEvent(QCloseEvent *event) {
    if (!event->spontaneous() || !isVisible())
        return;
    if (m_systemTrayIcon->isVisible()) {
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
    m_restoreAction->setEnabled(isMaximized() || !visible);
    m_minimizeAction->setEnabled(visible);
    m_maximizeAction->setEnabled(!isMaximized());
    QMainWindow::setVisible(visible);
}


void MainWindow::changeMusicLabelName(const QString &name) {
    if (!name.isEmpty()) {
        const auto label = name.right(name.size() - name.lastIndexOf('/') - 1);
        m_playerWidget->m_labelMusicFileName->setText(label);
    }
}

void MainWindow::createTrayIcon() {
    m_trayIconMenu = new QMenu(this);
    m_systemTrayIcon = new QSystemTrayIcon(this);
    m_minimizeAction = new QAction(QCoreApplication::translate("TrayUI", "Minimize"), this);
    m_maximizeAction = new QAction(QCoreApplication::translate("TrayUI", "Maximize"), this);
    m_restoreAction = new QAction(QCoreApplication::translate("TrayUI", "Restore"), this);
    m_quitAction = new QAction(QCoreApplication::translate("TrayUI", "Quit"), this);
    m_trayIconMenu->addAction(m_minimizeAction);
    m_trayIconMenu->addAction(m_maximizeAction);
    m_trayIconMenu->addAction(m_restoreAction);
    m_trayIconMenu->addSeparator();
    m_trayIconMenu->addAction(m_quitAction);
    m_systemTrayIcon->setContextMenu(m_trayIconMenu);
    const auto icon = QIcon(Res::trayIconSVG);
    m_systemTrayIcon->setIcon(icon);
    this->setWindowIcon(icon);
    m_systemTrayIcon->setToolTip("Tray Music");
    m_systemTrayIcon->show();
}
