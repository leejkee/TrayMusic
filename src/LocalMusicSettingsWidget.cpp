//
// Created by cww on 25-3-5.
//

#include "Assets.h"
#include "LocalMusicSettingsWidget.h"
#include <QCoreApplication>
#include "Settings.h"
#include <QFileDialog>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>
#include <QSpacerItem>

LocalMusicSettingsWidget::LocalMusicSettingsWidget(QWidget *parent) : QWidget(parent) {
    this->m_addButton = new QPushButton(QIcon(Res::AddSVG), "", this);
    this->m_listWidget = new QListWidget(this);
    this->m_removeButton = new QPushButton(QIcon(Res::RemoveSVG), "", this);
    this->m_messageLabel = new QLabel(this);
    m_messageLabel->setText("Local Music Paths: ");
    m_listWidget->setStyleSheet("QListWidget { font-size: 15px; }");

    const auto hlayout = new QHBoxLayout;
    const auto spaceH = new QSpacerItem(-1, 0, QSizePolicy::Expanding);
    hlayout->addWidget(m_messageLabel);
    hlayout->addItem(spaceH);
    hlayout->addWidget(m_addButton);
    hlayout->addWidget(m_removeButton);

    const auto layout = new QVBoxLayout(this);
    layout->addItem(hlayout);
    layout->addWidget(m_listWidget);
    loadSettings();
    connect(m_addButton, &QPushButton::clicked, this, &LocalMusicSettingsWidget::addMusicPath);
    connect(m_removeButton, &QPushButton::clicked, this, &LocalMusicSettingsWidget::removeMusicPath);
    connect(this, &LocalMusicSettingsWidget::signalAddButton, &Settings::instance(), &Settings::addLocalMusicDirectory);
    connect(this, &LocalMusicSettingsWidget::signalRemoveButton, &Settings::instance(), &Settings::removeMusicDirectory);
}

void LocalMusicSettingsWidget::addMusicPath() {
    const QString newMusicPath = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                                   QCoreApplication::applicationDirPath(),
                                                                   QFileDialog::ShowDirsOnly
                                                                   | QFileDialog::DontResolveSymlinks);
    if (!newMusicPath.isEmpty()) {
        Q_EMIT signalAddButton(newMusicPath);
        // Settings::instance().addMusicDirectory(newMusicPath);
        loadSettings();
    }
}

void LocalMusicSettingsWidget::loadSettings() {
    this->m_listWidget->clear();
    this->m_listWidget->addItems(Settings::instance().getLocalMusicDirectories());
    // PlayList::instance()->loadMusicFromDirectories(Settings::instance().getLocalMusicDirectories());
    Q_EMIT signalLocalMusicPathSettingsChanged();
}

void LocalMusicSettingsWidget::removeMusicPath() {
    const QListWidgetItem *item = this->m_listWidget->currentItem();
    if (!item) {
        qDebug() << "No music path selected";
        return;
    }
    const auto path = item->text();
    Q_EMIT signalRemoveButton(path);
    // Settings::instance().removeMusicDirectory(path);
    loadSettings();
}
