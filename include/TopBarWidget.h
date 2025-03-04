//
// Created by cww on 25-3-4.
//

#ifndef TOPBARWIDGET_H
#define TOPBARWIDGET_H
#include <QLabel>
#include <QWidget>

class QPushButton;

class TopBarWidget final : public QWidget {
public:
    explicit TopBarWidget(QWidget *parent = nullptr);

    void setPreBtnShow(bool b);

    QLabel *m_logoLabel;
    QPushButton *m_preButton;
    QPushButton *m_settingsButton;

    bool m_preButtonIsVisible = false;
};


#endif //TOPBARWIDGET_H
