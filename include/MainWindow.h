//
// Created by cww on 25-2-13.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>

class Player;
class IconWidget;
class PlayerWidget;
class QSystemTrayIcon;
class TrayUI;
class MainWindow final : public QMainWindow {
Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

protected:
    void closeEvent(QCloseEvent *event) override;
    // void mouseMoveEvent(QMouseEvent *event) override;
    // void mouseLeaveEvent(QMouseEvent *event) override;


private:
    void initMainApplication();
    void createConnect();
    void setVisible(bool visible) override;

    QAction* minimizeAction;
    QAction* maximizeAction;
    QAction* restoreAction;
    QAction* quitAction;
    QSystemTrayIcon *systemTrayIcon;
    QMenu *trayIconMenu;

    void initTray();
    void loadSettings();
    QWidget *m_centralWidget;
    TrayUI *m_gui;
    Player *m_player;
    IconWidget *m_iconWidget;
    PlayerWidget *m_playerWidget;

public Q_SLOTS:
    void changeMusicLabelName(const QString& name);

};


#endif //MAINWINDOW_H
