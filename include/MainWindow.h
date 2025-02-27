//
// Created by cww on 25-2-13.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>


class Player;
class ViewWidget;
class PlayerWidget;
class QSystemTrayIcon;
class TrayUI;
class WindowManager;
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

    QAction* m_minimizeAction;
    QAction* m_maximizeAction;
    QAction* m_restoreAction;
    QAction* m_quitAction;
    QSystemTrayIcon *m_systemTrayIcon;
    QMenu *m_trayIconMenu;

    void createTrayIcon();
    // void loadSettings();
    QWidget *m_centralWidget;
    Player *m_player;
    ViewWidget *m_iconWidget;
    PlayerWidget *m_playerWidget;
    WindowManager *m_windowManager;

public Q_SLOTS:
    void changeMusicLabelName(const QString& name);

};


#endif //MAINWINDOW_H
