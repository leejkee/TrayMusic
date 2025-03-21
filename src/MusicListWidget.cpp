//
// Created by cww on 25-2-28.
//
#include "MusicListWidget.h"
#include "Assets.h"
#include <QScrollArea>
#include <QVBoxLayout>
#include <QPropertyAnimation>
#include <QInputDialog>
#include "DBManager.h"
#include "ListButton.h"
#include "Settings.h"

MusicListWidget::MusicListWidget(QWidget *parent)
    : QWidget(parent) {
    // todo
    m_localListButton = new ListButton(User::LOCAL_LIST_KEY);
    m_expandButton = new QPushButton(QIcon(Res::DownSVG), "List", this);
    m_expandButton->setStyleSheet(R"(
    QPushButton {
        height: 30px;
        width: 60px;
        icon-size: 7px;
        padding: 0;
    })");

    m_addButton = new QPushButton(QIcon(Res::AddSVG), "", this);
    m_addButton->setStyleSheet(R"(
    QPushButton {
        width: 30px;
        height: 30px;
        border: none;
        padding: 0;
    })");

    const auto buttonLayout = new QHBoxLayout;
    const auto spaceH = new QSpacerItem(-1, 0, QSizePolicy::Expanding);
    buttonLayout->addWidget(m_expandButton);
    buttonLayout->addWidget(m_addButton);
    buttonLayout->addItem(spaceH);

    m_buttonWidget = new QWidget(this);
    m_buttonLayout = new QVBoxLayout(m_buttonWidget);

    m_scrollArea = new QScrollArea(this);
    m_scrollArea->setWidgetResizable(true);
    m_scrollArea->setFrameShape(QFrame::NoFrame);

    const auto m_mainLayout = new QVBoxLayout;
    const auto spaceV = new QSpacerItem(0, -1, QSizePolicy::Minimum, QSizePolicy::Expanding);
    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    m_mainLayout->setSpacing(0);
    m_mainLayout->addWidget(m_localListButton);
    m_mainLayout->addItem(buttonLayout);
    m_mainLayout->addWidget(m_buttonWidget);
    m_mainLayout->addItem(spaceV);

    const auto mainWidget = new QWidget(this);
    mainWidget->setLayout(m_mainLayout);
    m_scrollArea->setWidget(mainWidget);
    m_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    const auto layout = new QVBoxLayout;
    layout->addWidget(m_scrollArea);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    setLayout(layout);
    setFixedWidth(110);
    createConnections();
    initUserListButtons();
}

void MusicListWidget::createConnections() {
    connect(m_localListButton, &ListButton::signalButtonClicked, this, &MusicListWidget::handleMusicButtonClicked);
    connect(m_expandButton, &QPushButton::clicked, this, &MusicListWidget::toggleExpand);
    connect(m_addButton, &QPushButton::clicked, this, &MusicListWidget::addButton);
}


void MusicListWidget::toggleExpand() {
    const bool isV = m_buttonWidget->isVisible();
    m_buttonWidget->setVisible(!isV);
    if (!isV) {
        m_expandButton->setIcon(QIcon(Res::UpSVG));
    } else {
        m_expandButton->setIcon(QIcon(Res::DownSVG));
    }
}


void MusicListWidget::addButton() {
    qDebug() << "buttonWidget addButton";
    bool ok;
    const QString playlistName = QInputDialog::getText(this,
                                                       "New a music list",
                                                       "Music list name:",
                                                       QLineEdit::Normal,
                                                       "",
                                                       &ok);
    if (ok && !playlistName.isEmpty()) {
        newButton(playlistName);
        Q_EMIT signalMusicListButtonAdded(playlistName);
    }
}

void MusicListWidget::newButton(const QString &playlistName) {
    auto *button = new ListButton(playlistName, this);
    m_buttonLayout->addWidget(button);
    // button->setMusicListFromSongs(DBManager::instance().getMusicList(playlistName));
    // if no key, inserts a default-constructed value into the map
    connect(button, &ListButton::signalButtonClicked, this, &MusicListWidget::handleMusicButtonClicked);
}



void MusicListWidget::initUserListButtons() {
    const auto listName = Settings::instance().getUserMusicList();
    for (const auto &name: listName) {
        newButton(name);
    }
}


void MusicListWidget::handleMusicButtonClicked(const QString &name) {
    qDebug() << "buttonWidget handleMusicButtonClicked";
    Q_EMIT signalMusicListButtonClicked(name);
}

