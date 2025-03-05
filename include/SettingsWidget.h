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

class SettingsWidget final: public QWidget {
    Q_OBJECT
public:
    explicit SettingsWidget(Settings *settings, QWidget *parent = nullptr);


    void loadSettings();


    QPushButton *m_addBtn;
    QPushButton *m_removeBtn;
    QListWidget *m_listWidget;

private:
    Settings *m_settings;
    QLabel *m_messageLabel;

Q_SIGNALS:
    void musicPathChanged();

private Q_SLOTS:
    void addMusicPath();

    void removeMusicPath();
};


#endif //SETTINGSWIDGET_H
