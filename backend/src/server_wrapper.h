#ifndef uuid_guard_afeb95bb_1eacde7f_155d1c0f_836aa3f7
#define uuid_guard_afeb95bb_1eacde7f_155d1c0f_836aa3f7

#include <httpserver/httpserver.hpp>

namespace koa_2020{

class Server_wrapper{
public:
	//default constructor should NOT be used when starting a server
	Server_wrapper();
	Server_wrapper(int port);

	httpserver::webserver& unwrap();
private:
	bool startable;
	httpserver::webserver server;
};

}

#endif // uuid_guard_afeb95bb_1eacde7f_155d1c0f_836aa3f7
