//
// Created by cww on 25-3-16.
//

#include <QDirIterator>
#include <QDir>
#include <QRandomGenerator>

#include "MusicListCache.h"
#include "Assets.h"
#include "DBManager.h"
#include "Settings.h"


QList<Song> MusicListCache::getSongListByName(const QString &listName) const {
    return m_ListMap.value(listName);
}

QStringList MusicListCache::getSongNameListByName(const QString &listName) const {
    if (!m_ListMap.contains(listName)) {
        return {};
    }
    QStringList songName;
    for (const auto &song: m_ListMap.value(listName)) {
        songName.append(song.getFullName());
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
    QDirIterator it(User::LOGO_PNG_DIR, User::IMAGE_FILTERS, QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        m_logos.append(QPixmap(it.next()));
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
        QDirIterator it(filePath, User::MUSIC_FILTERS, QDir::Files, QDirIterator::Subdirectories);
        while (it.hasNext()) {
            it.next();
            Song song(it.filePath());
            musicList.append(song);
        }
    }
    return musicList;
}

const QPixmap &MusicListCache::getLogo(const qsizetype index) const {
    return m_logos.at(index);
}


qsizetype MusicListCache::getRandomIndex() const{
    static QVector<int> numbers;
    static qsizetype count = 0;
    static std::mt19937 gen(std::random_device{}());

    if (count == 0) {
        numbers.resize(m_logos.size());
        std::iota(numbers.begin(), numbers.end(), 0);
        std::shuffle(numbers.begin(), numbers.end(), gen);
        count = numbers.size();
    }

    const auto number = numbers.back();
    numbers.pop_back();
    count--;
    return number;
}
