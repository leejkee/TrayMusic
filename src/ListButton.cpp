//
// Created by cww on 25-3-6.
//

#include "ListButton.h"
#include "Assets.h"
#include <QPushButton>
#include <QFile>

ListButton::ListButton(const QString &name, QWidget *parent) : QPushButton(parent) {
    setIcon(QIcon(SvgRes::MusicListSVG));
    setFixedHeight(30);
    setText(name);
    m_listName = name;
    loadStyleSheet(this, QssRes::BUTTON_NORMAL_QSS);
    connect(this, &QPushButton::clicked, this , &ListButton::onButtonClicked);
}

void ListButton::loadStyleSheet(QPushButton* p, const QString &qssPath) {
    if (QFile file(qssPath); file.open(QFile::ReadOnly)) {
        p->setStyleSheet(file.readAll());
        file.close();
    } else {
        qDebug() << "Failed to load QSS file:" << qssPath;
    }
}

