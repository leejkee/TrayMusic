//
// Created by cww on 25-3-26.
//

#include "DataModel.h"
#include <qabstractitemview.h>
#include <QMouseEvent>
#include <QPainter>
#include <QSvgRenderer>
#include <QListView>
#include "Assets.h"
#include "MusicListCache.h"


void DataModel::setSongs(const QStringList &list) {
    beginResetModel();
    m_list.clear();
    for (const auto &song: list) {
        SongInfo info;
        info.name = convertToName(song);
        info.artist = convertToArtist(song);
        info.logoIndex = MusicListCache::instance().getRandomIndex();
        m_list.append(info);
    }
    endResetModel();
}

int DataModel::rowCount(const QModelIndex &parent) const {
    return parent.isValid() ? 0 : static_cast<int>(m_list.size());
}

QVariant DataModel::data(const QModelIndex &index, const int role) const {
    if (!index.isValid() || index.row() >= m_list.size()) return {};
    const auto &[name, artist, logoIndex] = m_list[index.row()];
    switch (role) {
        case Qt::DisplayRole: return name;
        case Qt::UserRole: return artist;
        case Qt::DecorationRole: return MusicListCache::instance().getLogo(logoIndex);
        default: return {};
    }
}

QString DataModel::convertToArtist(const QString &str) {
    return str.right(str.length() - str.indexOf("-") - 1).trimmed();
}

QString DataModel::convertToName(const QString &str) {
    return str.left(str.indexOf("-"));
}


SongDelegate::SongDelegate(QObject *parent) : QStyledItemDelegate(parent) {

    connect(this, &SongDelegate::signalPreviousIndexChanged, this, [this](const int index) {
    if (auto *view = qobject_cast<QListView*>(this->parent())) {
        qDebug() << "Song index: " << index;
        // 更新新旧索引对应的项
        if (m_previousIndex >= 0) {
            view->update(view->model()->index(m_previousIndex, 0));
        }
        if (index >= 0) {
            view->update(view->model()->index(index, 0));
        }
    }
});

    connect(this, &SongDelegate::signalPlayingStatusChanged, this, [this](const bool b) {
        qDebug() << "signalPlayingStatusChanged emitted. b =" << b
         << "m_previousIndex =" << m_previousIndex;
        Q_UNUSED(b);
        if (auto *view = qobject_cast<QListView*>(this->parent())) {
            // 更新当前播放索引对应的项
            if (m_previousIndex >= 0) {
                qDebug() << "signalPlayingStatusChanged:" << m_previousIndex;
                view->update(view->model()->index(m_previousIndex, 0));
            }
        }
    });
}

void SongDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                         const QModelIndex &index) const {
    painter->save();
    // painter->setRenderHint(QPainter::Antialiasing);
    // painter->setRenderHint(QPainter::TextAntialiasing);
    const QRect rect = option.rect;
    const auto cover = index.data(Qt::DecorationRole).value<QPixmap>();
    const QString title = index.data(Qt::DisplayRole).toString();
    const QString artist = index.data(Qt::UserRole).toString();
    // 设置字体
    const QFont titleFont(ViewConfig::FONT_MIRC_HEI, 12, QFont::Normal);
    // const QFont btnFont(ViewConfig::FONT_MIRC_HEI, 15, QFont::Normal);
    const QFont artistFont(ViewConfig::FONT_MIRC_HEI, 9);

    const int coverSize = rect.height() - 2 * ViewConfig::VIEW_LOGO_PADDING;

    // 绘制背景（如果需要）
    if (option.state & QStyle::State_Selected) {
        painter->fillRect(rect, QColor(224, 224, 224)); // 选中背景颜色
    }

    // 绘制封面
    painter->drawPixmap(rect.left() + ViewConfig::VIEW_LOGO_PADDING * 6, rect.top() + ViewConfig::VIEW_LOGO_PADDING,
                        coverSize, coverSize, cover);

    // 绘制歌名
    painter->setFont(titleFont);
    painter->drawText(rect.left() + coverSize + 8 * ViewConfig::VIEW_LOGO_PADDING,
                      rect.top() + ViewConfig::VIEW_LOGO_PADDING * 4, title);

    // 绘制歌手名
    painter->setFont(artistFont);
    painter->setPen(Qt::gray);
    painter->drawText(rect.left() + coverSize + 8 * ViewConfig::VIEW_LOGO_PADDING,
                      rect.top() + ViewConfig::VIEW_LOGO_PADDING * 7, artist);

    // 绘制Play/pause
    const QRect buttonRect(rect.left() + ViewConfig::VIEW_LOGO_PADDING,
                           rect.center().y() - ViewConfig::VIEW_BUTTON_SIZE / 2,
                           ViewConfig::VIEW_BUTTON_SIZE,
                           ViewConfig::VIEW_BUTTON_SIZE);

    static QSvgRenderer svgPlayingRenderer(SvgRes::ViewPlaySVG);
    static QSvgRenderer svgPauseRenderer(SvgRes::ViewPauseSVG);

    if (index.row() != m_previousIndex) {
        svgPlayingRenderer.render(painter, buttonRect);
    } else {
        if (m_isPlaying) {
            svgPauseRenderer.render(painter, buttonRect);
        } else {
            svgPlayingRenderer.render(painter, buttonRect);
        }
    }

    painter->restore();
}

bool DataModel::setData(const QModelIndex &index, const QVariant &value, const int role) {
    if (!index.isValid())
        return false;

    switch (role) {
        case Qt::DisplayRole: m_list[index.row()].name = value.toString();
            break;
        case Qt::UserRole: m_list[index.row()].artist = value.toString();
            break;
        default: break;
    }
    return QAbstractListModel::setData(index, value, role);
}

bool SongDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option,
                               const QModelIndex &index) {
    if (!index.isValid()) return false;

    // 计算按钮区域
    const QRect buttonRect(option.rect.left() + ViewConfig::VIEW_LOGO_PADDING,
                           option.rect.center().y() - ViewConfig::VIEW_BUTTON_SIZE / 2,
                           ViewConfig::VIEW_BUTTON_SIZE,
                           ViewConfig::VIEW_BUTTON_SIZE);

    if (event->type() == QEvent::MouseButtonPress || event->type() == QEvent::MouseButtonRelease) {
        if (const auto *mouseEvent = dynamic_cast<QMouseEvent *>(event); buttonRect.contains(mouseEvent->pos())) {
            if (event->type() == QEvent::MouseButtonRelease) {
                if (index.row() == m_previousIndex) {
                    m_isPlaying = !m_isPlaying;
                    Q_EMIT signalPlayToggle();
                } else {
                    m_previousIndex = index.row();
                    Q_EMIT signalViewPlayButtonClick(index.row());
                }
            }
            return true;
        }
    }
    return false;
}

void SongDelegate::setPreviousIndex(const int index) {
    if (index != m_previousIndex) {
        m_previousIndex = index;
        Q_EMIT signalPreviousIndexChanged(index);
    }
}

void SongDelegate::setPlayStatus(const bool playable) {
    if (playable != m_isPlaying) {
        qDebug() << "SongDelegate::setPlayStatus" << playable;
        m_isPlaying = playable;
        Q_EMIT signalPlayingStatusChanged(playable);
    }
}