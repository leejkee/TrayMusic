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
    m_pushButtonPlay = new QPushButton(QIcon(Res::playIconSVG), "");
    m_pushButtonPlay->setFixedSize(30, 30);
    m_labelMusicFileName = new QLabel(QCoreApplication::translate("TrayUI", "Song Name"));
    m_pushButtonPre = new QPushButton(QIcon(Res::preIconSVG), "");
    m_pushButtonPre->setFixedSize(30, 30);
    m_pushButtonNext = new QPushButton(QIcon(Res::nextIconSVG), "");
    m_pushButtonNext->setFixedSize(30, 30);
    m_pushButtonPlay->setEnabled(false);
    m_pushButtonNext->setEnabled(false);
    m_pushButtonPre->setEnabled(false);

    // VolumeCtrl Section Begin
    m_volumeWidget = new VolumeWidget(this);
    m_pushButtonVolume = new QPushButton(this);
    m_pushButtonVolume->setIcon(QIcon(Res::volumeSVG));
    m_pushButtonVolume->setFixedSize(30, 30);
    m_menuVolume = new QMenu(this);
    QWidgetAction *action = new QWidgetAction(this);
    action->setDefaultWidget(m_volumeWidget);
    m_menuVolume->addAction(action);
    m_pushButtonVolume->setStyleSheet("QToolButton::menu-indicator { image: none !important; }");
    connect(m_pushButtonVolume, &QPushButton::clicked, this, [this]() {
        show();
    });
    // VolumeCtrl Section End

    QVBoxLayout *Layout = new QVBoxLayout;
    QSpacerItem *spaceH = new QSpacerItem(-1, 0, QSizePolicy::Expanding);
    Layout->addWidget(m_labelMusicFileName);
    const auto buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(m_pushButtonPre);
    buttonLayout->addWidget(m_pushButtonPlay);
    buttonLayout->addWidget(m_pushButtonNext);
    buttonLayout->addItem(spaceH);
    buttonLayout->addWidget(m_pushButtonVolume);
    Layout->addLayout(buttonLayout);
    this->setLayout(Layout);
}


void PlayerWidget::setPlayButtonIcon(const bool playStatus) {
    if (playStatus) {
        m_pushButtonPlay->setIcon(QIcon(Res::pauseIconSVG));
    } else {
        m_pushButtonPlay->setIcon(QIcon(Res::playIconSVG));
    }
}

void PlayerWidget::setVolumeCtrlButtonIcon(const int volume) {
    if (volume != 0) {
        m_pushButtonVolume->setIcon(QIcon(Res::volumeSVG));
        m_volumeWidget->m_buttonMute->setIcon(QIcon(Res::volumeSVG));
    } else {
        m_pushButtonVolume->setIcon(QIcon(Res::volumeMuteSVG));
        m_volumeWidget->m_buttonMute->setIcon(QIcon(Res::volumeMuteSVG));
    }
}

void PlayerWidget::changeMusicName(const QString &name) {
    m_labelMusicFileName->setText(name);
}

void PlayerWidget::setButtonVisible(const bool b) {
    m_pushButtonPlay->setEnabled(b);
    m_pushButtonNext->setEnabled(b);
    m_pushButtonPre->setEnabled(b);
}


VolumeWidget::VolumeWidget(QWidget *parent) : QWidget(parent) {
    m_sliderV = new QSlider(this);
    m_sliderV->setRange(0, 100);
    m_sliderV->setValue(30);
    m_labelVolume = new QLabel(this);
    m_labelVolume->setText("30%");
    m_labelVolume->setStyleSheet("font-size: 7pt;");
    m_labelVolume->setAlignment(Qt::AlignCenter);
    connect(m_sliderV, &QSlider::valueChanged, m_labelVolume, [=]() {
        m_labelVolume->setText(QString("%1%").arg(m_sliderV->value()));
    });
    m_buttonMute = new QPushButton(QIcon(Res::volumeSVG), "", this);
    m_buttonMute->setIconSize(QSize(10, 10));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_sliderV);
    layout->addWidget(m_labelVolume);
    layout->addWidget(m_buttonMute);
    layout->setContentsMargins(5, 5, 0, 0);
    setLayout(layout);
    this->setFixedSize(30, 100);
}

void PlayerWidget::show() {
    if (m_menuVolume->isVisible()) {
        m_menuVolume->hide();
        qDebug() << "Menu hide";
    } else {
        QPoint pos = m_pushButtonVolume->mapToGlobal(QPoint(0, 0));
        pos.setY(pos.y() - m_menuVolume->sizeHint().height());
        pos.setX(pos.x() - 5);
        m_menuVolume->popup(pos);
        qDebug() << "Menu show";
    }
}
