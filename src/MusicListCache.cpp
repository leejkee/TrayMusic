//
// Created by cww on 25-3-16.
//

#include "MusicListCache.h"
#include <QMap>
#include "Assets.h"
#include "DBManager.h"
#include "PlayList.h"
#include "Settings.h"


QList<Song> MusicListCache::getSongListByName(const QString &listName) const{
    return m_ListMap.value(listName);
}

QStringList MusicListCache::getSongNameListByName(const QString &listName) const {
    if (!m_ListMap.contains(listName)) {
        return {};
    }
    QStringList songName;
    for (const auto &song : m_ListMap.value(listName)) {
        songName.append(song.getName());
    }
    return songName;
}

void MusicListCache::load() {
    qDebug() << "Loading MusicListCache";

    // Local Music cache first
    m_ListMap[User::LOCAL_LIST_KEY] = PlayList::getSongListFromDirectories(Settings::instance().getLocalMusicDirectories());
    // User
    const auto userList = Settings::instance().getUserMusicList();
    for (const auto &list : userList) {
        m_ListMap[list] = DBManager::instance().getMusicList(list);
    }
}

void MusicListCache::insert(const QString &list) {
    if (m_ListMap.contains(list)) {
        qDebug() << "[MusicListCache::insert]: " << list << " already exists";
        return;
    }
    m_ListMap[list] = {};
}

void MusicListCache::del(const QString &list) {
    if (m_ListMap.contains(list)) {
        m_ListMap.remove(list);
    }
    else {
        qDebug() << "[MusicListCache::del]: ERROR " << "NO " << list;
    }
}

void MusicListCache::reloadLocalMusicList() {
    m_ListMap[User::LOCAL_LIST_KEY] = PlayList::getSongListFromDirectories(Settings::instance().getLocalMusicDirectories());
}