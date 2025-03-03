//
// Created by cww on 25-2-22.
//

#include "WindowManager.h"
#include "MusicListManager.h"
#include <QGroupBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSlider>
#include "PlayerWidget.h"
#include "PlayList.h"
#include "Settings.h"
#include "ViewWidget.h"

WindowManager::WindowManager(const Settings *settings, QWidget *parent)
    : QWidget(parent)
{
    this->m_player = new Player(settings->getDefaultVolume());
    this->m_mainWidget = new ViewWidget(this);
    this->m_buttonWidget = new PlayerWidget(this);
    m_buttonWidget->m_volumeWidget->loadDefaultSetting(settings->getDefaultVolume());
    this->m_leftWidget = new MusicListManager(this);
    this->m_switchWidget = nullptr;

    m_viewLayout = new QHBoxLayout;
    m_viewLayout->setSpacing(0);
    m_viewLayout->setContentsMargins(0, 0, 0, 0);
    m_viewLayout->addWidget(m_leftWidget);
    m_viewLayout->addWidget(m_mainWidget);

    const auto m_bottomLayout = new QHBoxLayout;
    m_bottomLayout->setSpacing(0);
    m_bottomLayout->setContentsMargins(0, 0, 0, 0);
    m_bottomLayout->addWidget(m_buttonWidget);

    const auto bottomGroup = new QGroupBox;
    bottomGroup->setLayout(m_bottomLayout);

    const auto Layout = new QVBoxLayout(this);
    Layout->addItem(m_viewLayout);
    Layout->addWidget(bottomGroup);
    createConnections();
}

void WindowManager::createConnections() {
    // play or pause
    connect(m_buttonWidget->m_pushButtonPlay, &QPushButton::clicked, m_player, &Player::playToggle);

    // update the icon of playButton
    connect(m_player, &Player::playStatusChanged, m_buttonWidget, &PlayerWidget::setPlayButtonIcon);

    // set volume
    connect(m_buttonWidget->m_volumeWidget->m_sliderV, &QSlider::valueChanged, m_player, &Player::setVolume);
    connect(m_player, &Player::volumeChanged, m_buttonWidget, &PlayerWidget::setVolumeCtrlButtonIcon);
    connect(m_buttonWidget->m_volumeWidget->m_buttonMute, &QPushButton::clicked, this, [this]() {
        if (m_player->getVolume() == 0) {
            m_player->setVolume(m_buttonWidget->m_volumeWidget->m_sliderV->value());
        } else {
            m_player->setVolume(0);
        }
    });

    // progressbar and set position
    connect(m_player, &Player::playPositionChanged, m_buttonWidget->m_progressWidget, &ProgressBarWidget::updateSliderPosition);
    connect(m_player, &Player::playPositionChanged, m_buttonWidget->m_progressWidget, &ProgressBarWidget::updateLabelL);
    connect(PlayList::instance(), &PlayList::currentMusicIndexChanged, m_buttonWidget->m_progressWidget, &ProgressBarWidget::updateLabelR);
    connect(m_buttonWidget->m_progressWidget->m_sliderP, &QSlider::valueChanged, this, [this](const int value) {
        if (m_buttonWidget->m_progressWidget->m_isUpdatingSlider) {
            return;
        }
        m_player->setPlayPosition(value);
    });
}

WindowManager::~WindowManager() {

}

void WindowManager::showMainWidget() {
}


void WindowManager::showOtherWidget(QWidget *widget) {
}

void WindowManager::setBottomWidget(QWidget *widget) {
}



