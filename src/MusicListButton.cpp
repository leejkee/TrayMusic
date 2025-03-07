//
// Created by cww on 25-3-6.
//

#include "MusicListButton.h"
#include "Assets.h"
#include <QPushButton>
#include <QStringList>

MusicListButton::MusicListButton(QWidget *parent) : QPushButton(parent) {
    m_list = new QStringList;
    setIcon(QIcon(Res::musicListSVG));
}

QStringList MusicListButton::getMusicList() const {
    return *m_list;
}

void MusicListButton::setMusicList(const QStringList &list) {
    m_list->clear();
    m_list->append(list);
}
