//
// Created by cww on 25-3-16.
//

#include "MusicListCache.h"
#include <QDirIterator>
#include <QMap>
#include <QDir>
#include "Assets.h"
#include "DBManager.h"
#include "Settings.h"
#include "Utils.h"


QList<Song> MusicListCache::getSongListByName(const QString &listName) const {
    return m_ListMap.value(listName);
}

QStringList MusicListCache::getSongNameListByName(const QString &listName) const {
    if (!m_ListMap.contains(listName)) {
        return {};
    }
    QStringList songName;
    for (const auto &song: m_ListMap.value(listName)) {
        songName.append(song.getName());
    }
    return songName;
}

void MusicListCache::initCache() {
    qDebug() << "MusicListCache: Loading MusicListCache";

    // Local Music cache first
    m_ListMap[User::LOCAL_LIST_KEY] = getSongListFromDirectories(Settings::instance().getLocalMusicDirectories());
    // User
    const auto userList = Settings::instance().getUserMusicList();
    for (const auto &list: userList) {
        m_ListMap[list] = DBManager::instance().getMusicList(list);
    }

    qDebug() << "MusicListCache: load logos";
    QDirIterator it(User::LOGO_PNG_DIR, QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        it.next();
        QFileInfo fileInfo(it.next());
        QString png = fileInfo.absoluteFilePath();
        m_logoPaths.append(png);
    }
}

void MusicListCache::insertList(const QString &list) {
    if (m_ListMap.contains(list)) {
        qDebug() << "[MusicListCache::insert]: " << list << " already exists";
        return;
    }
    m_ListMap[list] = {};
}

void MusicListCache::delList(const QString &list) {
    if (m_ListMap.contains(list)) {
        m_ListMap.remove(list);
    } else {
        qDebug() << "[MusicListCache::del]: ERROR " << "NO " << list;
    }
}

void MusicListCache::reloadLocalMusicList() {
    m_ListMap[User::LOCAL_LIST_KEY] = getSongListFromDirectories(Settings::instance().getLocalMusicDirectories());
}


QList<Song> MusicListCache::getSongListFromDirectories(const QStringList &path) {
    QList<Song> musicList;
    for (const auto &filePath: path) {
        QDirIterator it(filePath, QDir::Files, QDirIterator::Subdirectories);
        while (it.hasNext()) {
            it.next();
            Song song(it.filePath());
            musicList.append(song);
        }
    }
    return musicList;
}

QString MusicListCache::getRandomLogo() const {
    auto it =  Tools::getRandomItem(m_logoPaths);
    if (it.isEmpty()) {
        qDebug() << "[MusicListCache::getRandomLogo]: ERROR " << "NO " << it;
    }
    return it;
}
