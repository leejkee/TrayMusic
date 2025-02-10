#include <QSystemTrayIcon>
#include <QDialog>

class Window: QDialog {
    Q_OBJECT

public:
    Window();
    void setVisible(bool visible) override;

protected:
    void closeEvent(QCloseEvent* event) override;
private Q_SLOTS:
    void setIcon(int index);

private:
    void createIconGroupBox();

};