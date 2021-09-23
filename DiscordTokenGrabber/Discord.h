#pragma once
#include <nlohmann/json.hpp>

using json = nlohmann::json;
namespace discord
{
	json make_embed_fields(json data, std ::string json);
	json make_discord_message(json embed, json data);
}
