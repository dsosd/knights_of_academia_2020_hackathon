#include "server.h"

#include <iostream>

namespace koa_2020{

Server::Server()
		:handler(new Server_handler()), wrapper(new Server_wrapper()){
}

void Server::start_listening(int port){
	wrapper = std::make_shared<Server_wrapper>(Server_wrapper(port));

	handler->disallow_all();
	handler->set_allowing("GET", true);
	handler->set_allowing("POST", true);

	wrapper->unwrap().register_resource("/api", &*handler);

	//since this call is blocking, this function should be called on a separate thread
	wrapper->unwrap().start(true);
}

void Server::stop(){
	wrapper->unwrap().stop();
}

}
