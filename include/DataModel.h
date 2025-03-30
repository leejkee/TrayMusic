//
// Created by cww on 25-3-26.
//

#ifndef DATAMODELVIEW_H
#define DATAMODELVIEW_H
#include <QStyledItemDelegate>
#include <QAbstractListModel>

class DataModel final : public QAbstractListModel {
public:
    explicit DataModel(QObject *parent = nullptr) : QAbstractListModel(parent){
    }

    struct SongInfo {
        QString name;
        QString artist;
        qsizetype logoIndex;
    };

    void setSongs(const QStringList &list);

protected:
    [[nodiscard]] int rowCount(const QModelIndex &parent) const override;

    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

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
    explicit SongDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    void setPreviousIndex(int index);

    void setPlayStatus(bool playable);

protected:
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option,
                     const QModelIndex &index) override;


Q_SIGNALS:
    void signalViewPlayButtonClick(int);

    void signalPlayToggle();

    void signalPreviousIndexChanged(int);

    void signalPlayingStatusChanged(bool);

private:
    int m_previousIndex;
    bool m_isPlaying;
};


#endif //DATAMODELVIEW_H
