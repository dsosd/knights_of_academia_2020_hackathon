#ifndef uuid_guard_7f8de925_aac161f2_9f4c9539_5315ae01
#define uuid_guard_7f8de925_aac161f2_9f4c9539_5315ae01

#include <memory>

#include <httpserver/httpserver.hpp>

namespace koa_2020{

using Sptr_resp = std::shared_ptr<httpserver::http_response>;
using Http_req = httpserver::http_request;

class Server_: public httpserver::http_resource{
public:
	void start_listening(int port);

	const Sptr_resp render_GET(const Http_req& req) final;
	const Sptr_resp render_POST(const Http_req& req) final;
private:
	//
};

class Server{
public:
	Server(int port);

	//void start_listening(int port);
private:
	httpserver::webserver serv;
};

}

#endif // uuid_guard_7f8de925_aac161f2_9f4c9539_5315ae01
