#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QObject>
#include<login.h>
#include<register.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //变量声明
    MainWindow(QWidget *parent = nullptr);
    Login* _my_login = new Login();
    Register *_my_register = new Register();
    ~MainWindow();
public:
    //函数声明
    void switch_register();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
