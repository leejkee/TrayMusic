//
// Created by cww on 25-2-28.
//
#include "MusicListManager.h"
#include "Assets.h"
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QPropertyAnimation>
#include <QInputDialog>

MusicListManager::MusicListManager(QWidget *parent)
    : QWidget(parent) {
    m_expandButton = new QPushButton(QIcon(Res::downSVG), "Lists", this);
    m_expandButton->setFixedWidth(60);
    m_expandButton->setStyleSheet(R"(
    QPushButton {
        height: 25px;
        background-color: #ffffff;
        icon-size: 7px;
        padding: 0;
    })");
    connect(m_expandButton, &QPushButton::clicked, this, &MusicListManager::toggleExpand);

    m_addButton = new QPushButton(QIcon(Res::adddSVG), "", this);
    m_addButton->setStyleSheet(R"(
    QPushButton {
        width: 10px;
        height: 10px;
        border-radius: 5px;
        background-color: #f5f5f5;
        border: none;
        padding: 0;
    })");
    connect(m_addButton, &QPushButton::clicked, this, &MusicListManager::createPlaylist);

    QHBoxLayout *btnlayout = new QHBoxLayout(this);
    btnlayout->setSpacing(0);
    btnlayout->setContentsMargins(0, 0, 0, 0);
    btnlayout->addWidget(m_expandButton);
    auto spaceH = new QSpacerItem(-1, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    btnlayout->addItem(spaceH);
    btnlayout->addWidget(m_addButton);
    QWidget *btnWidget = new QWidget(this);
    btnWidget->setLayout(btnlayout);

    m_buttonContainerWidget = new QWidget(this);
    m_buttonLayout = new QVBoxLayout(m_buttonContainerWidget);
    m_buttonLayout->setSpacing(0);
    m_buttonLayout->setContentsMargins(0, 0, 0, 0);
    m_buttonContainerWidget->hide();

    m_scrollArea = new QScrollArea(this);
    m_scrollArea->setWidgetResizable(true);
    m_scrollArea->setFrameShape(QFrame::NoFrame);

    m_mainLayout = new QVBoxLayout;
    auto spaceV = new QSpacerItem(0, -1, QSizePolicy::Minimum, QSizePolicy::Expanding);
    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    m_mainLayout->setSpacing(0);
    m_mainLayout->addWidget(btnWidget);
    m_mainLayout->addWidget(m_buttonContainerWidget);
    m_mainLayout->addItem(spaceV);

    QWidget *mainWidget = new QWidget(this);
    mainWidget->setLayout(m_mainLayout);
    m_scrollArea->setWidget(mainWidget);
    m_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(m_scrollArea);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    setLayout(layout);
    setFixedWidth(100);
}


void MusicListManager::toggleExpand() {
    const bool isV = m_buttonContainerWidget->isVisible();
    m_buttonContainerWidget->setVisible(!isV);
    if (!isV) {
        m_expandButton->setIcon(QIcon(Res::upSVG));
    } else {
        m_expandButton->setIcon(QIcon(Res::downSVG));
    }
}


void MusicListManager::createPlaylist() {
    bool ok;
    QString playlistName = QInputDialog::getText(this, "New a music list", "Music list name:", QLineEdit::Normal, "",
                                                 &ok);
    if (ok && !playlistName.isEmpty()) {
        addPlaylistButton(playlistName);
        emit playlistCreated(playlistName);
    }
}

void MusicListManager::addPlaylistButton(const QString &name) {
    QPushButton *playlistButton = new QPushButton(name, this);
    m_buttonsVector.append(playlistButton);
    m_buttonLayout->addWidget(playlistButton);
}


void MusicListManager::removePlaylistButton(const int index) {
    const auto button = m_buttonsVector.at(index);
    m_buttonsVector.removeAt(index);
    m_buttonLayout->removeWidget(button);
    delete button;
}