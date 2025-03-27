//
// Created by cww on 25-3-26.
//

#include "DataModel.h"

#include <QPainter>

#include "Assets.h"
#include "MusicListCache.h"


void DataModel::setSongs(const QStringList &list) {
    beginResetModel();
    for (const auto &song: list) {
        SongInfo info;
        info.name = convertToName(song);
        info.artist = convertToArtist(song);
        info.logo.loadFromData(MusicListCache::instance().getRandomLogo(), "PNG");
        m_list.append(info);
    }
    endResetModel();
}

int DataModel::rowCount(const QModelIndex &parent) const {
    return parent.isValid() ? 0 : static_cast<int>(m_list.size());
}

QVariant DataModel::data(const QModelIndex &index, const int role) const{
    if (!index.isValid() || index.row() >= m_list.size()) return {};

    const auto &[name, artist, logo] = m_list[index.row()];

    switch (role) {
        case Qt::DisplayRole: return name;    // 歌名
        case Qt::UserRole: return artist;     // 歌手名
        case Qt::DecorationRole: return logo;
        default: return {};
    }
    return {};
}

QString DataModel::convertToArtist(const QString &str) {
    return str.right(str.length() - str.indexOf("-") - 1).trimmed();
}

QString DataModel::convertToName(const QString &str) {
    return str.left(str.indexOf("-"));
}

void SongDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                         const QModelIndex &index) const {
    painter->save();

    QRect rect = option.rect;
    QPixmap cover = index.data(Qt::DecorationRole).value<QPixmap>();
    QString title = index.data(Qt::DisplayRole).toString();
    QString artist = index.data(Qt::UserRole).toString();

    // 设置字体
    QFont titleFont(User::FONT_MIRCRO_HEI, 12, QFont::Normal);
    QFont artistFont("Arial", 9);

    int padding = 10;
    int coverSize = rect.height() - 2 * padding;

    // 绘制背景（如果需要）
    if (option.state & QStyle::State_Selected) {
        painter->fillRect(rect, QColor(200, 200, 255)); // 选中背景颜色
    }

    // 绘制封面
    QRect coverRect(rect.left() + padding, rect.top() + padding, coverSize, coverSize);
    painter->drawPixmap(coverRect, cover);

    // 绘制歌名
    painter->setFont(titleFont);
    painter->drawText(rect.left() + coverSize + 2 * padding, rect.top() + padding + 5, title);

    // 绘制歌手名
    painter->setFont(artistFont);
    painter->setPen(Qt::gray);
    painter->drawText(rect.left() + coverSize + 2 * padding, rect.top() + coverSize / 2 + padding, artist);

    // 绘制右侧按钮
    QRect buttonRect(rect.right() - 60, rect.center().y() - 15, 50, 30);
    painter->setBrush(Qt::blue);
    painter->drawRoundedRect(buttonRect, 5, 5);
    painter->setPen(Qt::white);
    painter->drawText(buttonRect, Qt::AlignCenter, "播放");

    painter->restore();
}
