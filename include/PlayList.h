//
// Created by cww on 25-2-23.
//

#ifndef PLAYLIST_H
#define PLAYLIST_H
#include "Song.h"
#include <QObject>


class PlayList final: public QObject {
    Q_OBJECT
    Q_PROPERTY(int currentMusicIndex READ getCurrentMusicIndex WRITE setCurrentMusicIndex NOTIFY currentMusicIndexChanged)
public:
    static PlayList &instance() {
        static PlayList playListInstance;
        return playListInstance;
    }
    PlayList(const PlayList& playList) = delete;
    PlayList& operator=(const PlayList& playList) = delete;

    [[nodiscard]] QString getCurrentMusicName() const;
    [[nodiscard]] QString getCurrentMusicPath() const;
    [[nodiscard]] QString getFirstMusicPath() const;
    [[nodiscard]] int getCurrentMusicDuration() const;

    void loadMusicFromDirectories(const QStringList& filePathList);
    void loadMusicFromDirectory(const QString& path);
    void loadMusicFromUserList(const QStringList &fileAbsolutePathList);
    void switchMusicList(const QList<Song> &songs);

    ///
    /// @return return the list which contain the music name with no suffix(eg: ".mp3")
    [[nodiscard]] QStringList getMusicNameList() const;

    [[nodiscard]] int getCurrentMusicIndex() const;
    void setCurrentMusicIndex(int index);

    [[nodiscard]] bool isEmptyPlayList() const;


Q_SIGNALS:
    void currentMusicIndexChanged(int index);
    void currentMusicNameChanged(const QString& name);


public Q_SLOTS:
    void nextMusic();
    void previousMusic();
    void loadMusicByName(const QString& name);
    void playMusicListByName(const QString &name);


private:
    PlayList(){}
    int m_currentIndex{0};
    QList<Song> m_musicList{};
    void playFromFirst();

    void playStatusCtrl();

    void loadMusicFromSongs(const QList<Song> &songs);
};


#endif //PLAYLIST_H
