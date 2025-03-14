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
    static PlayList *instance() {
        static PlayList playListInstance;
        return &playListInstance;
    }
    PlayList(const PlayList& playList) = delete;
    PlayList& operator=(const PlayList& playList) = delete;

    [[nodiscard]] QString getCurrentMusicName() const;
    [[nodiscard]] QString getCurrentMusicPath() const;

    [[nodiscard]] int getCurrentMusicDuration() const;

    void loadMusicFromDirectories(const QStringList& filePathList);
    void loadMusicFromDirectory(const QString& path);

    void loadMusicFromDB(const QStringList &fileAbsolutePathList);



    void switchMusicList(const QList<Song> &songs);

    ///
    /// @param path lcoal music paths in settings
    /// @return Song structure
    static QList<Song> getSongListFromDirectories(const QStringList& path);

    ///
    /// @return return the list which contain the music name with no suffix(eg: ".mp3")
    [[nodiscard]] QStringList getMusicNameList() const;

    [[nodiscard]] int getCurrentMusicIndex() const;
    void setCurrentMusicIndex(int index);

    [[nodiscard]] bool isEmpty() const;


Q_SIGNALS:
    void currentMusicIndexChanged(int index);
    void currentMusicNameChanged(const QString& name);


public Q_SLOTS:
    void nextMusic();
    void previousMusic();
    void loadMusicFromSongs(const QList<Song> &songs);


private:
    PlayList(){}
    int m_currentIndex{0};
    QList<Song> m_musicList{};
};


#endif //PLAYLIST_H
