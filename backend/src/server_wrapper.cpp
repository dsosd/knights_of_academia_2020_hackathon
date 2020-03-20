#include "server_wrapper.h"

namespace koa_2020{

Server_wrapper::Server_wrapper()
		:server(httpserver::create_webserver()){
}

Server_wrapper::Server_wrapper(int port)
		:server(httpserver::create_webserver(port)){
}

httpserver::webserver& Server_wrapper::unwrap(){
	return server;
}

}
