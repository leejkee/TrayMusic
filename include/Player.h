//
// Created by cww on 25-2-14.
//

#ifndef PLAYER_H
#define PLAYER_H

class QMediaPlayer;
class QAudioOutput;

class Player final : public QObject {
    Q_OBJECT

public:
    Player();

    ~Player() override;

    void loadMusic(const QUrl &mp3Url);

    void volumeUp();

    void volumeDown();

    void volumeSet(float volume);

    void playToggle();

    void muteToggle();

    [[nodiscard]] bool playStatus() const;

private:
    QMediaPlayer *m_player;
    QAudioOutput *m_audioOut;
    bool m_isPlay;
    float m_volume;
Q_SIGNALS:
    void playStatusChanged(bool isPlay);
};
#endif //PLAYER_H
