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

    static QString getMusicNameWithoutSuffix(const QString& path);
    [[nodiscard]] QString getCurrentMusicName() const;
    [[nodiscard]] QString getCurrentMusicPath() const;

    void loadMusicFromDirectories(const QStringList& filePathList);
    void loadMusicFromDirectory(const QString& path);
    void setCurrentMusic(int index);
    [[nodiscard]] QList<Song> getMusicList() const;

    /// 
    /// @return return the list which contain the music name with no suffix(eg: ".mp3")
    [[nodiscard]] QStringList getMusicNameWithoutSuffixList() const;

    static QString convertIntToTime(int minutes, int seconds);
    static QString musicLength(const std::wstring &path);

    [[nodiscard]] int getCurrentMusicIndex() const;
    void setCurrentMusicIndex(int index);



Q_SIGNALS:
    void currentMusicIndexChanged(int index);
    void currentMusicNameChanged(const QString& name);


public Q_SLOTS:
    void nextMusic();
    void previousMusic();


private:
    PlayList(){}
    int m_currentIndex{0};
    QList<Song> m_musicList{};
};


#endif //PLAYLIST_H
