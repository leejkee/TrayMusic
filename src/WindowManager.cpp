//
// Created by cww on 25-2-22.
//

#include "WindowManager.h"
#include "MusicListManager.h"
#include <QGroupBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QListWidget>
#include <QSlider>
#include <QStackedWidget>

#include "Assets.h"
#include "TopBarWidget.h"
#include "Player.h"
#include "PlayerWidget.h"
#include "PlayList.h"
#include "Settings.h"
#include "ViewWidget.h"

WindowManager::WindowManager(const Settings *settings, QWidget *parent)
    : QWidget(parent)
{
    this->m_player = new Player(settings->getDefaultVolume());
    this->m_viewWidget = new ViewWidget(this);
    this->m_bottomWidget = new PlayerWidget(this);
    m_bottomWidget->m_volumeWidget->loadDefaultSetting(settings->getDefaultVolume());
    this->m_leftWidget = new MusicListManager(this);
    this->m_settingsWidget = new SettingsWidget(this);
    this->m_topBarWidget = new TopBarWidget(this);
    this->m_stackedWidget = new QStackedWidget(this);
    m_stackedWidget->addWidget(m_viewWidget);
    m_stackedWidget->addWidget(m_settingsWidget);

    m_viewLayout = new QHBoxLayout;
    m_viewLayout->setSpacing(0);
    m_viewLayout->setContentsMargins(0, 0, 0, 0);
    m_viewLayout->addWidget(m_leftWidget);
    m_viewLayout->addWidget(m_stackedWidget);
    // m_viewLayout->addWidget(m_stackedWidget);

    // bottom layout
    const auto m_bottomLayout = new QHBoxLayout;
    m_bottomLayout->setSpacing(0);
    m_bottomLayout->setContentsMargins(0, 0, 0, 0);
    m_bottomLayout->addWidget(m_bottomWidget);
    const auto bottomGroup = new QGroupBox;
    bottomGroup->setLayout(m_bottomLayout);
    // bottom layout

    const auto Layout = new QVBoxLayout(this);
    Layout->addWidget(m_topBarWidget);
    Layout->addItem(m_viewLayout);
    Layout->addWidget(bottomGroup);
    createConnections();
}

void WindowManager::createConnections() {
    // play or pause
    connect(m_bottomWidget->m_pushButtonPlay, &QPushButton::clicked, m_player, &Player::playToggle);

    // update the icon of playButton
    connect(m_player, &Player::playStatusChanged, m_bottomWidget, &PlayerWidget::setPlayButtonIcon);

    // set volume
    connect(m_bottomWidget->m_volumeWidget->m_sliderV, &QSlider::valueChanged, m_player, &Player::setVolume);
    connect(m_player, &Player::volumeChanged, m_bottomWidget, &PlayerWidget::setVolumeCtrlButtonIcon);
    connect(m_bottomWidget->m_volumeWidget->m_buttonMute, &QPushButton::clicked, this, [this]() {
        if (m_player->getVolume() == 0) {
            m_player->setVolume(m_bottomWidget->m_volumeWidget->m_sliderV->value());
        } else {
            m_player->setVolume(0);
        }
    });

    // progressbar and set position
    connect(m_player, &Player::playPositionChanged, m_bottomWidget->m_progressWidget, &ProgressBarWidget::updateSliderPosition);
    connect(m_player, &Player::playPositionChanged, m_bottomWidget->m_progressWidget, &ProgressBarWidget::updateLabelL);
    connect(PlayList::instance(), &PlayList::currentMusicIndexChanged, m_bottomWidget->m_progressWidget, &ProgressBarWidget::updateLabelR);
    connect(m_bottomWidget->m_progressWidget->m_sliderP, &QSlider::valueChanged, this, [this](const int value) {
        if (m_bottomWidget->m_progressWidget->m_isUpdatingSlider) {
            return;
        }
        m_player->setPlayPosition(value);
    });

    connect(m_topBarWidget->m_settingsButton, &QPushButton::clicked, this, &WindowManager::showSettingsWidget);
    connect(m_topBarWidget->m_preButton, &QPushButton::clicked, this, &WindowManager::showMainWidget);
}

WindowManager::~WindowManager() {

}

void WindowManager::showMainWidget() {
    qDebug() << "WindowManager::showMainWidget()";
    m_stackedWidget->setCurrentIndex(0);
}

void WindowManager::showSettingsWidget() {
    qDebug() << "showSettingsWidget";
    m_stackedWidget->setCurrentIndex(1);
}

SettingsWidget::SettingsWidget(QWidget *parent) {
    this->addBtn = new QPushButton(QIcon(Res::addSVG), "", this);
    this->listWidget = new QListWidget(this);
    this->removeBtn = new QPushButton(QIcon(Res::removeSVG), "", this);

    const auto hlayout = new QHBoxLayout;
    const auto spaceH = new QSpacerItem(-1, 0, QSizePolicy::Expanding);
    hlayout->addWidget(addBtn);
    hlayout->addItem(spaceH);
    hlayout->addWidget(removeBtn);

    const auto layout = new QVBoxLayout(this);
    layout->addItem(hlayout);
    layout->addWidget(listWidget);

}
