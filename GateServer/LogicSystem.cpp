#include "LogicSystem.h"
#include"HttpConnection.h"

LogicSystem::LogicSystem(){

	RegGet("/get_test", [](std::shared_ptr<HttpConnection> connection) {
		beast::ostream(connection->_response.body()) << "receive get_test req";
		});
}

LogicSystem::~LogicSystem()
{
}

bool LogicSystem::HandleGet(std::string path, std::shared_ptr<HttpConnection> con)
{
	if (_get_handler.find(path) == _get_handler.end()) {
		return false;
	}
	_get_handler[path](con);
	return true;
}

void LogicSystem::RegGet(std::string url, HttpHandler handler)
{
	_get_handler.insert({ url,handler });
}
