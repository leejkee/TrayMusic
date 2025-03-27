//
// Created by cww on 25-2-19.
//
#include <QHBoxLayout>
#include <QApplication>
#include <QLabel>
#include <QListView>
#include <QMenu>
#include <QStringListModel>
#include <QPainter>
#include <QMouseEvent>

#include "ViewWidget.h"
#include "PlayList.h"
#include "Assets.h"
#include "MusicListCache.h"
#include "BetterButton.h"
#include "DataModel.h"
#include "Utils.h"

// void PlayListDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
//                              const QModelIndex &index) const {
//     if (!index.isValid()) return;
//
//     // 获取文本数据
//     const QString text = index.data(Qt::DisplayRole).toString();
//
//
//     // 计算按钮区域
//     const QRect buttonRect(option.rect.right() - 50, option.rect.top() + User::VIEW_BUTTON_PADDING, 25,
//                            option.rect.height() -
//                            User::VIEW_BUTTON_PADDING * 2);
//
//     // 绘制背景（选中状态）
//     if (option.state & QStyle::State_Selected) {
//         QPalette palette = option.palette;
//         palette.setColor(QPalette::Highlight, Qt::gray);
//         painter->fillRect(option.rect, palette.highlight());
//     }
//
//     // image
//     // const QRect imgRect (option.rect.left(), option.rect.top() +(option.rect.height() - 35) / 2 , 35, 35);
//     // const auto fileP = MusicListCache::instance().getRandomLogo();
//     // if (QPixmap pixmap(fileP); !pixmap.isNull()) {
//     //     pixmap = pixmap.scaled(38, 38, Qt::KeepAspectRatio, Qt::SmoothTransformation);
//     //     painter->drawPixmap(imgRect, pixmap);
//     // }
//     // 绘制文本
//     // painter->drawText(nameRect, Qt::AlignLeft, getName(text));
//     // painter->drawText(artistRect, Qt::AlignLeft, getArtist(text));
//     painter->save();
//     const QFont nameFont("", 12);
//     painter->setFont(nameFont);
//     const QRect nameRect = option.rect.adjusted(35, 2, -50, -20);
//     painter->drawText(nameRect, Qt::AlignLeft | Qt::AlignTop, text);
//     // 恢复 QPainter 状态
//     painter->restore();
//
//     // 设置歌手名的字体
//     painter->save();
//     const QFont artistFont("Arial", 9);
//     painter->setFont(artistFont);
//     const QRect artistRect = option.rect.adjusted(65, 22, -50, -2);
//     painter->drawText(artistRect, Qt::AlignLeft | Qt::AlignTop, text);
//     painter->restore();
//
//     // 绘制按钮
//     QStyleOptionButton button;
//     button.rect = buttonRect;
//     button.icon = QIcon(SvgRes::PlayIconSVG);
//     button.state = QStyle::State_Enabled;
//     QApplication::style()->drawControl(QStyle::CE_PushButton, &button, painter);
// }
//





void ViewWidget::createConnections() {
    connect(m_playListView, &QListView::customContextMenuRequested, this, &ViewWidget::showContextMenu);
    connect(m_playListView, &QListView::doubleClicked, this, &ViewWidget::viewDoubleClick);
    connect(&PlayList::instance(), &PlayList::currentMusicIndexChanged, this, &ViewWidget::updateCurrentIndex);
    connect(m_playAllButton, &QPushButton::clicked, this, [this]() {
        Q_EMIT signalPlayAllClicked(m_labelName->text());
    });
    connect(m_songDelegate, &SongDelegate::playButtonClicked, this, &ViewWidget::viewDoubleClick);
}

ViewWidget::ViewWidget(QWidget *parent): QWidget(parent) {
    m_labelName = new QLabel(this);
    m_playAllButton = new BetterButton(QIcon(SvgRes::PlayIconSVG), this, User::PLAY_ALL_KEY);
    m_playAllButton->setFixedWidth(80);

    const auto spaceH = new QSpacerItem(-1, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    const auto layoutH = new QHBoxLayout;
    layoutH->addWidget(m_playAllButton);
    layoutH->addSpacerItem(spaceH);

    // m_playListModel = new QStringListModel(this);
    m_dataModel = new DataModel(this);
    m_songDelegate = new SongDelegate(this);

    // init fun
    // m_playListModel->setStringList(PlayList::instance()->getMusicNameWithoutSuffixList());
    m_playListView = new QListView(this);
    m_playListView->setModel(m_dataModel);
    m_playListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_playListView->setContextMenuPolicy(Qt::CustomContextMenu);
    m_playListView->setStyleSheet(Tools::readQSS(QssRes::LIST_VIEW_QSS));


    // Delegate Func
    // m_viewItemDelegate = new PlayListDelegate(this);
    // m_playListView->setItemDelegate(m_viewItemDelegate);
    m_playListView->setItemDelegate(m_songDelegate);

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
    if (PlayList::instance().isEmptyPlayList()) {
        qDebug() << "List is not loaded, PlayList is empty, load music first";
        qDebug() << "Q_EMIT ViewWidget::signalPlayAllClicked to load PlayList";
        if (m_labelName) {
            Q_EMIT signalPlayAllClicked(m_labelName->text());
        } else {
            qDebug() << "m_labelName is nullptr!";
        }
    }
    // Then, check music to play this song
    PlayList::instance().setCurrentMusicIndex(index.row());
}

void ViewWidget::updateCurrentIndex(const int index) {
    qDebug() << "ViewWidget::updateCurrentIndex";
    // m_playListView->selectionModel()->select(m_playListModel->index(index, 0), QItemSelectionModel::ClearAndSelect);
    m_playListView->selectionModel()->select(m_dataModel->index(index, 0), QItemSelectionModel::ClearAndSelect);
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
    }
    // this->m_playListModel->setStringList(songNameList);
    m_dataModel->setSongs(songNameList);
    m_labelName->setText(listName);
}

void ViewWidget::setDefaultList() const {
    showMusicList(User::LOCAL_LIST_KEY);
}


void ViewWidget::refreshForLocalMusic() const {
    if (m_labelName->text() == User::LOCAL_LIST_KEY) {
        showMusicList(User::LOCAL_LIST_KEY);
        PlayList::instance().loadMusicByName(m_labelName->text());
        qDebug() << "ViewWidget::refreshForLocalMusic";
    }
}
