#ifndef HTTPMGR_H
#define HTTPMGR_H

#include <QObject>
#include<global.h>
#include<singleton.h>
#include<QNetworkReply>


class HttpMgr:public QObject,public Singleton<HttpMgr>,
        public std::enable_shared_from_this<HttpMgr>
{
    Q_OBJECT
public:
    ~HttpMgr();
    void PostHttpReq(QUrl url,QJsonObject json,REQID req_id,MODULES mod);

private:
    friend class Singleton<HttpMgr>;
    HttpMgr();
    QNetworkAccessManager _manager;
private slots:
    void slot_http_finish(REQID req_id,QString res,ERROR err,MODULES mod);
signals:
    void sig_http_finish(REQID req_id,QString res,ERROR err,MODULES mod);
    void sig_reg_mod_finish(REQID req_id,QString res,ERROR err);

};

#endif // HTTPMGR_H
