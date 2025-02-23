//
// Created by cww on 25-2-19.
//
#include <QHBoxLayout>
#include <QStringListModel>
#include <QListView>
#include "ViewWidget.h"

ViewWidget::ViewWidget(QWidget *parent): QWidget(parent) {
    m_playListModel = new QStringListModel(this);
    m_playListView = new QListView(this);
    m_playListView->setModel(m_playListModel);

    QHBoxLayout *iconLayout = new QHBoxLayout;
    iconLayout->addWidget(m_playListView);
    this->setLayout(iconLayout);
}

void ViewWidget::initModel(const QStringList& list) {
    m_playListModel->setStringList(list);
}
