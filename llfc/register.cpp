#include "register.h"
#include "ui_register.h"
#include"QRegularExpression"
#include<httpmgr.h>
Register::Register(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
    ui->regist_Password_LD->setEchoMode(QLineEdit::Password);
    ui->regist_ConfirmPs_LD->setEchoMode(QLineEdit::Password);

    ui->error_tip->setProperty("state","normal");
    repolish(ui->error_tip);

    connect(HttpMgr::GetInstance().get(),&HttpMgr::sig_reg_mod_finish,this,&Register::slot_reg_mod_finish);
    initHttpHandlers();
}

void Register::showTip(QString str,bool flg)
{
    ui->error_tip->setText(str);
    if(flg){
        ui->error_tip->setProperty("state","normal");
    }else{
        ui->error_tip->setProperty("state","err");
    }

    repolish(ui->error_tip);
}

Register::~Register()
{
    delete ui;
}

void Register::on_regist_Getvarify_PB_clicked()
{
    auto email = ui->regist_email_LD->text();

    QRegularExpression regex(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
    bool match = regex.match(email).hasMatch();
    if(match){
        //发送http请求获取验证码
        qDebug()<<"email is "<<email;
    }else{
        showTip(tr("邮箱地址不正确"),false);
    }
}

void Register::slot_reg_mod_finish(REQID req_id, QString res, ERROR err)
{
    if(err!=ERROR::SUCCESS){
        showTip(tr("网络请求错误"),false);
        return;
    }
    //res需要转化为QByteArray,然后解析json
    QJsonDocument jsonDoc = QJsonDocument::fromJson(res.toUtf8());

    if(jsonDoc.isNull()){
        showTip(tr("json解析失败"),false);
        return;
    }
    if(!jsonDoc.isObject()){
        showTip(tr("json解析失败"),false);
        return;
    }

    _handlers[req_id](jsonDoc.object());
}

void Register::initHttpHandlers()
{
    _handlers.insert(REQID::ID_GET_VARIFY_CODE,[this](QJsonObject jsonObj){
        int error = jsonObj["error"].toInt();
        if(error!=ERROR::SUCCESS){
            showTip(tr("参数错误"),false);
            return;
        }
        auto email = jsonObj["email"].toString();
        showTip(tr("验证码已经发送到邮箱，请注意查收"),false);
        qDebug()<<"email is "<<email;
    });
}
