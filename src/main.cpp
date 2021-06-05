#include <string>
#include "world.hpp"
#include "lua.hpp"

void rendering_main(void);

#include <chrono>
#include <thread>

#include <atomic>
std::atomic<bool> run;
std::atomic<bool> paused;
std::atomic<bool> do_start;

#include <libintl.h>
#include <locale.h>
#include "path.hpp"
#include "network.hpp"

#include <iostream>
#include <fstream>

#include "serializer.hpp"

std::mutex world_lock;
int main(int argc, char ** argv) {
	setlocale(LC_ALL, "");
	bindtextdomain("main", Path::get("locale").c_str());
	textdomain("main");

	Client * client;
	Server * server;
	World * world = new World();

	//Archive test;
	//serialize(test, *world);
	//test.to_file("hello_world.v0");

	printf("%s\n", gettext("launching rendering thread"));
	std::thread t1(rendering_main);

	while(!do_start);
	
	paused = false;
	while(run) {
		std::unique_lock<std::mutex> lock(world_lock);
		world->do_tick();
		world->client_update();
		//std::this_thread::sleep_for(std::chrono::milliseconds(10));

		while(paused);
	}
	t1.join();

	//if(!strcmp(argv[1], "client")) {
	//	client = new Client("127.0.0.1", 4206);

	//uint8_t * arr = new uint8_t[16777216];
	//std::basic_ofstream<uint8_t> outfile("world_cache.wcyz", std::ofstream::out | std::ofstream::binary);
	//Serializer<World>::serialize(arr, *world);
	//outfile.write(arr, 16777216);
	//delete[] arr;
	/*} else if(!strcmp(argv[1], "server")) {
		server = new Server(4206);
		world = new World();
	}*/

	return 0;
}

#ifdef WIN32
#include <windows.h>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszArgument, int iShow) {
	char* argv[1];
	argv[0] = "/";
	main(1, argv);
}
#endif
