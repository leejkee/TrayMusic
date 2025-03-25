//
// Created by cww on 25-3-6.
//

#ifndef MUSICLISTBUTTON_H
#define MUSICLISTBUTTON_H
#include <QPushButton>


class BetterButton final : public QPushButton {
    Q_OBJECT

public:

    // others
    explicit BetterButton(QWidget *parent = nullptr);
    explicit BetterButton(const QIcon &icon, QWidget *parent = nullptr, QString name = "");

    // Music List buttons
    explicit BetterButton(const QString &name, QWidget *parent = nullptr);

    void loadStyleSheet(const QString &);

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;
signals:
    void signalButtonClicked(const QString &listName);

private Q_SLOTS:
    void onButtonClicked() {
        emit signalButtonClicked(m_listName);
    }

private:
    QString m_listName;
};


#endif //MUSICLISTBUTTON_H
