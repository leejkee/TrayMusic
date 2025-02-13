#ifndef TRAYUI_H
#define TRAYUI_H

class QGroupBox;
class QLabel;
class QComboBox;
class QCheckBox;
class QMenu;
class QAction;
class QSystemTrayIcon;
class QWidget;
class QMainWindow;

class TrayUI {
public:
    TrayUI();
    void setupUI(QMainWindow *parent);


    QGroupBox* iconGroupBox;
    QLabel* iconLabel;
    QComboBox* iconComboBox;
    QCheckBox* showIconCheckBox;
    QGroupBox *messageGroupBox;
    QAction* minimizeAction;
    QAction* maximizeAction;
    QAction* restoreAction;
    QAction* quitAction;
    QSystemTrayIcon *systemTrayIcon;
    QMenu *trayIconMenu;

private:
    void createIconGroupBox();
    void createMessageGroupBox();
    void createActions(QWidget *parent);
    void createTrayIconMenu(QWidget *parent);

};

#endif