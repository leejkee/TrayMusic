//
// Created by cww on 25-2-14.
//
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QDir>
#include "Player.h"
#include "PlayList.h"
#include "Settings.h"


Player::Player()
    : m_player(new QMediaPlayer)
      , m_audioOut(new QAudioOutput)
      , m_isPlay(false)
      , m_volume(Settings::instance().getDefaultVolume()) {
    m_player->setAudioOutput(m_audioOut);
    m_audioOut->setVolume(m_volume);
    loadMusic(QUrl::fromLocalFile(PlayList::instance()->getCurrentMusicPath()));
    connect(m_player, &QMediaPlayer::positionChanged, this, [this](const qint64 position) {
        emit playPositionChanged(position);
    });
    connect(m_player, &QMediaPlayer::mediaStatusChanged, this, [this](const QMediaPlayer::MediaStatus status) {
        if (status == QMediaPlayer::EndOfMedia) {
            emit playMusicEnd();
        }
    });
    // update the source of player when the current music changed
    connect(PlayList::instance(), &PlayList::currentMusicIndexChanged, this, &Player::changeSource);
    // auto check music
    connect(this, &Player::playMusicEnd, PlayList::instance(), &PlayList::nextMusic);
}

void Player::setPlayStatus(const bool playStatus) {
    if (playStatus != m_isPlay) {
        m_isPlay = playStatus;
        emit playStatusChanged(m_isPlay);
    }
}

Player::~Player() {
    delete m_player;
    delete m_audioOut;
}


void Player::loadMusic(const QUrl &mp3Url) {
    m_player->setSource(mp3Url);
}

void Player::setVolume(int volume) {
    if (volume > 100) {
        volume = 100;
    } else if (volume < 0) {
        volume = 0;
    }
    if (const float v = static_cast<float>(volume) / 100.0f; v != m_volume) {
        m_audioOut->setVolume(v);
        m_volume = v;
        emit volumeChanged(volume);
    }
}

float Player::getVolume() const {
    return m_volume;
}

void Player::playToggle() {
    if (m_isPlay != true) {
        m_player->play();
        setPlayStatus(true);
    } else {
        m_player->pause();
        setPlayStatus(false);
    }
}

void Player::changeSource() {
    const QUrl mp3Url = QUrl::fromLocalFile(PlayList::instance()->getCurrentMusicPath());
    m_player->stop();
    m_player->setSource(mp3Url);
    m_player->play();
    setPlayStatus(true);
}

void Player::setPlayPosition(const qint64 position) {
    m_player->setPosition(position);
}
