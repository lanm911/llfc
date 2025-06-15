#include "CServer.h"
#include"HttpConnection.h"
CServer::CServer(net::io_context& ioc, unsigned short& port) :_ioc(ioc),
_acceptor(ioc,tcp::endpoint(net::ip::address_v4::any(),port)),_socket(_ioc){

}

void CServer::Start()
{
	auto self = shared_from_this();
	_acceptor.async_accept(_socket, [self](beast::error_code ec) {
		try {
			if (ec) {
				self->Start();
				return;
			}
			std::make_shared<HttpConnection>(std::move(self->_socket))->Start();
			self->Start();
		}
		catch (std::exception& exp) {
			std::cout << "exception is " << exp.what() << std::endl;
			self->Start();
		}
		

	});

}
