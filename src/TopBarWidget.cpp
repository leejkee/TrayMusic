//
// Created by cww on 25-3-4.
//

#include "TopBarWidget.h"

#include <QHBoxLayout>
#include <QPushButton>
#include "Assets.h"

TopBarWidget::TopBarWidget(QWidget *parent) : QWidget(parent) {
    m_logoLabel = new QLabel(this);
    m_logoLabel->setFixedSize(175, 34);
    const QPixmap pixmap(Res::logoSVG);
    m_logoLabel->setPixmap(pixmap.scaledToHeight(34));

    m_preButton = new QPushButton(QIcon(Res::backPageSVG), "",this);
    m_preButton->setStyleSheet("background: transparent; border: none;");
    m_settingsButton = new QPushButton(QIcon(Res::settingSVG), "", this);
    m_settingsButton->setStyleSheet("background: transparent; border: none;");

    // m_preButton->setEnabled(m_preButtonIsVisible);

    const auto spacerH = new QSpacerItem(-1, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    const auto layout = new QHBoxLayout(this);
    layout->addWidget(m_logoLabel);
    layout->addItem(spacerH);
    layout->addWidget(m_preButton);
    layout->addWidget(m_settingsButton);
    setFixedHeight(50);
}

void TopBarWidget::setPreBtnShow(const bool b) {
    m_preButtonIsVisible = b;
    m_preButton->setEnabled(b);
}


