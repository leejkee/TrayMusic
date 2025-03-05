//
// Created by cww on 25-3-4.
//

#include "TopBarWidget.h"

#include <QHBoxLayout>
#include <QPushButton>
#include "Assets.h"
#include <QSvgWidget>

TopBarWidget::TopBarWidget(QWidget *parent) : QWidget(parent) {

    m_svgWidget = new QSvgWidget(Res::logoSVG);
    m_svgWidget->setFixedSize(130, 25);
    m_preButton = new QPushButton(QIcon(Res::backPageSVG), "",this);
    m_preButton->setStyleSheet("background: transparent; border: none;");
    m_settingsButton = new QPushButton(QIcon(Res::settingSVG), "", this);
    m_settingsButton->setStyleSheet("background: transparent; border: none;");

    const auto spacerH = new QSpacerItem(-1, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    const auto layout = new QHBoxLayout(this);
    layout->addWidget(m_svgWidget);
    layout->addItem(spacerH);
    layout->addWidget(m_preButton);
    layout->addWidget(m_settingsButton);
    setFixedHeight(40);
}

void TopBarWidget::setPreBtnShow(const bool b) {
    m_preButtonIsVisible = b;
    m_preButton->setEnabled(b);
}


