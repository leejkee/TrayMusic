//
// Created by cww on 25-2-19.
//
#include <QHBoxLayout>
#include "ViewWidget.h"
#include "PlayList.h"
#include <QListView>
#include <QStringListModel>

ViewWidget::ViewWidget(const QString& list, QWidget *parent): QWidget(parent) {
    PlayList::instance()->loadMusicFromDirectory(list);
    m_playListModel = new QStringListModel(this);
    m_playListModel->setStringList(PlayList::instance()->getMusicNameWithoutSuffixList());
    m_playListView = new QListView(this);
    m_playListView->setModel(m_playListModel);

    QHBoxLayout *iconLayout = new QHBoxLayout;
    iconLayout->addWidget(m_playListView);
    this->setLayout(iconLayout);
}

