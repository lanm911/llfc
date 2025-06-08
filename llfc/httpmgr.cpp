#include "httpmgr.h"


HttpMgr::~HttpMgr()
{

}

HttpMgr::HttpMgr()
{
    connect(this,&HttpMgr::sig_http_finish,this,&HttpMgr::slot_http_finish);
}

void HttpMgr::slot_http_finish(REQID req_id, QString res, ERROR err, MODULES mod)
{
    //发送信号通知相关模块
    switch (mod) {
    case MODULES::REGISTER_MOD://发送给注册模块
        emit sig_reg_mod_finish(req_id,res,err);
        break;
    default:
        break;
    }
}
void HttpMgr::PostHttpReq(QUrl url, QJsonObject json, REQID req_id, MODULES mod)
{
    //创建一个http请求，设置请求头部和请求体
    QByteArray date = QJsonDocument(json).toJson();
    //通过url构造请求
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader, QByteArray::number(date.length()));

    //发送请求
    QNetworkReply *reply = _manager.post(request,date);
    auto self = shared_from_this();
    //使用shared_from_this   1.构造伪闭包 2.增加智能指针计数

    //QObject::connect(reply,&QNetworkReply::finished,[this]{
    //});    lambda表达式捕获this，如果在回调函数结束之前，HttpMgr被释放则无法发送请求

    QObject::connect(reply,&QNetworkReply::finished,[reply,self,req_id,mod]{
        if(reply->error() != QNetworkReply::NoError){
            qDebug() <<reply->errorString();

            emit self->sig_http_finish(req_id,"",ERROR::ERR_NETWORK,mod);
            reply->deleteLater();
            return;
        }
        //读回请求
        auto res = reply->readAll();

        emit self->sig_http_finish(req_id,res,ERROR::SUCCESS,mod);

        reply->deleteLater();
        return;
    });

}

