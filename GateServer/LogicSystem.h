#pragma once
#include"const.h"

class HttpConnection;
typedef std::function<void(std::shared_ptr<HttpConnection>)> HttpHandler;
class LogicSystem:public Singleton<LogicSystem>
{
	friend class Singleton<LogicSystem>;
public:
	~LogicSystem();
	bool HandleGet(std::string path,std::shared_ptr<HttpConnection> con);
	void RegGet(std::string url,HttpHandler handler);


private:
	LogicSystem();
	std::unordered_map<std::string, HttpHandler> _post_handler;
	std::unordered_map<std::string, HttpHandler> _get_handler;
};

