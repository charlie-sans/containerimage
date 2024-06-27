#include "main.h"
#include "handle.h"
//http server
int create_socket(int port)
{
	int s;
	struct sockaddr_in addr;

	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s < 0) {
		perror("Unable to create socket");
		exit(1);
	}

	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = INADDR_ANY;

	if (bind(s, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
		perror("Unable to bind");
		exit(1);
	}

	if (listen(s, MAX_CONNECTIONS) < 0) {
		perror("Unable to listen");
		exit(1);
	}

	return s;
}