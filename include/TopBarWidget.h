//
// Created by cww on 25-3-4.
//

#ifndef TOPBARWIDGET_H
#define TOPBARWIDGET_H
#include <QWidget>

class BetterButton;
class QPushButton;
class QSvgWidget;

class TopBarWidget final : public QWidget {
public:
    explicit TopBarWidget(QWidget *parent = nullptr);

    void setPreBtnShow(bool b);

    QSvgWidget *m_svgWidget;
    BetterButton *m_preButton;
    BetterButton *m_settingsButton;

    bool m_preButtonIsVisible = false;
};


#endif //TOPBARWIDGET_H
