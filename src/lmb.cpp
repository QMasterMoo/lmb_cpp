#include <iostream>
#include <fstream>

#include "IRCconnector.h"
#include "lib/json.hpp"

using namespace std;
using json = nlohmann::json;

int main() {

    //Read in config
    ifstream configFile("config.json");
    json config;
    configFile >> config;

	//Connect to IRC server
    IRC irc(config["irc_server_address"], config["irc_server_port"], 
            config["irc_server_channel"], config["bot_username"], config["bot_password"]);

    irc.establishConnection();

    return 0;
}
