#include <iostream>
#include <string>
#include <string.h>//Needed for memset
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>

//Number of bytes to be received in each message
//Note: twitch has a max of 500 messages, but we need to account
//      ":moomasterq!moomasterq@moomasterq.tmi.twitch.tv PRIVMSG" etc.
const int BUFFER_SIZE = 768;

using namespace std;

int main() {
    //Read in password from stdin
    //Note: will eventually use config file so this won't be needed
    string tempPass;
    cin >> tempPass;

	//Server connection information
    int port = 6667;
    string serv = "irc.chat.twitch.tv";
    string nick = "NICK lessermoobot\n";
    string user = "USER lessermoobot\n";
	string pass = "PASS " + tempPass + '\n';
	string chan = "JOIN #moomasterq\n";

    //Resolve the server hostname to an address
    struct hostent *host; 
    host = gethostbyname(serv.c_str());

    //Setup the socket
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons((uint16_t)(port));
    addr.sin_addr = *((in_addr*)host->h_addr);
    int sockd = socket(AF_INET, SOCK_STREAM, 0);

    //Connect to the socket
    connect(sockd, (struct sockaddr*)&addr, sizeof(addr));
    //Send information to connect to channel
    send(sockd, pass.c_str(), pass.size(), 0);
    send(sockd, nick.c_str(), nick.size(), 0);
    send(sockd, user.c_str(), user.size(), 0);
    send(sockd, chan.c_str(), chan.size(), 0);

    //Connect and receive messages
	int connected = 0;
    char sockbuff[BUFFER_SIZE];
    while (connected < 1) { 
            memset(&sockbuff, '\0', BUFFER_SIZE);
            recv(sockd, sockbuff, BUFFER_SIZE, 0); 
            cout << sockbuff << endl;
    }


    return 0;
}
