#include "server.h"

#include <iostream>

namespace koa_2020{

Server::Server(int port)
		:serv(httpserver::create_webserver(port)){
	Server_ handler;
	serv.register_resource("/api", &handler);
	std::cout << "abc\n";
	serv.start(false);

	std::cout << "www\n";
}

const Sptr_resp Server_::render_GET(const Http_req& req){
	std::string resp = "GET request received!";
	return Sptr_resp(new httpserver::string_response(resp));
}

const Sptr_resp Server_::render_POST(const Http_req& req){
	std::string resp = "POST request received!";
	return Sptr_resp(new httpserver::string_response(resp));
}

}
