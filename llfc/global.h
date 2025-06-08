#ifndef GLOBAL_H
#define GLOBAL_H

#include <QWidget>
#include<functional>
#include<iostream>
#include"Qstyle"
#include<QNetworkAccessManager>
#include<QJsonObject>
#include<QJsonDocument>

extern std::function<void(QWidget*)> repolish;
class global : public QWidget
{
    Q_OBJECT
public:
    explicit global(QWidget *parent = nullptr);

public:

signals:

};

enum REQID{
    ID_GET_VARIFY_CODE = 1001,//获取验证码
    ID_REG_USER = 1002,//注册用户

};

enum ERROR{
    SUCCESS = 0,
    ERR_JSON = 1,//json解析失败
    ERR_NETWORK = 2,//网络连接失败
};

enum MODULES{
    REGISTER_MOD = 101,//注册模块

};

#endif // GLOBAL_H
