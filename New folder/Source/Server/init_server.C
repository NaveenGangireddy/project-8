#include <stdlib.h>
#include <unistd.h>

void start_server(){
    system("gnome-terminal -e 'sh -c \"cd server && g++ server.C -o server && ./server\"'");
	sleep(1);
}
