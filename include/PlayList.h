//
// Created by cww on 25-2-23.
//

#ifndef PLAYLIST_H
#define PLAYLIST_H
#include <QSqlDatabase>
#include <QAbstractItemModel>

struct Song{
    QString name;
    QString artist;
    QString album;
    QString path;
};

class PlayListModel : public QAbstractItemModel {
    Q_OBJECT
public:
    explicit PlayListModel(const QList<Song>& musicList, QObject *parent = nullptr);
    void setMusicList(const QList<Song> &musicList);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    QModelIndex index(int row, int column, const QModelIndex &parent) const;

    QModelIndex parent(const QModelIndex &child) const;

    // db
    // db

private:
    int m_row;
    int m_column;
    QList<Song> m_musicList;
};


class PlayList {
public:
    static PlayList *instance() {
        static PlayList playListInstance;
        return &playListInstance;
    }
    PlayList(const PlayList& playList) = delete;
    PlayList& operator=(const PlayList& playList) = delete;

    static QString getMusicNameWithoutPath(const QString& path);
    [[nodiscard]] QString getCurrentMusicName() const;
    QString getCurrentMusicPath();

    void loadMusicFromDirectories(const QStringList& filePathList);
    void loadMusicFromDirectory(const QString& path);
    void setCurrentMusic(int index);
    [[nodiscard]] QList<Song> getMusicList() const;


private:
    PlayList(){}
    int m_currentIndex{0};
    QList<Song> m_musicList{};
};


#endif //PLAYLIST_H
