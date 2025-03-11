//
// Created by cww on 25-2-23.
//

#ifndef PLAYLIST_H
#define PLAYLIST_H
#include <QSqlDatabase>
#include <QAbstractItemModel>

struct Song{
    QString name;
    QString path;
    int duration{};

    Song() = default;
    Song(QString name, QString path, const int duration) : name(std::move(name)), path(std::move(path)), duration(duration) {}
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

    [[nodiscard]] int getCurrentMusicDuration() const;

    void loadMusicFromDirectories(const QStringList& filePathList);
    void loadMusicFromDirectory(const QString& path);
    void loadMusicFromDB(const QStringList &fileAbsolutePathList);

    void loadMusicFromSongs(const QList<Song> &songs);

    ///
    /// @param path lcoal music paths in settings
    /// @return Song structure
    static QList<Song> loadSongsFromDirectories(const QStringList& path);

    ///
    /// @return return the list which contain the music name with no suffix(eg: ".mp3")
    [[nodiscard]] QStringList getMusicNameWithoutSuffixList() const;

    /// 
    /// @param seconds the length of mp3
    /// @return <QString> "00:00" style
    static QString convertSecondsToTime(int seconds);

    ///
    /// @param path mp3 file path
    /// @return <int> the length of mp3
    static int musicLength(const QString &path);

    [[nodiscard]] int getCurrentMusicIndex() const;
    void setCurrentMusicIndex(int index);

    [[nodiscard]] bool isEmpty() const;


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
