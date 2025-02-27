//
// Created by cww on 25-2-23.
//
#include "PlayList.h"
#include "taglib/tstring.h"
#include "taglib/fileref.h"
#include <QDir>

QString PlayList::convertSecondsToTime(const int seconds) {
    const int m = seconds / 60;
    const int s = seconds % 60;
    return QString::asprintf("%02d:%02d", m, s);
}

int PlayList::musicLength(const std::wstring &path) {
    if (const TagLib::FileRef f(path.c_str()); !f.isNull() && f.audioProperties()) {
        const TagLib::AudioProperties *properties = f.audioProperties();
        return properties->lengthInSeconds();
    }
    return {};
}


void PlayList::loadMusicFromDirectory(const QString &path) {
    m_musicList.clear();
    const QDir dir(path);
    QStringList files = dir.entryList(QDir::Files);
    for (const auto &file: files) {
        Song song;
        song.path = dir.absoluteFilePath(file);
        song.name = getMusicNameWithoutSuffix(song.path);
        song.duration = musicLength(song.path.toStdWString());
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


QString PlayList::getMusicNameWithoutSuffix(const QString &path) {
    const auto s = path.right(path.size() - path.lastIndexOf("/") - 1);
    return s.left(s.indexOf("."));
}

QString PlayList::getCurrentMusicName() const {
    return getMusicNameWithoutSuffix(m_musicList.at(m_currentIndex).name);
}

QString PlayList::getCurrentMusicPath() const {
    return m_musicList.at(m_currentIndex).path;
}

int PlayList::getCurrentMusicDuration() const {
    return m_musicList.at(m_currentIndex).duration;
}

QStringList PlayList::getMusicNameWithoutSuffixList() const {
    QStringList musicNames;
    for (const auto &it: m_musicList) {
        musicNames.append(it.name);
    }
    return musicNames;
}


int PlayList::getCurrentMusicIndex() const {
    return m_currentIndex;
}

void PlayList::setCurrentMusicIndex(const int index) {
    if (index != m_currentIndex) {
        m_currentIndex = index;
        emit currentMusicIndexChanged(index);
        emit currentMusicNameChanged(getCurrentMusicName());
    }
}

void PlayList::nextMusic() {
    int index = m_currentIndex;
    if (index == m_musicList.size() - 1) {
        index = 0;
    }
    else {
        index++;
    }
    setCurrentMusicIndex(index);
}

void PlayList::previousMusic() {
    int index = m_currentIndex;
    if (index == 0) {
        index = static_cast<int>(m_musicList.size()) - 1;
    }
    else {
        index--;
    }
    setCurrentMusicIndex(index);
}


