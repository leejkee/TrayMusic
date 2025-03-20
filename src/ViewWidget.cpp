//
// Created by cww on 25-2-19.
//
#include <QHBoxLayout>
#include "ViewWidget.h"
#include <QLabel>
#include "PlayList.h"
#include <QListView>
#include <QMenu>
#include <QPushButton>
#include <QStringListModel>
#include "Assets.h"
#include "MusicListCache.h"


void ViewWidget::createConnections() {
    connect(m_playListView, &QListView::customContextMenuRequested, this, &ViewWidget::showContextMenu);
    connect(m_playListView, &QListView::doubleClicked, this, &ViewWidget::viewDoubleClick);
    connect(&PlayList::instance(), &PlayList::currentMusicIndexChanged, this, &ViewWidget::updateCurrentIndex);
    connect(m_playAllButton, &QPushButton::clicked, this, [this]() {
        Q_EMIT signalPlayAllClicked(m_labelName->text());
    });
}

ViewWidget::ViewWidget(QWidget *parent): QWidget(parent) {
    m_labelName = new QLabel(this);
    m_playAllButton = new QPushButton(QIcon(Res::PlayIconSVG), User::PLAY_ALL_KEY, this);
    m_playAllButton->setFixedWidth(80);
    const auto spaceH = new QSpacerItem(-1, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    const auto layoutH = new QHBoxLayout;
    layoutH->addWidget(m_playAllButton);
    layoutH->addSpacerItem(spaceH);

    m_playListModel = new QStringListModel(this);
    // init fun
    // m_playListModel->setStringList(PlayList::instance()->getMusicNameWithoutSuffixList());
    m_playListView = new QListView(this);
    m_playListView->setModel(m_playListModel);
    m_playListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_playListView->setContextMenuPolicy(Qt::CustomContextMenu);
    m_playListView->setStyleSheet("QListView { font-size: 15px; }");

    auto *Layout = new QVBoxLayout;
    Layout->addWidget(m_labelName);
    Layout->addItem(layoutH);
    Layout->addWidget(m_playListView);
    this->setLayout(Layout);
    createConnections();
    setDefaultList();
}

void ViewWidget::viewDoubleClick(const QModelIndex &index) {
    qDebug() << "ViewWidget::viewDoubleClick";
    PlayList::instance().setCurrentMusicIndex(index.row());
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


void ViewWidget::showMusicList(const QString &listName) const {
    const auto songNameList = MusicListCache::instance().getSongNameListByName(listName);
    if (songNameList.isEmpty()) {
        qDebug() << "ViewWidget::showMusicList" << "MusicList is empty(MusicListCache::getSongNameListByName)";
        return;
    }
    this->m_playListModel->setStringList(songNameList);
    m_labelName->setText(listName);
}


void ViewWidget::setDefaultList() const {
    showMusicList(User::LOCAL_LIST_KEY);
}


void ViewWidget::refreshForLocalMusic() const {
    if (m_labelName->text() == User::LOCAL_LIST_KEY) {
        showMusicList(User::LOCAL_LIST_KEY);
        qDebug() << "ViewWidget::refreshForLocalMusic";
    }
}
