#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define NUM_PORT 80
#define IP_ADDRESS "139.124.187.23"
//ressource : /tp1.html
#define MAX_SIZE 1024

using namespace std;

void exitErreur(const char * msg) {
	perror(msg);
	exit( EXIT_FAILURE);

}//exitErreur

int main(int argc, char* argv[]) {

	if(argc != 4){
		cerr << "Usage : ./client-tcp-http.run <IP@> <port> <ressource>" << endl;
		return -1;
	}

	/*
	cout << "IP = " << argv[1] << endl
	     << "PORT = " << argv[2] << endl;
	*/

	int sock_client = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in sockaddr_client, sockaddr_serveur;

	sockaddr_serveur.sin_family = AF_INET;
	sockaddr_serveur.sin_port = htons(atoi(argv[2]));
	inet_aton(argv[1], &sockaddr_serveur.sin_addr);
	
	if(connect(sock_client, (struct sockaddr*)&sockaddr_serveur, sizeof(sockaddr_serveur)) == -1)
		exitErreur("connect");

	string query = "GET " + string(argv[3]) + "\n";
	const char* msg = query.c_str();
	if (write(sock_client, msg, strlen(msg)) == -1)
			exitErreur("write");

	string message = "";
	char buf[MAX_SIZE];
	while(true){
		int result = read(sock_client, buf, sizeof(buf)-1);
		if(result == -1)
			exitErreur("read");
		else if(result > 0){
			string tmp = string (buf, result); 
			message += tmp;
		}
		else
			break;
	}

	cout << message;

	close(sock_client);

}//main
