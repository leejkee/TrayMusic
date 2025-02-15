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
    void createConnect();
    void setVisible(bool visible) override;
    QWidget *CWidget;
    TrayUI *ui;
    Player *m_player;
};


#endif //MAINWINDOW_H
