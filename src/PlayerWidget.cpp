//
// Created by cww on 25-2-19.
//
#include "Assets.h"
#include "PlayerWidget.h"
#include <QCoreApplication>
#include <QPushButton>
#include <QLabel>
#include <QMenu>
#include <QVBoxLayout>
#include <QSlider>
#include <QStackedLayout>
#include <QWidgetAction>
#include <QToolButton>

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

    // VolumeCtrl Section Begin
    volumeWidget = new VolumeWidget(this);
    pushButtonVolume = new QPushButton(this);
    pushButtonVolume->setIcon(QIcon(Res::volumeSVG));
    pushButtonVolume->setFixedSize(30, 30);
    menuVolume = new QMenu(this);
    QWidgetAction *action = new QWidgetAction(this);
    action->setDefaultWidget(volumeWidget);
    menuVolume->addAction(action);
    pushButtonVolume->setStyleSheet("QToolButton::menu-indicator { image: none !important; }");
    connect(pushButtonVolume, &QPushButton::clicked, this, [this]() {
        show();
    });
    // VolumeCtrl Section End

    QVBoxLayout *Layout = new QVBoxLayout;
    QSpacerItem *spaceH = new QSpacerItem(-1, 0, QSizePolicy::Expanding);
    // QSpacerItem *spaceV = new QSpacerItem(0, -1, QSizePolicy::Minimum, QSizePolicy::Expanding);
    // Layout->addItem(spaceV);
    Layout->addWidget(labelMusicFileName);
    const auto buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(pushButtonPre);
    buttonLayout->addWidget(pushButtonPlay);
    buttonLayout->addWidget(pushButtonNext);
    buttonLayout->addItem(spaceH);
    buttonLayout->addWidget(pushButtonVolume);
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
        pushButtonVolume->setIcon(QIcon(Res::volumeSVG));
        volumeWidget->buttonMute->setIcon(QIcon(Res::volumeSVG));
    } else {
        pushButtonVolume->setIcon(QIcon(Res::volumeMuteSVG));
        volumeWidget->buttonMute->setIcon(QIcon(Res::volumeMuteSVG));
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


VolumeWidget::VolumeWidget(QWidget *parent) : QWidget(parent) {
    sliderV = new QSlider(this);
    sliderV->setRange(0, 100);
    sliderV->setValue(30);
    labelVolume = new QLabel(this);
    labelVolume->setText("30%");
    labelVolume->setStyleSheet("font-size: 7pt;");
    labelVolume->setAlignment(Qt::AlignCenter);
    connect(sliderV, &QSlider::valueChanged, labelVolume, [=]() {
        labelVolume->setText(QString("%1%").arg(sliderV->value()));
    });
    buttonMute = new QPushButton(QIcon(Res::volumeSVG), "", this);
    buttonMute->setIconSize(QSize(10, 10));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(sliderV);
    layout->addWidget(labelVolume);
    layout->addWidget(buttonMute);
    layout->setContentsMargins(5, 5, 0, 0);
    setLayout(layout);
    this->setFixedSize(30, 100);
}

void PlayerWidget::show() {
    if (menuVolume->isVisible()) {
        menuVolume->hide();
        qDebug() << "Menu hide";
    } else {
        QPoint pos = pushButtonVolume->mapToGlobal(QPoint(0, 0));
        pos.setY(pos.y() - menuVolume->sizeHint().height());
        pos.setX(pos.x() - 5);
        menuVolume->popup(pos);
        qDebug() << "Menu show";
    }
}
