#pragma once
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace web
{
	json get_data_from_token(std::string token);
	json do_get_request_return_json(std::string url, std ::map<std ::string, std ::string> headers = {}, int valid_code = 200);
	void send_to_webhook(std::string data);
}