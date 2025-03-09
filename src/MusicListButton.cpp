//
// Created by cww on 25-3-6.
//

#include "MusicListButton.h"

#include "Assets.h"
#include <QPushButton>
#include <QStringList>

QList<MusicListButton *> buttons{};

MusicListButton::MusicListButton(QWidget *parent) : QPushButton(parent) {
    setIcon(QIcon(Res::musicListSVG));
    setFixedHeight(25);
    buttons.append(this);
}

QList<Song>& MusicListButton::getMusicList(){
    return songs;
}

void MusicListButton::setMusicList(const QList<Song> &list) {
    if (list.isEmpty()) {
        qDebug() << "Init list for btn, List is empty";
        return;
    }
    for (auto song : list) {
        songs.append(song);
    }
}

void MusicListButton::initListFromDB(const QList<Song> &list) {
    setMusicList(list);
}
