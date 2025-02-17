//
// Created by cww on 25-2-13.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "Player.h"
class TrayUI;

class MainWindow final : public QMainWindow {
Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

protected:
    void closeEvent(QCloseEvent *event) override;


private:
    void initMainApplication();
    void createConnect();
    void setVisible(bool visible) override;


void loadSettings();
    QWidget *m_centralWidget;
    TrayUI *m_gui;
    Player *m_player;

public Q_SLOTS:
    void setPlayButtonIcon(bool play);
    void changeMusicLabelName(const QString& name);

};


#endif //MAINWINDOW_H
