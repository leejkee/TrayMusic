//
// Created by cww on 25-3-5.
//

#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H
#include <QWidget>

class QLabel;
class Settings;
class QPushButton;
class QListWidget;

class LocalMusicSettingsWidget final : public QWidget {
    Q_OBJECT

public:
    explicit LocalMusicSettingsWidget(QWidget *parent = nullptr);

    void loadSettings();

private:
    QPushButton *m_addButton;
    QPushButton *m_removeButton;
    QListWidget *m_listWidget;
    QLabel *m_messageLabel;

Q_SIGNALS:
    // signals for settings changed
    // 1, send to the settings
    // 2, send to the  viewWidget to refresh if the shown widget is "local"
    void signalLocalMusicPathSettingsChanged();
    void signalAddButton(const QString &);
    void signalRemoveButton(const QString &);

private Q_SLOTS:
    void addMusicPath();

    void removeMusicPath();
};


#endif //SETTINGSWIDGET_H
