#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    connect(ui->login_Register_PB,&QPushButton::clicked,this,&Login::switch_register);

}

Login::~Login()
{
    delete ui;
}
