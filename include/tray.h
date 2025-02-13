#ifndef TRAY_H
#define TRAY_H
#include <QMainWindow>
#include <QSystemTrayIcon>

QT_BEGIN_NAMESPACE
class QGroupBox;
class QLabel;
class QComboBox;
class QCheckBox;
class QSpinBox;
class QLineEdit;
class QTextEdit;
class QPushButton;
class QMenu;
class QAction;

QT_END_NAMESPACE

class Window final : public QMainWindow {
    Q_OBJECT

public:
    Window();
    void setVisible(bool visible) override;

protected:
    void closeEvent(QCloseEvent *event) override;
private Q_SLOTS:
    void setIcon(int index);
    void showMessage();

private:
    void createIconGroupBox();
    void createMessageGroupBox();
    void createActions();
    void createTrayIconMenu();

    QWidget* centralWidget;
    QGroupBox* iconGroupBox;
    QLabel* iconLabel;
    QComboBox* iconComboBox;
    QCheckBox* showIconCheckBox;

    QGroupBox* messageGroupBox;
    QLabel* messageTypeLabel;
    QLabel* durationLabel;
    QLabel* durationInfo;
    QLabel* titleLabel;
    QLabel* bodyLabel;
    QComboBox* messageTypeComboBox;
    QSpinBox* durationSpinBox;
    QLineEdit* titleEdit;
    QTextEdit* bodyEdit;
    QPushButton* showMessageButton;

    QAction* minimizeAction;
    QAction* maximizeAction;
    QAction* restoreAction;
    QAction* size_800x600_Action;
    QAction* quitAction;

    QSystemTrayIcon *systemTrayIcon;
    QMenu *trayIconMenu;
};

#endif