//
// Created by cww on 25-3-6.
//

#include "MusicListButton.h"

#include "Assets.h"
#include <QPushButton>
#include <QStringList>
#include "DBManager.h"


MusicListButton::MusicListButton(const QString &name, QWidget *parent) : QPushButton(parent) {
    setIcon(QIcon(Res::musicListSVG));
    setFixedHeight(30);
    setText(name);
    m_listName = name;
    connect(this, &QPushButton::clicked, this , &MusicListButton::onButtonClicked);
}

const QList<Song> &MusicListButton::getMusicList() const{
    return m_songs;
}

void MusicListButton::setMusicListFromSongs(const QList<Song> &list) {
    if (list.isEmpty()) {
        qDebug() << "Init list for btn, List is empty";
        // return;
    }
    m_songs.clear();
    m_songs.append(list);
}

void MusicListButton::setMusicListFromDB(const QString &tableName) {
    this->setMusicListFromSongs(DBManager::instance().getMusicList(tableName));
}


