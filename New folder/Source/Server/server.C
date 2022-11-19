#include<bits/stdc++.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include <unistd.h>

#include "../src/operations/_write.C"
#include "../src/operations/_read.C"


using namespace std;



#define MAX 1024
#define SIZE 1024

#define PORT 5200
// void send_file(FILE *fp, int sockfd, const char *filename)
// {
// 	int n;
// 	char data[SIZE] = {0};
// 	send(sockfd, filename, sizeof(filename), 0);
// 	while (fgets(data, SIZE, fp) != NULL)
// 	{
// 		if (send(sockfd, data, sizeof(data), 0) == -1)
// 		{
// 			perror("Error in sending file.");
// 			exit(1);
// 		}
// 		bzero(data, SIZE);
// 	}
// }
// void write_file(int sockfd){
//   int n;
//   FILE *fp;
//   char filename[] = "received_";
//   char buffer[SIZE];
  
//   n = recv(sockfd, buffer, SIZE, 0);
//   strcat(filename, buffer);
//   printf("%s\n", filename);
//   fp = fopen(filename, "w");
//   while (1) {
//     n = recv(sockfd, buffer, SIZE, 0);
//     if (n <= 0){
//       break;
//       return;
//     }
//     fprintf(fp, "%s", buffer);
//     bzero(buffer, SIZE);
//   }
//   return;
// }

int main()
{
	int serverSocketHandler = socket(AF_INET , SOCK_STREAM , 0);
	//creating a socket and assigning it to the socket handler
	if(serverSocketHandler < 0)
        {
       // socket methode return -1 if the creation was not successful
		cout << "Socket creation has failed.";
		return 0;
	    }
	struct sockaddr_in serverAddr , clientAddr;
	//specifying address and type for the server to operate under
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	int bindStatus = bind(serverSocketHandler , (struct sockaddr*) & serverAddr , sizeof(serverAddr));
	if(bindStatus < 0)
    {
		cout << "Socket binding has failed" << endl;
		return 0;
	}
	//listen to the client while others are waiting in queue of size 5
	int listenStatus = listen(serverSocketHandler , 5);
	if(listenStatus < 0)
        {	// when queue is full listen fails
		cout << "Listner has failed" << endl;
		return 0;
        }
	cout << "\t\t...Waiting for connections... \n\n";
	char buff[MAX];
	int clientSocketHandler;
	socklen_t len = sizeof(clientAddr);
	int connection;
	if((connection = accept(serverSocketHandler , (struct sockaddr*) & clientAddr , &len)) < 0)
    {
		cout << "Server didn't accept the request." << endl;
		return 0;
	}
	else
    {
		cout << "Server accepted the request. \n" ;
	}
	// write_file(connection);
	while(true){
		char buffer[SIZE];
		int response_code = recv(connection, buffer, SIZE, 0);
		if(response_code<=0){
			cout<<"Something went wrong\n";
			exit(0);
		}
		else if(strcmp(buffer, "upload")==0){
			cout<<buffer<<endl;

			write_file(connection);
		}
		else if(strcmp(buffer, "download")==0){
			cout<<buffer<<endl;
			// // sleep(10);
			// FILE *fp;
				char command[] = "this is message from server";
				send(connection, command, sizeof(command) + 1, 0);
			// 	const char *filename = "init_server.C";
			// 	fp = fopen(filename, "r");
			// 	if (fp == NULL)
			// 	{
			// 		perror("Error in reading file.");
			// 		// exit(1);
			// 	}
			// 	// sleep(20);
			// 	// char command[] = "upload";
			// 	send(connection, command, sizeof(command) + 1, 0);
				
			// 	send_file(fp, connection, filename);
			
		}
		sleep(20);

	}
	// while(true){
    //         // infinite loop for chatting
	// 	int rMsgSize;

	// 	if((rMsgSize  = recv(connection , buff , MAX , 0)) > 0){
	// 		cout << "received client : " << buff << endl;

	// 		if(buff[0] == 'b' && buff[1] == 'y' && buff[2] == 'e'){
	// 			cout << "Server : Bye bro" << endl;
	// 			cout << "\nConnection ended... take care bye bye...\n" ;
	// 			send(connection , buff , strlen(buff)+1 , 0);
	// 			break;
	// 		}

	// 		cout << "Server : ";
	// 		char input[MAX];
	// 		string s;
	// 		getline(cin , s);
	// 		int n = s.size();
	// 		for(int i = 0 ; i < n ; i++){
	// 			input[i] = s[i];
	// 		}

	// 	input[n] = '\0';

	// 	send(connection , input , strlen(input)+1 , 0);
	// 	}
	// }
	close(serverSocketHandler);
	return 0;

}
