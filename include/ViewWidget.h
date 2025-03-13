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
class QLabel;


class ViewWidget final : public QWidget {
    Q_OBJECT

public:
    explicit ViewWidget(QWidget *parent = nullptr);


Q_SIGNALS:
    void viewDoubleClicked(int index);

private Q_SLOTS:
    void showContextMenu(const QPoint &pos);

    void handleAction(int index);


public Q_SLOTS:
    void viewDoubleClick(const QModelIndex &index);

    void updateCurrentIndex(int index);

    void reloadModel();

    void init();

    void playAllButtonClicked(const QString &name, const QList<Song> &list);

private:
    QLabel *m_labelName;
    QListView *m_playListView;
    QStringListModel *m_playListModel;
    QPushButton *m_playAllButton;
    void loadMusicStringFromData(const QList<Song> &list);
};


#endif //ICONWIDGET_H
