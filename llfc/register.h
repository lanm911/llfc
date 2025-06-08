#ifndef REGISTER_H
#define REGISTER_H

#include <QWidget>
#include<global.h>

namespace Ui {
class Register;
}

class Register : public QWidget
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);

    void showTip(QString str,bool flg);

    ~Register();

private slots:
    void on_regist_Getvarify_PB_clicked();
    void slot_reg_mod_finish(REQID req_id,QString res,ERROR err);
signals:

private:
    Ui::Register *ui;
    QMap<REQID,std::function<void(const QJsonObject&)>> _handlers;
    void initHttpHandlers();
};

#endif // REGISTER_H
