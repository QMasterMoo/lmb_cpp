#include <string>
#include <string.h>//Needed for memset
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <iostream>

#include "IRCconnector.h"

IRC::IRC(string serverAdress, int serverPort, string channel, string botUsername, string botPassword){
	this->serverAdress = serverAdress;
	this->serverPort = serverPort;
	this->channel = channel;
	this->botUsername = botUsername;
	this->botPassword = botPassword;
}

bool IRC::establishConnection(){
	//Resolve the server hostname to an address
    struct hostent *host; 
    host = gethostbyname(serverAdress.c_str());

    //Setup the socket
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons((uint16_t)(serverPort));
    addr.sin_addr = *((in_addr*)host->h_addr);
    int sockd = socket(AF_INET, SOCK_STREAM, 0);
    connect(sockd, (struct sockaddr*)&addr, sizeof(addr));

    //Create message strings
    string pass = "PASS " + botPassword + '\n';
    string user = "USER " + botUsername + '\n';
    string nick = "NICK " + botUsername + '\n';
    string chan = "JOIN #" + channel + '\n';

    //Send information to connect to channel
 	send(sockd, pass.c_str(), pass.size(), 0);
    send(sockd, nick.c_str(), nick.size(), 0);
    send(sockd, user.c_str(), user.size(), 0);
    send(sockd, chan.c_str(), chan.size(), 0);

    //TODO: move this to receive function
    //receive messages
	int connected = 0;
    char sockbuff[BUFFER_SIZE];
    while (connected < 1) { 
            memset(&sockbuff, '\0', BUFFER_SIZE);
            recv(sockd, sockbuff, BUFFER_SIZE, 0); 
            cout << sockbuff << endl;
    }

    return true;
}