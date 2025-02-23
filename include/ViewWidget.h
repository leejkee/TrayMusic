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
class QStringListModel;

class ViewWidget final : public QWidget {

public:
    explicit ViewWidget(QWidget *parent = nullptr);
    void initModel(const QStringList& list);

    QListView *m_playListView;
    QStringListModel *m_playListModel;


};


#endif //ICONWIDGET_H
