//
// Created by cww on 25-2-22.
//

#include "WindowManager.h"

#include <QGroupBox>
#include <QLabel>
#include <QGridLayout>

WindowManager::WindowManager(QWidget *mainWidget, QWidget *parent)
    : QWidget(parent)
, m_mainWidget(mainWidget)
, m_bottomWidget(nullptr)
, m_otherWidget(nullptr)
, m_mainLayout(nullptr)
{
    if (mainWidget == nullptr) {
        qDebug() << "mainWidget is null";
        return;
    }
    QGroupBox *mainGroup = new QGroupBox;
    QGroupBox *bottomGroup = new QGroupBox;
    m_bottomLayout = new QHBoxLayout;
    m_mainLayout = new QGridLayout;
    m_mainLayout->addWidget(m_mainWidget, 0, 0, 1, 1);

    mainGroup->setLayout(m_mainLayout);
    bottomGroup->setLayout(m_bottomLayout);

    QVBoxLayout *Layout = new QVBoxLayout(this);
    Layout->addWidget(mainGroup);
    Layout->addWidget(bottomGroup);
}

WindowManager::~WindowManager() {
    delete m_mainWidget;
    delete m_otherWidget;
    delete m_bottomWidget;
}

void WindowManager::showMainWidget() {
    if (m_otherWidget != nullptr) {
        m_mainLayout->removeWidget(m_otherWidget);
        delete m_otherWidget;
    }
    m_mainLayout->addWidget(m_mainWidget);
}


void WindowManager::showOtherWidget(QWidget *widget) {
    if (widget == nullptr) {
        qDebug() << "other widget is null";
        return;
    }
    if (m_mainLayout->indexOf(m_mainWidget) != -1) {
        m_mainLayout->removeWidget(m_mainWidget);
    }

    m_otherWidget = widget;
    m_mainLayout->addWidget(m_otherWidget, 0, 0, 1, 1);
}

void WindowManager::setBottomWidget(QWidget *widget) {
    if (widget == nullptr) {
        qDebug() << "bottom widget is null";
        return;
    }
    if (m_bottomWidget != nullptr) {
        m_bottomLayout->removeWidget(m_bottomWidget);
        delete m_bottomWidget;
    }
    m_bottomWidget = widget;
    m_bottomLayout->addWidget(m_bottomWidget);
}



