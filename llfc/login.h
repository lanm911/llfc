#ifndef LOGIN_H
#define LOGIN_H

#include<QObject>
#include<QWidget>
namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT
signals:
    void switch_register();
public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
