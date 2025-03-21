//
// Created by cww on 25-2-14.
//

#ifndef PLAYER_H
#define PLAYER_H

class QMediaPlayer;
class QAudioOutput;

class Player final : public QObject {
    Q_OBJECT
    Q_PROPERTY(bool playStatus READ playStatus WRITE setPlayStatus NOTIFY playStatusChanged)
    Q_PROPERTY(int volume READ getVolume WRITE setVolume NOTIFY volumeChanged)

public:
    explicit Player();

    ~Player() override;

    void playMusic();

    [[nodiscard]] float getVolume() const;

    [[nodiscard]] bool playStatus() const { return m_isPlay; };

private:
    QMediaPlayer *m_player;
    QAudioOutput *m_audioOut;

    bool m_isPlay;
    float m_volume;
    void setPlayStatus(bool playStatus);

Q_SIGNALS:
    void playStatusChanged(bool isPlay);

    void volumeChanged(int volume);

    void playPositionChanged(qint64 position);

    void playMusicEnd();

public Q_SLOTS:

    void setVolume(int volume);
    void playToggle();
    void changeSource();
    void setPlayPosition(qint64 position);
};
#endif //PLAYER_H
