//
// Created by cww on 25-3-5.
//

#include "Assets.h"
#include "SettingsWidget.h"
#include <QCoreApplication>
#include "Settings.h"
#include <QFileDialog>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QPushButton>
#include <QListWidget>
#include <QSpacerItem>
#include "PlayList.h"

SettingsWidget::SettingsWidget(Settings *settings, QWidget *parent) : QWidget(parent) {
    this->m_settings = settings;
    this->m_addBtn = new QPushButton(QIcon(Res::addSVG), "", this);
    this->m_listWidget = new QListWidget(this);
    this->m_removeBtn = new QPushButton(QIcon(Res::removeSVG), "", this);
    this->m_messageLabel = new QLabel(this);
    m_messageLabel->setText("Local Music Paths: ");
    m_listWidget->setStyleSheet("QListWidget { font-size: 15px; }");

    const auto hlayout = new QHBoxLayout;
    const auto spaceH = new QSpacerItem(-1, 0, QSizePolicy::Expanding);
    hlayout->addWidget(m_messageLabel);
    hlayout->addItem(spaceH);
    hlayout->addWidget(m_addBtn);
    hlayout->addWidget(m_removeBtn);

    const auto layout = new QVBoxLayout(this);
    layout->addItem(hlayout);
    layout->addWidget(m_listWidget);
    loadSettings();
    connect(m_addBtn, &QPushButton::clicked, this, &SettingsWidget::addMusicPath);
    connect(m_removeBtn, &QPushButton::clicked, this, &SettingsWidget::removeMusicPath);
}

void SettingsWidget::addMusicPath() {
    const QString newMusicPath = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                                   QCoreApplication::applicationDirPath(),
                                                                   QFileDialog::ShowDirsOnly
                                                                   | QFileDialog::DontResolveSymlinks);
    if (!newMusicPath.isEmpty()) {
        m_settings->addMusicDirectory(newMusicPath);
        loadSettings();
    }
}

void SettingsWidget::loadSettings() {
    this->m_listWidget->clear();
    this->m_listWidget->addItems(m_settings->getMusicDirectories());
    PlayList::instance()->loadMusicFromDirectories(m_settings->getMusicDirectories());
    Q_EMIT musicPathChanged();
}

void SettingsWidget::removeMusicPath() {
    const QListWidgetItem *item = this->m_listWidget->currentItem();
    if (!item) {
        qDebug() << "No music path selected";
        return;
    }
    const auto path = item->text();
    m_settings->removeMusicDirectory(path);
    loadSettings();
}
