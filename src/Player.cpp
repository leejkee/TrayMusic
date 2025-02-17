//
// Created by cww on 25-2-14.
//
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QDir>
#include "Player.h"


Player::Player(const QStringList& list)
    : m_player(new QMediaPlayer)
      , m_audioOut(new QAudioOutput)
      , m_isPlay(false)
      , m_volume(0.3) {
    m_player->setAudioOutput(m_audioOut);
    m_audioOut->setVolume(m_volume);
    if (!list.isEmpty()) {
        for (const auto& it : list) {
            QDir dir(it);
            QStringList files = dir.entryList(QDir::Files);
            for (const auto& file : files) {
                m_musicList.append(dir.absoluteFilePath(file));
            }
        }
        m_currentMusicIt = m_musicList.begin();
        loadMusic(QUrl::fromLocalFile(*m_currentMusicIt));
    }
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

void Player::nextMusic() {
    if (m_currentMusicIt == m_musicList.end()) {
        m_currentMusicIt = m_musicList.begin();
    }
    ++m_currentMusicIt;
    emit currentMusicChanged(*m_currentMusicIt);
    loadMusic(*m_currentMusicIt);
    m_player->play();
}

void Player::previousMusic() {
    if (m_currentMusicIt == m_musicList.begin()) {
        m_currentMusicIt = m_musicList.end();
    }
    --m_currentMusicIt;
    emit currentMusicChanged(*m_currentMusicIt);
    loadMusic(*m_currentMusicIt);
    m_player->play();
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
        setPlayStatus(true);
    } else {
        m_player->pause();
        setPlayStatus(false);
    }
}
