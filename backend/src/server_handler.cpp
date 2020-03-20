#include "server_handler.h"

namespace koa_2020{

const Sptr_resp Server_handler::render_GET(const Http_req& req){
	std::string resp = "GET request received!";
	return Sptr_resp(new httpserver::string_response(resp));
}

const Sptr_resp Server_handler::render_POST(const Http_req& req){
	std::string resp = "POST request received!";
	return Sptr_resp(new httpserver::string_response(resp));
}

}
