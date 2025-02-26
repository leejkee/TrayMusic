//
// Created by cww on 25-2-14.
//
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QDir>
#include "Player.h"
#include "PlayList.h"


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
                m_musicPathList.append(dir.absoluteFilePath(file));
            }
        }
        m_currentMusicIt = m_musicPathList.begin();
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
    if (m_currentMusicIt == m_musicPathList.end()) {
        m_currentMusicIt = m_musicPathList.begin();
    }
    ++m_currentMusicIt;
    emit currentMusicChanged(*m_currentMusicIt);
    loadMusic(*m_currentMusicIt);
    m_player->play();
    setPlayStatus(true);
}

void Player::previousMusic() {
    if (m_currentMusicIt == m_musicPathList.begin()) {
        m_currentMusicIt = m_musicPathList.end();
    }
    --m_currentMusicIt;
    emit currentMusicChanged(*m_currentMusicIt);
    loadMusic(*m_currentMusicIt);
    m_player->play();
    setPlayStatus(true);
}

void Player::loadMusic(const QUrl &mp3Url) {
    m_player->setSource(mp3Url);
}

void Player::setVolume(int volume) {
    if (volume > 100) {
        volume = 100;
    }
    else if (volume < 0) {
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

QStringList Player::getMusicList() const {
    QStringList musicList;
    for (const auto& it : m_musicPathList) {
         musicList.append(it.right(it.size() - it.lastIndexOf("/") - 1));
    }
    return musicList;
}

// void Player::muteToggle() {
//     if (m_volume == 0) {
//         setVolume(30);
//     }
//     else {
//         setVolume(0);
//     }
// }