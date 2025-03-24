//
// Created by cww on 25-2-19.
//
#include <QHBoxLayout>
#include "ViewWidget.h"

#include <QApplication>
#include <QLabel>
#include "PlayList.h"
#include <QListView>
#include <QMenu>
#include <QStringListModel>
#include "Assets.h"
#include "ListButton.h"
#include "MusicListCache.h"
#include <QPainter>
#include <QMouseEvent>

void PlayListDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                             const QModelIndex &index) const {
    if (!index.isValid()) return;

    // 获取文本数据
    const QString text = index.data(Qt::DisplayRole).toString();

    // 计算按钮区域
    const QRect buttonRect(option.rect.right() - 50, option.rect.top() + User::VIEW_BUTTON_PADDING, 25,
                           option.rect.height() -
                           User::VIEW_BUTTON_PADDING * 2);

    // 绘制背景（选中状态）
    if (option.state & QStyle::State_Selected) {
        painter->fillRect(option.rect, option.palette.highlight());
    }

    // 绘制文本
    painter->drawText(option.rect.adjusted(5, User::VIEW_TEXT_PADDING, -50, -User::VIEW_TEXT_PADDING),
                      Qt::AlignVCenter | Qt::AlignLeft,
                      text);

    // 绘制按钮
    QStyleOptionButton button;
    button.rect = buttonRect;
    button.icon = QIcon(SvgRes::PlayIconSVG);
    button.state = QStyle::State_Enabled;
    QApplication::style()->drawControl(QStyle::CE_PushButton, &button, painter);
}

bool PlayListDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option,
                                   const QModelIndex &index) {
    if (!index.isValid()) return false;

    // 计算按钮区域
    const QRect buttonRect(option.rect.right() - 50, option.rect.top() + User::VIEW_BUTTON_PADDING, 25,
                           option.rect.height() -
                           User::VIEW_BUTTON_PADDING * 2);

    if (event->type() == QEvent::MouseButtonPress || event->type() == QEvent::MouseButtonRelease) {
        if (const auto *mouseEvent = dynamic_cast<QMouseEvent *>(event); buttonRect.contains(mouseEvent->pos())) {
            if (event->type() == QEvent::MouseButtonRelease) {
                emit playButtonClicked(index);
            }
            return true; // 表示事件已处理
        }
    }
    return false;
}

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
    m_playAllButton = new ListButton(this);
    m_playAllButton->setText(User::PLAY_ALL_KEY);
    m_playAllButton->setIcon(QIcon(SvgRes::PlayIconSVG));
    m_playAllButton->setFixedWidth(80);
    ListButton::loadStyleSheet(m_playAllButton, QssRes::BUTTON_NORMAL_QSS);
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
    // m_playListView->setStyleSheet("QListView { font-size: 12px; }");
    PlayListDelegate *playListDelegate = new PlayListDelegate(this);
    m_playListView->setItemDelegate(playListDelegate);
    connect(playListDelegate, &PlayListDelegate::playButtonClicked, this, &ViewWidget::viewDoubleClick);
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
        qDebug() << "PlayList is empty";
        qDebug() << "Q_EMIT ViewWidget::signalPlayAllClicked to load PlayList";
        Q_EMIT signalPlayAllClicked(m_labelName->text());
    }
    // Then, check music to play this song
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
