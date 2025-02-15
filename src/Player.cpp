//
// Created by cww on 25-2-14.
//
#include <QMediaPlayer>
#include <QAudioOutput>
#include "Player.h"

Player::Player()
    : m_player(new QMediaPlayer)
      , m_audioOut(new QAudioOutput)
      , m_isPlay(false)
      , m_volume(0.3) {
    m_player->setAudioOutput(m_audioOut);
    m_audioOut->setVolume(m_volume);
}

Player::~Player() {
    delete m_player;
    delete m_audioOut;
}

void Player::loadMusic(const QUrl &mp3Url) {
    m_player->setSource(mp3Url);
}

void Player::volumeUp() {
    m_volume = (m_volume == 1 ? 1 : (m_volume + static_cast<float>(0.2)));
    m_audioOut->setVolume(m_volume);
}

void Player::volumeDown() {
    m_volume = (m_volume == 0 ? 0 : (m_volume - static_cast<float>(0.2)));
    m_audioOut->setVolume(m_volume);
}

void Player::volumeSet(const float volume) {
    m_audioOut->setVolume(volume);
}

void Player::muteToggle() {
    if (m_volume == 0) {
        volumeUp();
        return;
    }
    m_volume = 0;
    volumeSet(m_volume);
}


void Player::playToggle() {
    if (m_isPlay != true) {
        m_player->play();
        m_isPlay = true;
    } else {
        m_player->pause();
        m_isPlay = false;
    }
    emit playStatusChanged(m_isPlay);
}

bool Player::playStatus() const {
    return this->m_isPlay;
}
