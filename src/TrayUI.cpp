#include "TrayUI.h"
#include "QMainWindow"
#include <QCheckBox>
#include <QComboBox>
#include <QCoreApplication>
#include <QGroupBox>
#include <QLabel>
#include <QMenu>
#include <QPushButton>
#include <QSystemTrayIcon>
#include <QVBoxLayout>


TrayUI::TrayUI() {
}

/// You should calls the function QMainWindow::setCentralWidget() before you use this function
/// @param parent the pointer to MainWindow
void TrayUI::setupUI(QMainWindow *parent) {
    createIconGroupBox();
    createMessageGroupBox();
    createActions(parent);
    createTrayIconMenu(parent);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(iconGroupBox);
    mainLayout->addWidget(messageGroupBox);
    QWidget* parentPtr = parent->centralWidget();
    if (parentPtr != nullptr) {
        parentPtr->setLayout(mainLayout);
    }
}

// Window::Window() {
//     createIconGroupBox();
//     createMessageGroupBox();
//     createActions();
//     createTrayIconMenu();
//     connect(iconComboBox, &QComboBox::currentIndexChanged, this,
//             &Window::setIcon);
//     connect(this->showIconCheckBox, &QCheckBox::toggled, systemTrayIcon,
//             &QSystemTrayIcon::setVisible);
//
//     centralWidget = new QWidget(this);
//     QVBoxLayout *mainLayout = new QVBoxLayout;
//     mainLayout->addWidget(iconGroupBox);
//     mainLayout->addWidget(messageGroupBox);
//     centralWidget->setLayout(mainLayout);
//     setCentralWidget(centralWidget);
//
//     iconComboBox->setCurrentIndex(1);
//     systemTrayIcon->show();
//     setWindowTitle(tr("Tray"));
// }

void TrayUI::createIconGroupBox() {
    iconGroupBox = new QGroupBox(QCoreApplication::translate("TrayUI", ("Tray Icon")));

    iconLabel = new QLabel(QCoreApplication::translate("TrayUI", ("Icon:")));
    iconComboBox = new QComboBox;
    iconComboBox->addItem(QIcon(":/images/bad.png"), QCoreApplication::translate("TrayUI", ("Bad")));
    iconComboBox->addItem(QIcon(":/images/heart.png"), QCoreApplication::translate("TrayUI", ("Heart")));
    iconComboBox->addItem(QIcon(":/images/trash.png"), QCoreApplication::translate("TrayUI", ("Trash")));
    showIconCheckBox = new QCheckBox(QCoreApplication::translate("TrayUI", "Show icon"));
    showIconCheckBox->setChecked(true);

    QHBoxLayout *iconLayout = new QHBoxLayout;
    iconLayout->addWidget(iconLabel);
    iconLayout->addWidget(iconComboBox);
    iconLayout->addStretch();
    iconLayout->addWidget(showIconCheckBox);
    iconGroupBox->setLayout(iconLayout);
}

void TrayUI::createMessageGroupBox() {
    messageGroupBox = new QGroupBox(QCoreApplication::translate("TrayUI", "Music Player"));
}

void TrayUI::createActions(QWidget* parent) {
    minimizeAction = new QAction(QCoreApplication::translate("TrayUI", "Minimize"), parent);
    maximizeAction = new QAction(QCoreApplication::translate("TrayUI", "Maximize"), parent);
    restoreAction = new QAction(QCoreApplication::translate("TrayUI", "Restore"), parent);
    quitAction = new QAction(QCoreApplication::translate("TrayUI", "Quit"), parent);
}

void TrayUI::createTrayIconMenu(QWidget *parent) {
    trayIconMenu = new QMenu(parent);
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(maximizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    systemTrayIcon = new QSystemTrayIcon(parent);
    systemTrayIcon->setContextMenu(trayIconMenu);

    const auto icon = iconComboBox->itemIcon(iconComboBox->currentIndex());
    systemTrayIcon->setIcon(icon);
    parent->setWindowIcon(icon);
    systemTrayIcon->setToolTip(iconComboBox->itemText(iconComboBox->currentIndex()));
}


