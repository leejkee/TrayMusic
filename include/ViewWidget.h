//
// Created by cww on 25-2-19.
//

#ifndef ICONWIDGET_H
#define ICONWIDGET_H
#include <QWidget>

class QGroupBox;
class QPushButton;
class QCheckBox;
class QListView;
class QTableView;
class QStringListModel;
class PlayListModel;

class ViewWidget final : public QWidget {

public:
    explicit ViewWidget(QWidget *parent = nullptr) : QWidget(parent), m_playListView(nullptr), m_playListModel(nullptr) {}
    explicit ViewWidget(const QString &list, QWidget *parent = nullptr);

    QListView *m_playListView;
    QStringListModel *m_playListModel;
};


#endif //ICONWIDGET_H
