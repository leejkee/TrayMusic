//
// Created by cww on 25-2-23.
//
#include "PlayList.h"
#include "Song.h"
#include <QString>
#include <QDirIterator>
#include "MusicListCache.h"
#include "Assets.h"

void PlayList::loadMusicFromDirectory(const QString &path) {
    m_musicList.clear();
    const QDir dir(path);
    QStringList files = dir.entryList(QDir::Files);
    for (const auto &file: files) {
        Song song(dir.absoluteFilePath(file));
        m_musicList.append(song);
    }
    m_currentIndex = User::UNINITIALIZED_VALUE;
}

void PlayList::loadMusicFromUserList(const QStringList &fileAbsolutePathList) {
    m_musicList.clear();
    for (const auto &file: fileAbsolutePathList) {
        Song song(file);
        m_musicList.append(song);
    }
    m_currentIndex = User::UNINITIALIZED_VALUE;
}

void PlayList::loadMusicFromSongs(const QList<Song> &songs) {
    m_musicList.clear();
    m_musicList = songs;
}

void PlayList::switchMusicList(const QList<Song> &songs) {
    loadMusicFromSongs(songs);
}

void PlayList::loadMusicFromDirectories(const QStringList &filePathList) {
    m_musicList.clear();
    for (const auto &filePath: filePathList) {
        QDirIterator it(filePath, QDir::Files, QDirIterator::Subdirectories);
        while (it.hasNext()) {
            it.next();
            Song song(it.filePath());
            m_musicList.append(song);
        }
    }
    m_currentIndex = User::UNINITIALIZED_VALUE;
}


QString PlayList::getCurrentMusicName() const {
    return m_musicList.at(m_currentIndex).getFullName();
}


QString PlayList::getCurrentMusicPath() const {
    if (isEmptyPlayList()) {
        qDebug() << "PlayList::getCurrentMusicPath() is empty";
        return {};
    }
    return m_musicList.at(m_currentIndex).getPath();
}


QString PlayList::getFirstMusicPath() const {
    if (isEmptyPlayList()) {
        qDebug() << "PlayList::getFirstMusicPath() is empty";
        return {};
    }
    return m_musicList.begin()->getPath();
}


int PlayList::getCurrentMusicDuration() const {
    return m_musicList.at(m_currentIndex).getDuration();
}


QStringList PlayList::getMusicNameList() const {
    QStringList musicNames;
    for (const auto &it: m_musicList) {
        musicNames.append(it.getFullName());
    }
    return musicNames;
}

int PlayList::getCurrentMusicIndex() const {
    return m_currentIndex;
}

void PlayList::setCurrentMusicIndex(const int index) {
    if (index != m_currentIndex) {
        m_currentIndex = index;
        Q_EMIT currentMusicIndexChanged(index);
        Q_EMIT currentMusicNameChanged(getCurrentMusicName());
    }
}

void PlayList::nextMusic() {
    int index = m_currentIndex;
    if (index == m_musicList.size() - 1) {
        index = 0;
    } else {
        index++;
    }
    setCurrentMusicIndex(index);
}

void PlayList::previousMusic() {
    int index = m_currentIndex;
    if (index == 0) {
        index = static_cast<int>(m_musicList.size()) - 1;
    } else {
        index--;
    }
    setCurrentMusicIndex(index);
}


bool PlayList::isEmptyPlayList() const {
    return m_musicList.isEmpty();
}

void PlayList::loadMusicByName(const QString &name) {
    loadMusicFromSongs(MusicListCache::instance().getSongListByName(name));
}

void PlayList::playMusicListByName(const QString &name) {
    if (isEmptyPlayList()) {
        qDebug() << "PlayList::playMusicListByName() is empty, load list by name";
        loadMusicFromSongs(MusicListCache::instance().getSongListByName(name));
    }
    playFromFirst();
}


void PlayList::playFromFirst() {
    setCurrentMusicIndex(0);
    Q_EMIT currentMusicIndexChanged(0);
    Q_EMIT currentMusicNameChanged(getCurrentMusicName());
}

void PlayList::playStatusCtrl() {
}
