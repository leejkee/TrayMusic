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
    explicit Player(const QStringList &list);

    ~Player() override;

    void loadMusic(const QUrl &mp3Url);

    void setVolume(int volume);
    [[nodiscard]] float getVolume() const;

    void playToggle();


    [[nodiscard]] QString currentMusic() const {
        return m_currentMusicIt->right(
            m_currentMusicIt->size() - m_currentMusicIt->lastIndexOf("/") - 1);
    };

    [[nodiscard]] bool playStatus() const { return m_isPlay; };

    void setPlayStatus(bool playStatus);

private:
    QMediaPlayer *m_player;
    QAudioOutput *m_audioOut;
    QStringList::iterator m_currentMusicIt;
    QStringList m_musicList;
    bool m_isPlay;
    float m_volume;

Q_SIGNALS:
    void playStatusChanged(bool isPlay);

    void currentMusicChanged(QString currentMusic);

    void volumeChanged(int volume);

public Q_SLOTS:
    void nextMusic();

    void previousMusic();

    // void muteToggle();
};
#endif //PLAYER_H
