#ifndef uuid_guard_c0f3b0fe_8691e8d0_f1456af3_289f93ef
#define uuid_guard_c0f3b0fe_8691e8d0_f1456af3_289f93ef

#include <memory>

#include <httpserver/httpserver.hpp>

namespace koa_2020{

using Sptr_resp = std::shared_ptr<httpserver::http_response>;
using Http_req = httpserver::http_request;

class Server_handler: public httpserver::http_resource{
public:
	const Sptr_resp render_GET(const Http_req& req) final;
	const Sptr_resp render_POST(const Http_req& req) final;
private:
	//
};

}

#endif // uuid_guard_c0f3b0fe_8691e8d0_f1456af3_289f93ef
