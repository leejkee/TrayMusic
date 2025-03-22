//
// Created by cww on 25-3-6.
//

#include "ListButton.h"
#include <QEvent>
#include "Assets.h"
#include <QPushButton>
#include <QFile>
#include <utility>

ListButton::ListButton(const QString &name, QWidget *parent) : QPushButton(parent) {
    setIcon(QIcon(SvgRes::MusicListSVG));
    setFixedHeight(30);
    setText(name);
    m_listName = name;
    loadStyleSheet(this, QssRes::BUTTON_NORMAL_QSS);
    connect(this, &QPushButton::clicked, this , &ListButton::onButtonClicked);
    installEventFilter(this);
}

ListButton::ListButton(QWidget *parent) : QPushButton(parent) {
    installEventFilter(this);
}

ListButton::ListButton(const QIcon &icon, QWidget *parent, QString name) : QPushButton(parent)
        , m_listName(std::move(name)){
    setIcon(icon);
    loadStyleSheet(this, QssRes::BUTTON_NORMAL_QSS);
    installEventFilter(this);
}


void ListButton::loadStyleSheet(QPushButton* p, const QString &qssPath) {
    if (QFile file(qssPath); file.open(QFile::ReadOnly)) {
        p->setStyleSheet(file.readAll());
        file.close();
    } else {
        qDebug() << "Failed to load QSS file:" << qssPath;
    }
}

bool ListButton::eventFilter(QObject *watched, QEvent *event) {
    if (watched == this) {
        if (event->type() == QEvent::Enter) {
            setCursor(Qt::PointingHandCursor);
        }
        else if (event->type() == QEvent::Leave) {
            setCursor(Qt::ArrowCursor);
        }
    }
    return QPushButton::eventFilter(watched, event);
}
