#include <string>
#include <string.h>//Needed for memset
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <iostream>
#include <exception>

#include "IRCconnector.h"

IRC::IRC(string serverAdress, int serverPort, string channel, string botUsername, string botPassword){
	this->serverAdress = serverAdress;
	this->serverPort = serverPort;
	this->channel = channel;
	this->botUsername = botUsername;
	this->botPassword = botPassword;
}

void IRC::establishConnection(){
	//Resolve the server hostname to an address
    struct hostent *host; 
    host = gethostbyname(serverAdress.c_str());

    //Setup the socket
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons((uint16_t)(serverPort));
    addr.sin_addr = *((in_addr*)host->h_addr);
    sockd = socket(AF_INET, SOCK_STREAM, 0);
    //Make sure we properly connect
    if (connect(sockd, (struct sockaddr*)&addr, sizeof(addr)) != 0){
        throw runtime_error("IRC::connection to server failed");
    }

    //Create message strings
    string pass = "PASS " + botPassword + '\n';
    string user = "USER " + botUsername + '\n';
    string nick = "NICK " + botUsername + '\n';
    string chan = "JOIN #" + channel + '\n';

    //CAP REQ messages so we get enough informtaion
    send(sockd, "CAP REQ :twitch.tv/membership\n", 30, 0);
    send(sockd, "CAP REQ :twitch.tv/commands\n",   28, 0);
    send(sockd, "CAP REQ :twitch.tv/tags\n",       24, 0);

    //Send information to connect to channel
 	send(sockd, pass.c_str(), pass.size(), 0);
    send(sockd, nick.c_str(), nick.size(), 0);
    send(sockd, user.c_str(), user.size(), 0);
    send(sockd, chan.c_str(), chan.size(), 0);
}

void IRC::closeConnection(){
	close(sockd);
	sockd = -1;
}

string IRC::receive(){
    //receive messages
    char sockbuff[BUFFER_SIZE] = {'\0'}; 
    recv(sockd, sockbuff, BUFFER_SIZE, 0); 
    //Check for empty message
    if (sockbuff[0] == '\0'){
    	throw EmptyMessage();
    }
    return sockbuff;
}