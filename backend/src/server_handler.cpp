#include "server_handler.h"

#include <server.h>

namespace koa_2020{

Server_handler::Server_handler(Server& server_)
		:server(server_){
}

const Sptr_resp Server_handler::render_GET(const Http_req& req){
	std::string resp = "GET request received!";
	//
	return Sptr_resp(new httpserver::string_response(resp));
}

const Sptr_resp Server_handler::render_POST(const Http_req& req){
	std::string resp = "POST request received!";

	//block all further inbound requests
	this->disallow_all();
	//allow server to end
	server.mutex.unlock();

	return Sptr_resp(new httpserver::string_response(resp));
}

}
