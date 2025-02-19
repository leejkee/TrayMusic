//
// Created by cww on 25-2-19.
//
#include <QHBoxLayout>
#include <QCheckBox>
#include <QPushButton>
#include <QCoreApplication>
#include "IconWidget.h"

IconWidget::IconWidget(QWidget *parent): QWidget(parent) {
    showIconCheckBox = new QCheckBox(QCoreApplication::translate("TrayUI", "Show icon"));
    showIconCheckBox->setChecked(true);
    pushButtonLoadFile = new QPushButton(QCoreApplication::translate("TrayUI", "Load File"));

    QHBoxLayout *iconLayout = new QHBoxLayout;
    iconLayout->addWidget(showIconCheckBox);
    iconLayout->addStretch();
    iconLayout->addWidget(pushButtonLoadFile);
    this->setLayout(iconLayout);
}
