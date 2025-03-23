//
// Created by cww on 25-2-19.
//
#ifndef ICONWIDGET_H
#define ICONWIDGET_H
#include "Song.h"
#include <QWidget>
#include <QStyledItemDelegate>

class QPushButton;
class QListView;
class QStringListModel;
class QLabel;
class QPainter;

class PlayListDelegate final : public QStyledItemDelegate {
    Q_OBJECT

public:
    explicit PlayListDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {
    }

protected:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option,
                     const QModelIndex &index) override;

Q_SIGNALS:
    void playButtonClicked(const QModelIndex &index);
};


class ViewWidget final : public QWidget {
    Q_OBJECT

public:
    explicit ViewWidget(QWidget *parent = nullptr);

Q_SIGNALS:
    void signalViewDoubleClicked(int index);

    void signalPlayAllClicked(const QString &name);

private Q_SLOTS:
    void showContextMenu(const QPoint &pos);

    void handleAction(int index);

public Q_SLOTS:
    void viewDoubleClick(const QModelIndex &index);

    void updateCurrentIndex(int index);

    void showMusicList(const QString &listName) const;

    ///
    /// init function
    /// This function will set the default string list (Local Music List) for ViewWidget
    void setDefaultList() const;

    void refreshForLocalMusic() const;

private:
    QLabel *m_labelName;
    QListView *m_playListView;
    QStringListModel *m_playListModel;
    QPushButton *m_playAllButton;

    void createConnections();
};


#endif //ICONWIDGET_H
