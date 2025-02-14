//
// Created by cww on 25-2-14.
//

#ifndef PLAYER_H
#define PLAYER_H

class QMediaPlayer;
class QAudioOutput;
class Player
{
  public:
    Player();
    ~Player();

    void loadMusic(const QUrl& mp3Url);
    void volumeUp();
    void volumeDown();
    void volumeSet(float volume);
    void playToggle();
    void muteToggle();
    [[nodiscard]] bool playStatus() const;

  private:
    QMediaPlayer *player;
    QAudioOutput *audioOut;
    bool isPlay;
    float volume;



};
#endif //PLAYER_H
