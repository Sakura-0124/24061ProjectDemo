#include "JsonHandler.h"


std::string JsonHandler::extractJsonFromHTTP(const std::string& http_request) {
    size_t pos = http_request.find("\r\n\r\n");
    if (pos == std::string::npos) {
        return "";
    }
    return http_request.substr(pos + 4);
}

bool JsonHandler::parseJson(const std::string& json_str, Json::Value& json_value) {
    Json::CharReaderBuilder builder;
    std::string errors;
    std::istringstream json_stream(json_str);
    return Json::parseFromStream(builder, json_stream, &json_value, &errors);
}

std::string JsonHandler::writeJson(const Json::Value& json_value) {
    Json::StreamWriterBuilder builder;
    return Json::writeString(builder, json_value);
}

Json::Value JsonHandler::createResponse(bool success, const std::string& message) {
    Json::Value response;
    response["status"] = success ? "success" : "error";
    response["message"] = message;
    return response;
}