//
// Created by cww on 25-2-23.
//
#include "PlayList.h"
#include "taglib/tag.h"
#include "taglib/fileref.h"
#include <QDir>

void PlayList::loadMusicFromDirectory(const QString &path) {
    m_musicList.clear();
    const QDir dir(path);
    QStringList files = dir.entryList(QDir::Files);
    for (const auto &file: files) {
        const TagLib::FileName fileTagLib{file.toStdString().c_str()};
        TagLib::FileRef f(fileTagLib);
        Song song;
        song.path = dir.absoluteFilePath(file);
        song.name = getMusicNameWithoutPath(song.path);
        // song.artist = QString::fromStdString(f.tag()->artist().to8Bit());
        // song.album = QString::fromStdString(f.tag()->album().to8Bit());
        m_musicList.append(song);
    }
    m_currentIndex = 0;
}

void PlayList::loadMusicFromDirectories(const QStringList &filePathList) {
    m_musicList.clear();
    for (const auto &filePath: filePathList) {
        const QDir dir(filePath);
        QStringList files = dir.entryList(QDir::Files);
        for (const auto &file: files) {
            loadMusicFromDirectory(file);
        }
    }
}


void PlayList::setCurrentMusic(const int index) {
    m_currentIndex = index;
}

QString PlayList::getMusicNameWithoutPath(const QString &path) {
    return path.right(path.size() - path.lastIndexOf("/") - 1);
}

QString PlayList::getCurrentMusicName() const {
    return getMusicNameWithoutPath(m_musicList.at(m_currentIndex).name);
}

QString PlayList::getCurrentMusicPath() {
    return m_musicList.at(m_currentIndex).path;
}

QList<Song> PlayList::getMusicList() const {
    return m_musicList;
}



// PlayListModel
PlayListModel::PlayListModel(const QList<Song>&musicList, QObject *parent) : QAbstractItemModel(parent), m_musicList(musicList) {
    m_row = static_cast<int>(musicList.count());
    m_column = 3;
}

int PlayListModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return m_row;
}

int PlayListModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return m_column;
}

QVariant PlayListModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) {
        return QVariant();
    }

    const Song &song = m_musicList.at(index.row());
    switch (role) {
        case Qt::DisplayRole:
            switch (index.column()) {
                case 0: return song.name;
                case 1: return song.artist;
                case 2: return song.album;
                default: return QVariant();
            }
        default:
            return QVariant();
    }
}

QVariant PlayListModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            switch (section) {
                case 0: return tr("Name");
                case 1: return tr("Artist");
                case 2: return tr("Album");
                default: return QVariant();
            }
        }
    }
    return QVariant();
}

QModelIndex PlayListModel::index(const int row, const int column, const QModelIndex &parent) const {
    if (!hasIndex(row, column, parent)) {
        return QModelIndex();
    }

    return createIndex(row, column);
}
QModelIndex PlayListModel::parent(const QModelIndex &child) const {
    return {};
}
