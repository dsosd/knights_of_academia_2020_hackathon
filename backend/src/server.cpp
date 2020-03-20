#include "server.h"

#include <iostream>

namespace koa_2020{

Server::Server()
		:handler(new Server_handler()), wrapper(new Server_wrapper()){
}

void Server::start_listening(int port){
	wrapper = std::make_shared<Server_wrapper>(Server_wrapper(port));

	wrapper->unwrap().register_resource("/api", &*handler);

	wrapper->unwrap().start(false);
}

}
