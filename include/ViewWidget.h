//
// Created by cww on 25-2-19.
//

#ifndef ICONWIDGET_H
#define ICONWIDGET_H
#include <QWidget>

#include "Settings.h"

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
    QWidget *m_topWidget;
Q_SIGNALS:
    void viewDoubleClicked(int index);

private Q_SLOTS:
    void showContextMenu(const QPoint &pos);

    void handleAction(int index);

public Q_SLOTS:
    void viewDoubleClick(const QModelIndex &index);

    void updateCurrentIndex(int index);
};


#endif //ICONWIDGET_H
