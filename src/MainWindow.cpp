//
// Created by cww on 25-2-13.
//

#include <QApplication>
#include <QAudioOutput>
#include <QCloseEvent>
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
#include "Settings.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      , m_settings(new Settings) {
    initMainApplication();
}

MainWindow::~MainWindow() {
    delete m_settings;
}

void MainWindow::loadSettings() {
    PlayList::instance()->loadMusicFromDirectories(m_settings->getMusicDirectories());
}

void MainWindow::initMainApplication() {
    loadSettings();
    m_viewWidget = new ViewWidget(this);
    m_player = new Player(m_settings->getDefaultVolume());
    m_playerWidget = new PlayerWidget(this);
    m_playerWidget->m_volumeWidget->loadDefaultSetting(m_settings->getDefaultVolume());
    m_windowManager = new WindowManager(m_viewWidget, this);
    m_windowManager->setBottomWidget(m_playerWidget);
    createConnections();
    setCentralWidget(m_windowManager);
    createTrayIcon();
}

void MainWindow::createConnections() {
    // quit the application
    connect(m_quitAction, &QAction::triggered, qApp, &QApplication::quit);

    // resize the main window
    connect(m_maximizeAction, &QAction::triggered, this, &MainWindow::showMaximized);
    connect(m_minimizeAction, &QAction::triggered, this, &MainWindow::hide);
    connect(m_restoreAction, &QAction::triggered, this, &MainWindow::showNormal);

    // play or pause
    connect(m_playerWidget->m_pushButtonPlay, &QPushButton::clicked, m_player, &Player::playToggle);

    // update the icon of playButton
    connect(m_player, &Player::playStatusChanged, m_playerWidget, &PlayerWidget::setPlayButtonIcon);

    // set volume
    connect(m_playerWidget->m_volumeWidget->m_sliderV, &QSlider::valueChanged, m_player, &Player::setVolume);
    connect(m_player, &Player::volumeChanged, m_playerWidget, &PlayerWidget::setVolumeCtrlButtonIcon);
    connect(m_playerWidget->m_volumeWidget->m_buttonMute, &QPushButton::clicked, this, [this]() {
        if (m_player->getVolume() == 0) {
            m_player->setVolume(m_playerWidget->m_volumeWidget->m_sliderV->value());
        } else {
            m_player->setVolume(0);
        }
    });

    // progressbar and set position
    connect(m_player, &Player::playPositionChanged, m_playerWidget->m_progressWidget,
            &ProgressBarWidget::updateSliderPosition);
    connect(m_player, &Player::playPositionChanged, m_playerWidget->m_progressWidget, &ProgressBarWidget::updateLabelL);
    connect(PlayList::instance(), &PlayList::currentMusicIndexChanged, m_playerWidget->m_progressWidget,
            &ProgressBarWidget::updateLabelR);

    connect(m_playerWidget->m_progressWidget->m_sliderP, &QSlider::valueChanged, this, [this](const int value) {
        if (m_playerWidget->m_progressWidget->m_isUpdatingSlider) {
            return;
        }
        m_player->setPlayPosition(value);
    });

    // auto check music
    connect(m_player, &Player::playMusicEnd, PlayList::instance(), &PlayList::nextMusic);
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
