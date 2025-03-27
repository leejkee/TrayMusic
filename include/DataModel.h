//
// Created by cww on 25-3-26.
//

#ifndef DATAMODELVIEW_H
#define DATAMODELVIEW_H
#include <QAbstractListModel>
#include <QStyledItemDelegate>



class DataModel final : public QAbstractListModel {
public:
    explicit DataModel(QObject *parent = nullptr) : QAbstractListModel(parent) {}

    struct SongInfo {
        QString name;
        QString artist;
        QPixmap logo;
    };
    void setSongs(const QStringList &list);

protected:
    [[nodiscard]] int rowCount(const QModelIndex &parent) const override;

    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;


private:
    QList<SongInfo> m_list{};

    ///
    /// @param str should be the @m_fullName
    /// @return the artist name
    static QString convertToArtist(const QString &str);

    ///
    /// @param str should be the @m_fullName
    /// @return the song name with no suffix "- artist"
    static QString convertToName(const QString &str);
};


class SongDelegate final : public QStyledItemDelegate {
    Q_OBJECT

public:
    explicit SongDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;


    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override {
        Q_UNUSED(index);
        return QSize(200, 60);  // 自定义行高
    }
};


#endif //DATAMODELVIEW_H
