#ifndef IRCCONNECTOR_H
#define IRCCONNECTOR_H

#include <string>

using namespace std;

//Number of bytes to be received in each message
//Note: twitch has a max of 500 messages, but we need to account
//      ":moomasterq!moomasterq@moomasterq.tmi.twitch.tv PRIVMSG" etc.
//      There is a lot of stuff in front of messages
const int BUFFER_SIZE = 1024;

struct EmptyMessage : public exception {
	const char * what() const throw() {
		return "IRC::received empty message from IRC server";
	}
};

class IRC {
public:
	//Initialize all the needed values
	IRC(string serverAdress, int serverPort, string channel, string botUsername, string botPassword);

	//Connect to server, connect
	bool establishConnection();

	//Close conection, usually used to reopen it later
	bool closeConnection();

	//Receive message
	string receive();

private:
	string serverAdress;
	string channel;
	string botUsername;
	string botPassword;
	int serverPort;

	//socketID for sending and receiving
	int sockd;
};


#endif