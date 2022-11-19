#include <bits/stdc++.h>
#include "classes.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define SIZE 1024
#define PORT 5200
using namespace std;

void Utilities::welcomeMenu(){
	for(auto x: Utilities::readFileLineByLine("decorate.txt")){
		cout<<x<<endl;
	}
}

vector<string> Utilities::readFileLineByLine(const char *filename){
	vector<string> v;
	ifstream openFile(filename);
	
	string temp;
	while (getline(openFile, temp)){
		v.push_back(temp);
	}
	openFile.close();
	
	return v;
}
void Utilities::authenticationMenu(Authenticate &auth){
	int option;
	do{
		string username;
	cout<<"Enter username to register: ";
	cin>>username;
	if(auth.isUserExist(username)){
		cout<<"\nUser is already Registered.\n1. Try again with different username\n2. Goto login\n";
		cout<<"Enter your option: ";
		cin>>option;
		if(option==1) continue;
		if(option==2) this->loginMenu(auth); cout<<auth.activUser<<endl; break; continue;
	}
	else{
		string password;
		cout<<"Enter password to register: ";
		cin>>password;
		bool result = auth.Register(new User(username, password, 2));
		if(result){
			cout<<"Hurreh! user registered sucessfully\n";
			cout<<"1. To login\n2. To exit\n";
			cout<<"Enter your choice: ";
			int op;
			cin>>op;
			if(op==1) this->loginMenu(auth);
			else if(op==2) this->Exit();
		}
	}
	}while(option==1);
}


// const char *get_filename_ext(const char *filename) {
//     const char *dot = strrchr(filename, '.');
//     if(!dot || dot == filename) return "";
//     return dot + 1;
// }

// void send_file(FILE *fp, int sockfd, const char *ext){
//   int n;
//   char data[SIZE] = {0};
//  send(sockfd, ext, sizeof(ext), 0);
//   while(fgets(data, SIZE, fp) != NULL) {
//     if (send(sockfd, data, sizeof(data), 0) == -1) {
//       perror("Error in sending file.");
//       exit(1);
//     }
//     bzero(data, SIZE);
//   }
// }

// void write_file(int sockfd){
//   int n;
//   FILE *fp;
//   char filename[] = "received.";
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

Client::Client(){
	int clientSocket , serverSocket , receiveMsgSize;
	clientSocket = socket(AF_INET , SOCK_STREAM , 0);
	if(clientSocket < 0)
        {
		cout << "Creation of client socket failed" << endl;
		// return 0;
        }
	struct sockaddr_in serverAddr , clientAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serverAddr.sin_port = htons(PORT);
	if(connect(clientSocket ,  (struct sockaddr*) & serverAddr , sizeof(serverAddr)) < 0)
	{
		cout << "Connection Error..." << endl;
		// return 0;
	}
	else
	{
		cout << "\t\tConnection Established..." << endl;
	}

	this->clientSocket = clientSocket;

	// while(true)
	// {
	// 	string s;
	// 	char input[SIZE];
	// 	cout << "Client : ";
	// 	getline(cin , s);
	// 	int n = s.size();
	// 	for(int i = 0 ; i < n ; i++)
	// 	{
	// 		input[i] = s[i];
	// 	}
	// 	input[n] = '\0';
	// 	send(clientSocket , input , strlen(input)+1 , 0);
	// 	char receiveMessage[SIZE];
	// 	int rMsgSize = recv(clientSocket , receiveMessage , SIZE , 0);
	// 	if(rMsgSize < 0)
	// 	{
	// 		cout << "Packet recieve failed." << endl;
	// 		// return 0;
	// 	}
	// 	else if(rMsgSize == 0)
	// 	{
	// 		cout << "Server is off." << endl;
	// 		// return 0;
	// 	}

	// 	if(receiveMessage[0] == 'b' && receiveMessage[1] == 'y' && receiveMessage[2] == 'e')
	// 	{
	// 		cout << "\nConnection ended... take care bye bye... " ;
	// 		break;
	// 	}
	// 	cout << "received server : " << receiveMessage <<endl;
	// }
}


void clientOperationsMenu(){
	cout<<"1. Upload file\n2. Show files\n3.Delete file\n";
	cout<<"Enter option: ";
	int option;
	cin>>option;

	if(option==1){
		//upload the file
		
	}
	else if(option==2){
		//List the files
	}
	else if(option==3){
		//Delete the file
	}else{
		cout<<"invalid input\n";
	}

}



void Utilities::Exit(){
	cout<<"Thank you for choosing us!\nHave a nice day!!\n";
	exit(0);
}

bool Utilities::loginMenu(Authenticate &auth){
	cout<<"\nWelcome to login\n\n";
	bool validUser=false, validPassword=false;
		string _username, username;
	do{
		cout<<"Enter username: ";
		cin>>_username;
		if(auth.isUserExist(_username)){
			validUser = true;
		}
		else{
			cout<<"Opps! user not exist. Please enter a valid username.\n";
		}
	}while(!validUser);

	do{
		string _password, password;
		cout<<"Enter password: ";
		cin>>_password;
		
		ifstream fin("users.txt",ios::in);
		string userType;
		while(fin>>username>>password>>userType){
			// cout<<password<<" "<<_password<<endl;
			if(_password==password and _username==username){
				validPassword=true;
			}
		}
		if(!validPassword){
			cout<<"Wrong Password, Try again\n";
		}
	}while(!validPassword);

	if(validUser and validPassword){
		cout<<"logged in sucessfully"<<endl;
		auth.activUser = _username;
		auth.setLoggedIn();
		//User authentcated
		// clientOperationsMenu();
		// auth.carBooking();
		return true;
	}
	return false;
}
Authenticate::Authenticate(){

}

void Authenticate::setLoggedIn(){
	this->loggedIn = true;
}
void Authenticate::logout(){
	this->loggedIn = false;
	this->activUser= "";

}

bool Authenticate::isLoggedIn(){
	return this->loggedIn;
}

User *Authenticate:: getUserDetails(string username){
	return NULL;
}

void splitString(string str, string delimiter = " ")
{
    int start = 0;
    int end = str.find(delimiter);
    while (end != -1) {
        cout << str.substr(start, end - start) << endl;
        start = end + delimiter.size();
        end = str.find(delimiter, start);
    }
    cout << str.substr(start, end - start);
}

bool Authenticate::isUserExist(string username){
	ifstream openFile2("users.txt");
	string line;
	while(!openFile2.eof()){
		getline(openFile2, line);
		string _username;
		for(auto x: line){
			if(x==' ') break;
			else _username += x;
		}
		if(username==_username){
			return true;
		}
	}
	openFile2.close();

	return false;
}

bool Authenticate:: Register(User *urs){
	
	ofstream writeFile("users.txt", ios::app);
	if(!writeFile) return false;
	writeFile<<urs->userName<<" "<<urs->password<<" "<<urs->userType<<"\n";
	writeFile.close();
	return true;
}


bool Authenticate:: login(){
	
	this->loggedIn = true;
	return "true";
}

