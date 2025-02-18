#ifndef TRAYUI_H
#define TRAYUI_H
#include <QLabel>
#include <QSlider>
#include <QPushButton>

class QGroupBox;
class QLabel;
class QComboBox;
class QCheckBox;
class QMenu;
class QAction;
class QSystemTrayIcon;
class QWidget;
class QMainWindow;
class QMediaPlayer;
class QPushButton;

class TrayUI {
public:
    TrayUI();
    void setupUI(QMainWindow *parent);
    QGroupBox* iconGroupBox;
    QPushButton *pushButtonLoadFile;
    QCheckBox* showIconCheckBox;

    QAction* minimizeAction;
    QAction* maximizeAction;
    QAction* restoreAction;
    QAction* quitAction;
    QSystemTrayIcon *systemTrayIcon;
    QMenu *trayIconMenu;

    QGroupBox *musicPlayerGroupBox;
    QPushButton *pushButtonPlay;
    QLabel *labelMusicFileName;
    QPushButton *pushButtonPre;
    QPushButton *pushButtonNext;
    QWidget *volumeControlWidget;
    QPushButton *volumeCtrlButton;
    QSlider *volumeSlider;

    static const QString trayIconSVG;
    static const QString playIconSVG;
    static const QString pauseIconSVG;
    static const QString preIconSVG;
    static const QString nextIconSVG;
    static const QString volumeSVG;
    static const QString volumeMuteSVG;


private:
    void createIconGroupBox();
    void createMusicPlayerGroupBox();
    void createActions(QWidget *parent);
    void createTrayIconMenu(QWidget *parent);
};

#endif