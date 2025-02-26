//
// Created by cww on 25-2-23.
//
#include "PlayList.h"
#include "taglib/tstring.h"
#include "taglib/fileref.h"
#include <QDir>

QString PlayList::convertIntToTime(const int minutes, const int seconds) {
    QString m;
    QString s;
    if (minutes >= 0 && minutes < 10) {
        m = QString("0") + QString::number(minutes);
    } else if (minutes >= 10) {
        m = QString::number(minutes);
    }

    if (seconds >= 0 && seconds < 10) {
        s = QString("0") + QString::number(seconds);
    } else if (seconds >= 10) {
        s = QString::number(seconds);
    }
    return m + ":" + s;
}

QString PlayList::musicLength(const std::wstring &path) {
    if (const TagLib::FileRef f(path.c_str()); !f.isNull() && f.audioProperties()) {
        const TagLib::AudioProperties *properties = f.audioProperties();
        const int seconds = properties->lengthInSeconds() % 60;
        const int minutes = (properties->lengthInSeconds() - seconds) / 60;
        return convertIntToTime(minutes, seconds);
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

        // ToDo use QListView? resize the view to full the widget

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

QList<Song> PlayList::getMusicList() const {
    return m_musicList;
}

QStringList PlayList::getMusicNameWithoutSuffixList() const {
    QStringList musicNames;
    for (const auto &it: m_musicList) {
        musicNames.append(it.name);
    }
    return musicNames;
}



