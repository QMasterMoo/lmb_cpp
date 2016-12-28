#include <iostream>
#include <fstream>

#include "IRCconnector.h"
#include "lib/json.hpp"

using namespace std;
using json = nlohmann::json;

int main() {
    #ifdef DEBUG
        cout << "Debug Mode" << endl;
        cout << endl;
    #endif

    //Read in config
    ifstream configFile("config.json");
    json config;
    configFile >> config;

	//Connect to IRC server
    IRC irc(config["irc_server_address"], config["irc_server_port"], 
            config["irc_server_channel"], config["bot_username"], config["bot_password"]);
    try {
        irc.establishConnection();
    }
    catch (exception &e){
        cerr << "main::" << e.what() << endl;
        exit(1);
    }
    bool connected = true;
    while (connected){
        string message;
        try {
            message = move(irc.receive());
        }
        catch (EmptyMessage& e){
            cerr << e.what() << endl;
            //Restablish the connection
            irc.closeConnection();
            irc.establishConnection();
        }
        cout << message << endl;
    }

    return 0;
}
