//
// Created by cww on 25-3-6.
//

#ifndef MUSICLISTBUTTON_H
#define MUSICLISTBUTTON_H
#include <QPushButton>


class ListButton final : public QPushButton {
    Q_OBJECT

public:
    explicit ListButton(QWidget *parent = nullptr);
    explicit ListButton(const QIcon &icon, QWidget *parent = nullptr, QString name = "");
    explicit ListButton(const QString &name, QWidget *parent = nullptr);
    static void loadStyleSheet(QPushButton *, const QString &);

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
