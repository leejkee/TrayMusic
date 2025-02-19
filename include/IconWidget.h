//
// Created by cww on 25-2-19.
//

#ifndef ICONWIDGET_H
#define ICONWIDGET_H
#include <QWidget>

class QGroupBox;
class QPushButton;
class QCheckBox;

class IconWidget final : public QWidget {

public:
    explicit IconWidget(QWidget *parent = nullptr);

    QPushButton *pushButtonLoadFile;
    QCheckBox* showIconCheckBox;

};


#endif //ICONWIDGET_H
