//
// Created by cww on 25-2-19.
//
#include <QHBoxLayout>
#include "ViewWidget.h"
#include "PlayList.h"
#include <QListView>
#include <QMenu>
#include <QStringListModel>


ViewWidget::ViewWidget(QWidget *parent): QWidget(parent) {
    m_playListModel = new QStringListModel(this);
    m_playListModel->setStringList(PlayList::instance()->getMusicNameWithoutSuffixList());
    m_playListView = new QListView(this);
    m_playListView->setModel(m_playListModel);
    m_playListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_playListView->setContextMenuPolicy(Qt::CustomContextMenu);
    m_playListView->setStyleSheet("QListView { font-size: 15px; }");
    connect(m_playListView, &QListView::customContextMenuRequested, this, &ViewWidget::showContextMenu);
    connect(m_playListView, &QListView::doubleClicked, this, &ViewWidget::viewDoubleClick);
    connect(PlayList::instance(), &PlayList::currentMusicIndexChanged, this, &ViewWidget::updateCurrentIndex);
    QHBoxLayout *Layout = new QHBoxLayout;
    Layout->addWidget(m_playListView);
    this->setLayout(Layout);
}


void ViewWidget::viewDoubleClick(const QModelIndex &index) {
    qDebug() << "ViewWidget::viewDoubleClick";
    PlayList::instance()->setCurrentMusicIndex(index.row());
}

void ViewWidget::updateCurrentIndex(const int index) {
    qDebug() << "ViewWidget::updateCurrentIndex";
    m_playListView->selectionModel()->select(m_playListModel->index(index, 0), QItemSelectionModel::ClearAndSelect);
}

void ViewWidget::showContextMenu(const QPoint &pos) {
    qDebug() << "ViewWidget::showContextMenu";
    const QModelIndex index = m_playListView->indexAt(pos);
    if (!index.isValid()) {
        return;
    }
    auto clickedRow = index.row();
    QMenu *menu = new QMenu(this);
    QAction *action = menu->addAction(tr("Playlist"));
    connect(action, &QAction::triggered, this, [clickedRow, this]() {
        handleAction(clickedRow);
    });
    connect(menu, &QMenu::aboutToHide, menu, &QMenu::deleteLater);
    menu->exec(m_playListView->viewport()->mapToGlobal(pos));
}

void ViewWidget::handleAction(const int index) {
    qDebug() << "ViewWidget::handleAction" << index;
}

void ViewWidget::reloadModel() {
    qDebug() << "ViewWidget::reloadModel";
    this->m_playListModel->setStringList(PlayList::instance()->getMusicNameWithoutSuffixList());
}