//
// Created by cww on 25-2-19.
//
#include "Assets.h"
#include "PlayerWidget.h"
#include <QCoreApplication>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QSlider>

PlayerWidget::PlayerWidget(QWidget *parent) : QWidget(parent) {
    pushButtonPlay = new QPushButton(QIcon(Res::playIconSVG), "");
    pushButtonPlay->setFixedSize(30, 30);
    labelMusicFileName = new QLabel(QCoreApplication::translate("TrayUI", "Song Name"));
    pushButtonPre = new QPushButton(QIcon(Res::preIconSVG), "");
    pushButtonPre->setFixedSize(30, 30);
    pushButtonNext = new QPushButton(QIcon(Res::nextIconSVG), "");
    pushButtonNext->setFixedSize(30, 30);
    pushButtonPlay->setEnabled(false);
    pushButtonNext->setEnabled(false);
    pushButtonPre->setEnabled(false);
    volumeCtrlButton = new QPushButton(QIcon(Res::volumeSVG), "");
    volumeCtrlButton->setFixedSize(30, 30);

    volumeSlider = new QSlider(Qt::Vertical);
    volumeSlider->setRange(0, 100);
    volumeSlider->setValue(30);

    QVBoxLayout *Layout = new QVBoxLayout;
    QSpacerItem *spaceH = new QSpacerItem(-1, 0, QSizePolicy::Expanding);
    QSpacerItem *spaceV = new QSpacerItem(0, -1, QSizePolicy::Minimum, QSizePolicy::Expanding);
    Layout->addItem(spaceV);
    Layout->addWidget(labelMusicFileName);
    const auto buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(pushButtonPre);
    buttonLayout->addWidget(pushButtonPlay);
    buttonLayout->addWidget(pushButtonNext);
    buttonLayout->addItem(spaceH);
    buttonLayout->addWidget(volumeCtrlButton);
    // buttonLayout->addWidget(volumeSlider);
    Layout->addLayout(buttonLayout);
    this->setLayout(Layout);
}

void PlayerWidget::setPlayButtonIcon(const bool playStatus) {
    if (playStatus) {
        pushButtonPlay->setIcon(QIcon(Res::pauseIconSVG));
    } else {
        pushButtonPlay->setIcon(QIcon(Res::playIconSVG));
    }
}

void PlayerWidget::setVolumeCtrlButtonIcon(const int volume) {
    if (volume != 0) {
        volumeCtrlButton->setIcon(QIcon(Res::volumeSVG));
    }
    else {
        volumeCtrlButton->setIcon(QIcon(Res::volumeMuteSVG));
    }
}

void PlayerWidget::changeMusicName(const QString &name) {
    labelMusicFileName->setText(name);
}

void PlayerWidget::setButtonVisible(const bool b) {
    pushButtonPlay->setEnabled(b);
    pushButtonNext->setEnabled(b);
    pushButtonPre->setEnabled(b);
}


