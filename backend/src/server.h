#ifndef uuid_guard_7f8de925_aac161f2_9f4c9539_5315ae01
#define uuid_guard_7f8de925_aac161f2_9f4c9539_5315ae01

#include <memory>

#include <server_handler.h>
#include <server_wrapper.h>

namespace koa_2020{

class Server{
public:
	Server();

	void start_listening(int port);
	void stop();
private:
	std::unique_ptr<Server_handler> handler;
	std::shared_ptr<Server_wrapper> wrapper;
};

}

#endif // uuid_guard_7f8de925_aac161f2_9f4c9539_5315ae01
