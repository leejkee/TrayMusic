//
// Created by cww on 25-2-13.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "Player.h"
class TrayUI;

class MainWindow : public QMainWindow {

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event);


private:
    void createConnect();
    void setVisible(bool visible) override;
    QWidget *CWidget;
    TrayUI *ui;
    Player *m_player;
};


#endif //MAINWINDOW_H
