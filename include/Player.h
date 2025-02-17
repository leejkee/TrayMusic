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
    // Q_PROPERTY(QStringList currentMusic READ currentMusic WRITE setCurrentMusic NOTIFY currentMusicChanged)


public:
    explicit Player(const QStringList &list);

    ~Player() override;

    void loadMusic(const QUrl &mp3Url);

    void volumeUp();

    void volumeDown();

    void volumeSet(float volume);

    void playToggle();

    void muteToggle();

    [[nodiscard]] QString currentMusic() const { return *m_currentMusicIt; };

    [[nodiscard]] bool playStatus() const { return m_isPlay; };

    void setPlayStatus(bool playStatus);

private:
    QMediaPlayer *m_player;
    QAudioOutput *m_audioOut;
    QStringList::iterator m_currentMusicIt;
    // QString m_currentMusic;
    QStringList m_musicList;
    bool m_isPlay;
    float m_volume;

Q_SIGNALS:
    void playStatusChanged(bool isPlay);

    void currentMusicChanged(QString currentMusic);

public Q_SLOTS:
    void nextMusic();

    void previousMusic();
};
#endif //PLAYER_H
