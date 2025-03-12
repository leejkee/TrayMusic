//
// Created by cww on 25-3-6.
//

#include "MusicListButton.h"

#include "Assets.h"
#include <QPushButton>
#include <QStringList>
#include "DBManager.h"

QMap<QString, MusicListButton *> MusicListButton::buttonMap;

MusicListButton::MusicListButton(const QString &name, QWidget *parent) : QPushButton(parent) {
    setIcon(QIcon(Res::musicListSVG));
    setFixedHeight(30);
    setText(name);
    buttonMap.insert(name, this);
}

QList<Song>& MusicListButton::getMusicList(){
    return songs;
}

void MusicListButton::setMusicListFromSongs(const QList<Song> &list) {
    if (list.isEmpty()) {
        qDebug() << "Init list for btn, List is empty";
        return;
    }
    songs.clear();
    songs.append(list);
}

void MusicListButton::setMusicListFromDB(const QString &tableName) {
    this->setMusicListFromSongs(DBManager::instance().getMusicList(tableName));
}


