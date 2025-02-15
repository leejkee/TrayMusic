//
// Created by cww on 25-2-13.
//

#include "MainWindow.h"
#include <QApplication>
#include <QAudioOutput>
#include <QCheckBox>
#include <QComboBox>
#include <QSystemTrayIcon>
#include <QCloseEvent>
#include <QMessageBox>
#include <QFileDialog>
#include <QPushButton>
#include <QLabel>
#include "TrayUI.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      , ui(new TrayUI)
    , m_player(new Player){
    CWidget = new QWidget(this);
    setCentralWidget(CWidget);
    ui->setupUI(this);
    createConnect();
    ui->systemTrayIcon->show();
}

MainWindow::~MainWindow() {
    delete ui;
    delete m_player;
}

void MainWindow::createConnect() {
    // connect for actions
    connect(ui->quitAction, &QAction::triggered, qApp, &QApplication::quit);
    connect(ui->maximizeAction, &QAction::triggered, this,
            &MainWindow::showMaximized);
    connect(ui->minimizeAction, &QAction::triggered, this, &MainWindow::hide);
    connect(ui->restoreAction, &QAction::triggered, this,
            &MainWindow::showNormal);

    // connect for system tray
    connect(ui->iconComboBox, &QComboBox::currentIndexChanged, this, [this](const int index) {
        const QIcon currentIcon{ui->iconComboBox->itemIcon(index)};
        ui->systemTrayIcon->setIcon(currentIcon);
        this->setWindowIcon(currentIcon);
        ui->systemTrayIcon->setToolTip(
            ui->iconComboBox->itemText(index));
    });

    connect(ui->showIconCheckBox, &QCheckBox::toggled, ui->systemTrayIcon, &QSystemTrayIcon::setVisible);
    connect(ui->pushButtonLoadFile, &QPushButton::clicked, this, [this]() {
        if (const QString fileName = QFileDialog::getOpenFileName(this, tr("Open Mp3"),"", tr("Mp3 Files (*.mp3)")); fileName.isEmpty()) {
            return;
        }
        else {
            m_player->loadMusic(QUrl::fromLocalFile(fileName));
            ui->labelSongName->setText(fileName);
        }
    });

    connect(ui->pushButtonPlay, &QPushButton::clicked, this, [this]() {
        m_player->playToggle();
    });

    connect(m_player, &Player::playStatusChanged, this, [this](const bool isPlaying) {
        if (isPlaying) {
            ui->pushButtonPlay->setText("Pause");
        }
        else {
            ui->pushButtonPlay->setText("Play");
        }
    });
}

void MainWindow::closeEvent(QCloseEvent *event) {
    if (!event->spontaneous() || !isVisible())
        return;
    if (ui->systemTrayIcon->isVisible()) {
        QMessageBox::information(this, tr("Tray"), tr(
                                     "The program will keep running in the "
                                     "system tray. To terminate the program, "
                                     "choose <b>Quit</b> in the context menu "
                                     "of the system tray entry."));
        this->hide();
        event->ignore();
    }
}

void MainWindow::setVisible(const bool visible) {
    ui->restoreAction->setEnabled(isMaximized() || !visible);
    ui->minimizeAction->setEnabled(visible);
    ui->maximizeAction->setEnabled(!isMaximized());
    QMainWindow::setVisible(visible);
}



