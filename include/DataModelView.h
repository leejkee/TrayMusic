//
// Created by cww on 25-3-26.
//

#ifndef DATAMODELVIEW_H
#define DATAMODELVIEW_H
#include <QListView>
#include <QAbstractListModel>



class DataModel final : public QAbstractListModel {
public:
    explicit DataModel(QObject *parent = nullptr);

    struct SongInfo {
        QString name;
        QString artist;
        QByteArray logo;
    };

protected:
    [[nodiscard]] int rowCount(const QModelIndex &parent) const override;

    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;


private:
    QList<SongInfo> m_list{};
    void setSongs(const QStringList &list);

    ///
    /// @param str should be the @m_fullName
    /// @return the artist name
    static QString convertToArtist(const QString &str);

    ///
    /// @param str should be the @m_fullName
    /// @return the song name with no suffix "- artist"
    static QString convertToName(const QString &str);
};

class DataView final : public QListView {
};


#endif //DATAMODELVIEW_H
