#include "main.h"

#include <arduino.h>
#include <server.h>

int main(int argc, char** argv){
	koa_2020::Server serv;

	serv.start_listening(26500);

	return 0;
}
