//
// Created by cww on 25-3-6.
//

#include "ListButton.h"
#include "Assets.h"
#include <QPushButton>
#include <QStringList>

ListButton::ListButton(const QString &name, QWidget *parent) : QPushButton(parent) {
    setIcon(QIcon(Res::MusicListSVG));
    setFixedHeight(30);
    setText(name);
    m_listName = name;
    connect(this, &QPushButton::clicked, this , &ListButton::onButtonClicked);
}

