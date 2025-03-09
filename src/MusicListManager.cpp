//
// Created by cww on 25-2-28.
//
#include "MusicListManager.h"
#include "Assets.h"
#include <QScrollArea>
#include <QVBoxLayout>
#include <QPropertyAnimation>
#include <QInputDialog>
#include "MusicListButton.h"

MusicListManager::MusicListManager(QWidget *parent)
    : QWidget(parent) {
    m_buttonLocalMusic = new MusicListButton(this);
    m_buttonLocalMusic->setText("Local Music");
    m_expandButton = new QPushButton(QIcon(Res::downSVG), "Music List", this);
    m_expandButton->setStyleSheet(R"(
    QPushButton {
        height: 25px;
        width: 80px;
        icon-size: 7px;
        padding: 0;
    })");

    m_addButton = new QPushButton(QIcon(Res::addSVG), "", this);
    m_addButton->setStyleSheet(R"(
    QPushButton {
        width: 25px;
        height: 25px;
        border: none;
        padding: 0;
    })");

    const auto buttonlayout = new QHBoxLayout;
    const auto spaceH = new QSpacerItem(-1, 0, QSizePolicy::Expanding);
    buttonlayout->addWidget(m_expandButton);
    buttonlayout->addItem(spaceH);
    buttonlayout->addWidget(m_addButton);

    m_buttonWidget = new ButtonWidget(this);

    m_scrollArea = new QScrollArea(this);
    m_scrollArea->setWidgetResizable(true);
    m_scrollArea->setFrameShape(QFrame::NoFrame);

    const auto m_mainLayout = new QVBoxLayout;
    const auto spaceV = new QSpacerItem(0, -1, QSizePolicy::Minimum, QSizePolicy::Expanding);
    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    m_mainLayout->setSpacing(0);
    m_mainLayout->addWidget(m_buttonLocalMusic);
    m_mainLayout->addItem(buttonlayout);
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
    setFixedWidth(120);
    createConnections();
}


void MusicListManager::createConnections() {
    connect(m_expandButton, &QPushButton::clicked, this, &MusicListManager::toggleExpand);
    connect(m_addButton, &QPushButton::clicked, m_buttonWidget, &ButtonWidget::addButton);
}


void MusicListManager::toggleExpand() {
    const bool isV = m_buttonWidget->isVisible();
    m_buttonWidget->setVisible(!isV);
    if (!isV) {
        m_expandButton->setIcon(QIcon(Res::upSVG));
    } else {
        m_expandButton->setIcon(QIcon(Res::downSVG));
    }
}


// void MusicListManager::createPlaylist() {
//     bool ok;
//     const QString playlistName = QInputDialog::getText(this,
//                                                         "New a music list",
//                                                         "Music list name:",
//                                                         QLineEdit::Normal,
//                                                         "",
//                                                         &ok);
//     if (ok && !playlistName.isEmpty()) {
//         addPlaylistButton(playlistName);
//         emit playlistCreated(playlistName);
//     }
// }

ButtonWidget::ButtonWidget(QWidget *parent) : QWidget(parent) {
    m_layout = new QVBoxLayout(this);
    MusicListButton *button = new MusicListButton(this);
    m_layout->addWidget(button);
    hide();
}

void ButtonWidget::addButton() {
    qDebug() << "addButton";
    bool ok;
    const QString playlistName = QInputDialog::getText(this,
                                                       "New a music list",
                                                       "Music list name:",
                                                       QLineEdit::Normal,
                                                       "",
                                                       &ok);
    if (ok && !playlistName.isEmpty()) {
        MusicListButton *button = new MusicListButton(this);
        button->setText(playlistName);
        m_layout->addWidget(button);
        Q_EMIT playlistCreated(playlistName);
    }
}
