//
// Created by cww on 25-3-4.
//

#ifndef TOPBARWIDGET_H
#define TOPBARWIDGET_H
#include <QLabel>
#include <QWidget>

class QPushButton;
class QSvgWidget;

class TopBarWidget final : public QWidget {
public:
    explicit TopBarWidget(QWidget *parent = nullptr);

    void setPreBtnShow(bool b);

    QSvgWidget *m_svgWidget;
    QPushButton *m_preButton;
    QPushButton *m_settingsButton;

    bool m_preButtonIsVisible = false;
};


#endif //TOPBARWIDGET_H
