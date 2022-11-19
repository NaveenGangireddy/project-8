#include <bits/stdc++.h>
#include "classes.h"
#include <filesystem>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
// #include <glob.h>
#define LOG_LEVEL DEBUG
#include "logger/Logger.h"
#include "src/operations/_write.C"
#include "src/operations/_read.C"
#include "server/init_server.C"

#define SIZE 1024
using namespace std;
namespace fs = filesystem;

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

// void write_file(int sockfd)
// {
// 	int n;
// 	FILE *fp;
// 	char filename[] = "received_";
// 	char buffer[SIZE];

// 	n = recv(sockfd, buffer, SIZE, 0);
// 	strcat(filename, buffer);
// 	printf("%s\n", filename);
// 	fp = fopen(filename, "w");
// 	while (1)
// 	{
// 		n = recv(sockfd, buffer, SIZE, 0);
// 		if (n <= 0)
// 		{
// 			break;
// 			return;
// 		}
// 		fprintf(fp, "%s", buffer);
// 		bzero(buffer, SIZE);
// 	}
// 	return;
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
	debug("debug log");
	cout << "HI" << endl;
	// info("informational log");
	// notice("notice log");
	Authenticate auth;
	Utilities u;

Login_menu:
	u.welcomeMenu();
	cout << "\n\n";
	cout << "1. -  Login\n2. -  Register\n3. -  Exit\n\n";
	int authOption;

	cout << "Enter your option: ";
	cin >> authOption;
	cout << "\n\n";
	switch (authOption)
	{
	case 1: // login
		u.loginMenu(auth);
		break;
	case 2: // Register
		u.authenticationMenu(auth);
		break;
	case 3:
		u.Exit();
	}

	if (auth.loggedIn)
	{
		// user authenticated
		cout << auth.activUser;

		// invoke the server
		start_server();
		// client creation
		Client c;
		do
		{
			cout << "1. Upload file\n2. Download file\n3. Show files\n4. Exit\n";
			cout << "Enter option: ";
			int option;
			cin >> option;
			switch (option)
			{
			case 1:
			{ // Upload
				FILE *fp;
				char command[] = "upload";
				send(c.clientSocket, command, sizeof(command) + 1, 0);
				const char *filename = "secure.h";
				fp = fopen(filename, "r");
				if (fp == NULL)
				{
					perror("Error in reading file.");
					exit(1);
				}
				send_file(fp, c.clientSocket, filename);
			}

			break;
			case 2:
				// Download
				{

					FILE *fp;
				char command[] = "download";
				send(c.clientSocket, command, sizeof(command) + 1, 0);
				sleep(1);
					char buffer[SIZE];
					int response_code = recv(c.clientSocket, buffer, SIZE, 0);
					if (response_code <= 0)
					{
						cout << "Something went wrong\n";
						exit(0);
					}

					cout << buffer << endl;

					// write_file(c.clientSocket);
				}
				break;
			case 3:
				// show files
				{
					string path = "/home/rjbabu1309/RajaBabu/sprint2/";
					for (const auto &entry : fs::directory_iterator(path))
						cout << entry.path() << endl;
				}
				break;
				// default:
				// 	cout << "Invalid input";
				// 	break;
			}

		} while (false);
	}
	else
	{
		// user is logged logged out or not authenticated
		cout << "User is not logged in\n";
		goto Login_menu;
	}

	return 0;
}