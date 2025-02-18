#include "TrayUI.h"
#include "QMainWindow"
#include <QCheckBox>
#include <qevent.h>
#include <QGroupBox>
#include <QLabel>
#include <QMenu>
#include <QPushButton>
#include <QSystemTrayIcon>
#include <QVBoxLayout>

template <int WIDTH, int HEIGHT, typename... Args>
void setButtonFixedSize(Args... buttons) {
    (void)std::initializer_list<int>{([&](){
        if constexpr (std::is_pointer_v<std::remove_cv_t<decltype(buttons)>> &&
                      std::is_same_v<std::remove_cv_t<std::remove_pointer_t<decltype(buttons)>>, QPushButton>) {
            buttons->setFixedSize(WIDTH, HEIGHT);
        } else {
            qDebug() << "Warning: Non-QPushButton pointer parameter discarded.";
        }
        return 0; // fold expression
    }(), 0)...};
}


const QString TrayUI::trayIconSVG(":/images/icon.svg");
const QString TrayUI::playIconSVG(":/images/play.svg");
const QString TrayUI::pauseIconSVG(":/images/pause.svg");
const QString TrayUI::preIconSVG(":/images/pre.svg");
const QString TrayUI::nextIconSVG(":/images/next.svg");
const QString TrayUI::volumeSVG(":/images/high-volume.svg");
const QString TrayUI::volumeMuteSVG(":/images/no-volume.svg");

TrayUI::TrayUI()
{
}

/// You should call the function QMainWindow::setCentralWidget() before you use this function
/// @param parent the pointer to MainWindow
void TrayUI::setupUI(QMainWindow *parent) {
    createIconGroupBox();
    createMusicPlayerGroupBox();
    createActions(parent);
    createTrayIconMenu(parent);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(iconGroupBox);
    mainLayout->addWidget(musicPlayerGroupBox);
    if (QWidget *parentPtr = parent->centralWidget(); parentPtr != nullptr) {
        parentPtr->setLayout(mainLayout);
    }
}


void TrayUI::createIconGroupBox() {
    iconGroupBox = new QGroupBox(QCoreApplication::translate("TrayUI", ("Tray Icon")));
    showIconCheckBox = new QCheckBox(QCoreApplication::translate("TrayUI", "Show icon"));
    showIconCheckBox->setChecked(true);
    pushButtonLoadFile = new QPushButton(QCoreApplication::translate("TrayUI", "Load File"));

    QHBoxLayout *iconLayout = new QHBoxLayout;
    iconLayout->addWidget(showIconCheckBox);
    iconLayout->addStretch();
    iconLayout->addWidget(pushButtonLoadFile);
    iconGroupBox->setLayout(iconLayout);
    // qDebug() << "children :" << iconGroupBox->children();
}

void TrayUI::createMusicPlayerGroupBox() {
    musicPlayerGroupBox = new QGroupBox(QCoreApplication::translate("TrayUI", "Music Player"));
    pushButtonPlay = new QPushButton(QIcon(playIconSVG), "");
    labelMusicFileName = new QLabel(QCoreApplication::translate("TrayUI", "Song Name"));
    pushButtonPre = new QPushButton(QIcon(preIconSVG), "");
    pushButtonNext = new QPushButton(QIcon(nextIconSVG), "");
    pushButtonPlay->setEnabled(false);
    pushButtonNext->setEnabled(false);
    pushButtonPre->setEnabled(false);

    volumeCtrlButton = new QPushButton(QIcon(volumeSVG), "");
    volumeControlWidget = new QWidget(volumeCtrlButton);
    QVBoxLayout *volumeCtrlLayout = new QVBoxLayout;
    volumeSlider = new QSlider(Qt::Vertical);
    volumeSlider->setRange(0, 100);
    volumeSlider->setValue(30);
    volumeCtrlLayout->addWidget(volumeSlider);
    volumeControlWidget->setWindowFlags(Qt::ToolTip | Qt::FramelessWindowHint);
    volumeControlWidget->setLayout(volumeCtrlLayout);
    volumeControlWidget->resize(30, 80);

    setButtonFixedSize<30, 30>(pushButtonPlay, pushButtonPre, pushButtonNext, volumeCtrlButton);

    QVBoxLayout *Layout = new QVBoxLayout;
    QSpacerItem *spaceH = new QSpacerItem(-1, 0, QSizePolicy::Expanding);
    QSpacerItem *spaceV = new QSpacerItem(0, -1, QSizePolicy::Minimum, QSizePolicy::Expanding);
    Layout->addWidget(labelMusicFileName);
    Layout->addItem(spaceV);
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(pushButtonPre);
    buttonLayout->addWidget(pushButtonPlay);
    buttonLayout->addWidget(pushButtonNext);
    buttonLayout->addItem(spaceH);
    buttonLayout->addWidget(volumeCtrlButton);
    Layout->addLayout(buttonLayout);
    musicPlayerGroupBox->setLayout(Layout);
}

void TrayUI::createActions(QWidget *parent) {
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

    const auto icon = QIcon(trayIconSVG);
    systemTrayIcon->setIcon(icon);
    parent->setWindowIcon(icon);
    systemTrayIcon->setToolTip("Tray Music");
}




