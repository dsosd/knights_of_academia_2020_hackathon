#include "main.h"

#include <thread>

#include <arduino.h>
#include <server.h>

int main(int argc, char** argv){
	koa_2020::Server serv;

	std::thread t1(
		[&serv](){serv.start_listening(26500);}
	);



	t1.join();

	return 0;
}
