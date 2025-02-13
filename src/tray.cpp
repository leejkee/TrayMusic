#include "tray.h"

#include <QApplication>
#include <QCheckBox>
#include <QComboBox>
#include <QCoreApplication>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QMenu>
#include <QPushButton>
#include <QSpinBox>
#include <QSystemTrayIcon>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QCloseEvent>
#include <QMessageBox>


Window::Window() {
    createIconGroupBox();
    createMessageGroupBox();
    createActions();
    createTrayIconMenu();
    iconLabel->setMinimumWidth(durationLabel->sizeHint().width());
    connect(iconComboBox, &QComboBox::currentIndexChanged, this,
            &Window::setIcon);
    connect(showMessageButton, &QPushButton::clicked, this,
            &Window::showMessage);
    connect(this->showIconCheckBox, &QCheckBox::toggled, systemTrayIcon,
            &QSystemTrayIcon::setVisible);

    centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(iconGroupBox);
    mainLayout->addWidget(messageGroupBox);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    iconComboBox->setCurrentIndex(1);
    systemTrayIcon->show();
    setWindowTitle(tr("Tray"));
}

void Window::createIconGroupBox() {
    iconGroupBox = new QGroupBox(tr("Tray Icon"));

    iconLabel = new QLabel(tr("Icon:"));
    iconComboBox = new QComboBox;
    iconComboBox->addItem(QIcon(":/images/bad.png"), tr("Bad"));
    iconComboBox->addItem(QIcon(":/images/heart.png"), tr("Heart"));
    iconComboBox->addItem(QIcon(":/images/trash.png"), tr("Trash"));
    showIconCheckBox = new QCheckBox(tr("Show icon"));
    showIconCheckBox->setChecked(true);

    QHBoxLayout *iconLayout = new QHBoxLayout;
    iconLayout->addWidget(iconLabel);
    iconLayout->addWidget(iconComboBox);
    iconLayout->addStretch();
    iconLayout->addWidget(showIconCheckBox);
    iconGroupBox->setLayout(iconLayout);
}

void Window::createMessageGroupBox() {
    messageGroupBox = new QGroupBox(tr("Balloon Message"));

    messageTypeLabel = new QLabel(tr("Message type:"));
    messageTypeComboBox = new QComboBox;
    messageTypeComboBox->addItem(tr("None"), QSystemTrayIcon::NoIcon);
    messageTypeComboBox->addItem(
        style()->standardIcon(QStyle::SP_MessageBoxInformation),
        tr("Information"), QSystemTrayIcon::Information);
    messageTypeComboBox->addItem(
        style()->standardIcon(QStyle::SP_MessageBoxWarning), tr("Warning"),
        QSystemTrayIcon::Warning);
    messageTypeComboBox->addItem(
        style()->standardIcon(QStyle::SP_MessageBoxCritical), tr("Critical"),
        QSystemTrayIcon::Critical);
    messageTypeComboBox->addItem(QIcon(), tr("Custom icon"), -1);
    messageTypeComboBox->setCurrentIndex(1);

    durationLabel = new QLabel(tr("Duration:"));
    durationSpinBox = new QSpinBox;
    durationSpinBox->setRange(5, 60);
    durationSpinBox->setSuffix(tr(" s"));
    durationSpinBox->setValue(15);
    durationInfo = new QLabel(tr("(some systems might ignore this hint)"));
    durationInfo->setIndent(10);

    titleLabel = new QLabel(tr("Title:"));
    titleEdit = new QLineEdit(tr("Cannot connect to network"));

    bodyLabel = new QLabel(tr("Body:"));
    bodyEdit = new QTextEdit;
    bodyEdit->setPlainText("Hello World");

    showMessageButton = new QPushButton(tr("Show Message"));
    // default buttons decide which button is clicked when user press enter
    showMessageButton->setDefault(true);

    QGridLayout *messageLayout = new QGridLayout;
    messageLayout->addWidget(messageTypeLabel, 0, 0);
    messageLayout->addWidget(messageTypeComboBox, 0, 1, 1, 2);
    messageLayout->addWidget(durationLabel, 1, 0);
    messageLayout->addWidget(durationSpinBox, 1, 1);
    messageLayout->addWidget(durationInfo, 1, 2, 1, 3);
    messageLayout->addWidget(titleLabel, 2, 0);
    messageLayout->addWidget(titleEdit, 2, 1, 1, 4);
    messageLayout->addWidget(bodyLabel, 3, 0);
    messageLayout->addWidget(bodyEdit, 3, 1, 2, 4);
    messageLayout->setRowStretch(4, 1);
    messageLayout->setColumnStretch(3, 1);
    messageLayout->addWidget(showMessageButton, 5, 4);
    messageGroupBox->setLayout(messageLayout);
}

void Window::createActions() {
    minimizeAction = new QAction(tr("Minimize"), this);
    connect(this->minimizeAction, &QAction::triggered, this, &Window::hide);
    maximizeAction = new QAction(tr("Maximize"), this);
    connect(this->maximizeAction, &QAction::triggered, this, [this]() {
        this->resize(1920, 1080);
        this->showMaximized();
    });
    restoreAction = new QAction(tr("Restore"), this);
    connect(this->restoreAction, &QAction::triggered, this,
            &Window::showNormal);
    quitAction = new QAction(tr("Quit"), this);
    connect(this->quitAction, &QAction::triggered, qApp,
            &QCoreApplication::quit);
}

void Window::createTrayIconMenu() {
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(maximizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    systemTrayIcon = new QSystemTrayIcon(this);
    systemTrayIcon->setContextMenu(trayIconMenu);
}

// SLOTS FUNCTIONS SEGMENT BEGIN

void Window::setIcon(int index) {
    QIcon currentIcon{iconComboBox->itemIcon(index)};
    systemTrayIcon->setIcon(currentIcon);
    setWindowIcon(currentIcon);
    systemTrayIcon->setToolTip(iconComboBox->itemText(index));
}

void Window::showMessage() {
    showIconCheckBox->setChecked(true);
    int selectedIcon =
            messageTypeComboBox->itemData(messageTypeComboBox->currentIndex())
            .toInt();
    const auto msgIcon = static_cast<QSystemTrayIcon::MessageIcon>(
        selectedIcon);
    if (selectedIcon == -1) {
        systemTrayIcon->showMessage(
            titleEdit->text(), bodyEdit->toPlainText(),
            iconComboBox->itemIcon(iconComboBox->currentIndex()),
            durationSpinBox->value() * 1000);
    } else {
        systemTrayIcon->showMessage(titleEdit->text(), bodyEdit->toPlainText(),
                                    msgIcon, durationSpinBox->value() * 1000);
    }
}

void Window::setVisible(bool visible) {
    minimizeAction->setEnabled(visible);
    maximizeAction->setEnabled(!isMaximized());
    restoreAction->setEnabled(isMaximized() || !visible);
    QMainWindow::setVisible(visible);
}

void Window::closeEvent(QCloseEvent *event) {
    if (!event->spontaneous() || !isVisible())
        return;
    if (systemTrayIcon->isVisible()) {
        QMessageBox::information(this, tr("Tray"), tr(
                                     "The program will keep running in the "
                                     "system tray. To terminate the program, "
                                     "choose <b>Quit</b> in the context menu "
                                     "of the system tray entry."));
        this->hide();
        event->ignore();
    }
}


// SLOTS FUNCTIONS SEGMENT END
