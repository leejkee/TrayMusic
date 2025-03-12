//
// Created by cww on 25-2-19.
//

#ifndef ICONWIDGET_H
#define ICONWIDGET_H

#include "Song.h"
#include <QWidget>

class QGroupBox;
class QPushButton;
class QCheckBox;
class QListView;
class QTableView;
class QStringListModel;
class PlayListModel;


class ViewWidget final : public QWidget {
    Q_OBJECT

public:
    explicit ViewWidget(QWidget *parent = nullptr);

    QListView *m_playListView;
    QStringListModel *m_playListModel;
    QPushButton *m_playAllButton;

Q_SIGNALS:
    void viewDoubleClicked(int index);

private Q_SLOTS:
    void showContextMenu(const QPoint &pos);

    void handleAction(int index);

    void loadMusicStringFromData(const QList<Song> &list);

public Q_SLOTS:
    void viewDoubleClick(const QModelIndex &index);

    void updateCurrentIndex(int index);

    void reloadModel();
};


#endif //ICONWIDGET_H
