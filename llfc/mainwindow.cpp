#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent)
    ,ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //创建login界面，设置为主界面
    _my_login = new Login();
    setCentralWidget(_my_login);
    _my_login->show();

    //创建register界面，连接login信号与register的切换
    connect(_my_login,&Login::switch_register,this,&MainWindow::switch_register);
}

void MainWindow::switch_register()
{
    _my_login->hide();
    setCentralWidget(_my_register);
    _my_register->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

