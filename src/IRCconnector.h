#ifndef IRCCONNECTOR_H
#define IRCCONNECTOR_H

#include <string>

using namespace std;

//Number of bytes to be received in each message
//Note: twitch has a max of 500 messages, but we need to account
//      ":moomasterq!moomasterq@moomasterq.tmi.twitch.tv PRIVMSG" etc.
const int BUFFER_SIZE = 768;

class IRC {
public:
	//Initialize all the needed values
	IRC(string serverAdress, int serverPort, string channel, string botUsername, string botPassword);

	//Connect to server, connect
	bool establishConnection();
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