#include <iostream>
using namespace std;


class User{
	string userName;
	string password;
	int userType;
	friend class Authenticate;
public:
	User(string userName, string password, int userType){
		this->userName = userName;
		this->password = password;
		this->userType = userType;
	}
	string getType(string username);
	string getUsername(){
		return userName;
	}


};
class Authenticate {
	string userName;
	string password;
	// static Authenticate *instance;
public:
	bool loggedIn = false;
	string activUser;
	// Authenticate *init();
	Authenticate();
	bool Register(User*);
	bool login();
	bool isLoggedIn();
	void setLoggedIn();
	void logout();
	bool createUser(string userName, string password);
	int checkUserExistence(string userName);
	bool isUserExist(string userName);
	User *getUserDetails(string userName);
	
};

class Utilities{
public:
	void welcomeMenu();
	bool loginMenu(Authenticate &auth);
	void authenticationMenu(Authenticate &auth);
	vector<string> readFileLineByLine(const char *filename);
	void Exit();
};


class Client{
	
	public:
	int clientSocket;
	Client();
};