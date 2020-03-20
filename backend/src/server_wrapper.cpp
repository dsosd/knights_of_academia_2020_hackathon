#include "server_wrapper.h"

#include <exception>

namespace koa_2020{

Server_wrapper::Server_wrapper()
		:server(httpserver::create_webserver()){
	startable = false;
}

Server_wrapper::Server_wrapper(int port)
		//MAGIC server config
		:server(httpserver::create_webserver(port)
			.max_threads(6)){
	startable = true;
}

httpserver::webserver& Server_wrapper::unwrap(){
	if (!startable){
		throw std::exception();
	}
	return server;
}

}
