//
// Created by cww on 25-2-14.
//
#include <QMediaPlayer>
#include <QAudioOutput>
#include "Player.h"
#include <QFileDialog>

Player::Player()
    : player(new QMediaPlayer)
      , audioOut(new QAudioOutput)
      , isPlay(false)
      , volume(0.3) {
    player->setAudioOutput(audioOut);
    audioOut->setVolume(volume);
}

Player::~Player() {
    delete player;
    delete audioOut;
}

void Player::loadMusic(const QUrl &mp3Url) {
    player->setSource(mp3Url);
}

void Player::volumeUp() {
    volume = (volume == 1 ? 1 : (volume + static_cast<float>(0.2)));
    audioOut->setVolume(volume);
}

void Player::volumeDown() {
    volume = (volume == 0 ? 0 : (volume - static_cast<float>(0.2)));
    audioOut->setVolume(volume);
}

void Player::volumeSet(const float volume) {
    audioOut->setVolume(volume);
}

void Player::muteToggle() {
    if (volume == 0) {
        volumeUp();
        return;
    }
    volume = 0;
    volumeSet(volume);
}


void Player::playToggle() {
    if (isPlay == true) {
        player->play();
        isPlay = false;
    } else {
        player->pause();
        isPlay = true;
    }
}

bool Player::playStatus() const {
    return this->isPlay;
}
