#include "server.h"

#include <iostream>

namespace koa_2020{

Server::Server()
		:handler(new Server_handler(*this)), wrapper(new Server_wrapper()){
}

void Server::start_listening(int port){
	wrapper = std::make_shared<Server_wrapper>(Server_wrapper(port));

	handler->disallow_all();
	handler->set_allowing("GET", true);
	handler->set_allowing("POST", true);

	wrapper->unwrap().register_resource("/api", &*handler, true);

	wrapper->unwrap().start(false);

	//wait for server to finish (and unlock the mutex)
	mutex.lock();

	//block until the mutex is unlocked
	mutex.lock();
	//clean up
	mutex.unlock();
}

void Server::stop(){
	wrapper->unwrap().sweet_kill();
}

}
