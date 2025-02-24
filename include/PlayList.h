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
    QString duration;
};

class PlayListModel : public QAbstractItemModel {
    Q_OBJECT
public:
    PlayListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    int rowCount;
    int columnCount;
    QVector<Song> rows;
};


class PlayList {
public:
    static PlayList *instance() {
        static PlayList playListInstance;
        return &playListInstance;
    }

    void getCurrentMusicName();
    void getCurrentMusicPath();
    // void loadMusicFromDirectories(const QStringList& filelist);
    void loadMusicFromDirectory(const QString& path);
    void setCurrentMusic(int index);

    // db operate; only functions about "User Music List" call these functions
    void initDB(const QString& dbname);
    QStringList readListFromDB(const QString& listName);
    void saveListToDB(const QStringList& list, const QString& tableName);
    // db operate



private:
    QSqlDatabase m_db;

    int m_currentIndex{0};
    QStringList m_musicList;
    QString m_currentMusic;
};


#endif //PLAYLIST_H
