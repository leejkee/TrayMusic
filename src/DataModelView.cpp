//
// Created by cww on 25-3-26.
//

#include "DataModelView.h"

#include "MusicListCache.h"
#include "Song.h"


void DataModel::setSongs(const QString &list) {
    beginResetModel();
    for (const auto &song: list) {
        SongInfo info;
        info.name = convertToName(song);
        info.artist = convertToArtist(song);
        info.logo = MusicListCache::instance().getRandomLogo();
        m_list.append(info);
    }
    endResetModel();
}
int DataModel::rowCount(const QModelIndex &parent) const override {
    return parent.isValid() ? 0 : m_list.size();
}

QVariant DataModel::data(const QModelIndex &index, const int role) const override {
    if (!index.isValid() || index.row() >= m_list.size()) return {};

    const auto &[name, artist, logo] = m_list[index.row()];

    switch (role) {
        case Qt::DisplayRole: return name;   // 歌名
        case Qt::UserRole: return artist;     // 歌手名
        case Qt::DecorationRole: return logo; // 图片
        default: ;
    }
    return {};
}
QString DataModel::convertToArtist(const QString &str) {
    return str.right(str.length() - str.indexOf("-") - 1).trimmed();
}

QString DataModel::convertToName(const QString &str) {
    return str.left(str.indexOf("-"));
}
