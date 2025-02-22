//
// Created by cww on 25-2-22.
//

#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H
#include <QWidget>

class QGridLayout;

class WindowManager final : public QWidget{

public:
    explicit WindowManager(QWidget *mainWidget, QWidget *parent = nullptr);
    ~WindowManager() override;
    void showMainWidget();
    void showOtherWidget(QWidget *widget);
    void setBottomWidget(QWidget *widget);

private:
    QWidget* m_mainWidget;
    QWidget* m_bottomWidget;
    QWidget *m_otherWidget;
    QGridLayout *m_mainLayout;
    QLayout *m_bottomLayout;
};





#endif //WINDOWMANAGER_H
