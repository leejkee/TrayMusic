//
// Created by cww on 25-2-19.
//
#include <QHBoxLayout>
#include "ViewWidget.h"
#include "PlayList.h"
#include <QTableView>

ViewWidget::ViewWidget(const QString& list, QWidget *parent): QWidget(parent) {
    initModel(list);
    m_playListView = new QTableView(this);
    m_playListView->setModel(m_playListModel);

    QHBoxLayout *iconLayout = new QHBoxLayout;
    iconLayout->addWidget(m_playListView);
    this->setLayout(iconLayout);
}

void ViewWidget::initModel(const QString& list) {
    PlayList::instance()->loadMusicFromDirectory(list);
    m_playListModel = new PlayListModel(PlayList::instance()->getMusicList(), this);
}
