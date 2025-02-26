//
// Created by cww on 25-2-23.
//

#ifndef PLAYLIST_H
#define PLAYLIST_H
#include <QSqlDatabase>
#include <QAbstractItemModel>

struct Song{
    QString name;
    // QString artist;
    // QString album;
    QString path;
    QString duration;
};



class PlayList {
public:
    static PlayList *instance() {
        static PlayList playListInstance;
        return &playListInstance;
    }
    PlayList(const PlayList& playList) = delete;
    PlayList& operator=(const PlayList& playList) = delete;

    static QString getMusicNameWithoutSuffix(const QString& path);
    [[nodiscard]] QString getCurrentMusicName() const;
    [[nodiscard]] QString getCurrentMusicPath() const;

    void loadMusicFromDirectories(const QStringList& filePathList);
    void loadMusicFromDirectory(const QString& path);
    void setCurrentMusic(int index);
    [[nodiscard]] QList<Song> getMusicList() const;

    QStringList getMusicNameWithoutSuffixList() const;

    static QString convertIntToTime(int minutes, int seconds);
    static QString musicLength(const std::wstring &path);


private:
    PlayList(){}
    int m_currentIndex{0};
    QList<Song> m_musicList{};
};


#endif //PLAYLIST_H
