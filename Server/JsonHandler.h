#ifndef JSON_HANDLER_H
#define JSON_HANDLER_H

#include "General.h"

class JsonHandler {
public:
    // 从HTTP请求中提取JSON
    std::string extractJsonFromHTTP(const std::string& http_request);
    
    // 解析JSON字符串
    bool parseJson(const std::string& json_str, Json::Value& json_value);
    
    // 将JSON对象转为字符串
    std::string writeJson(const Json::Value& json_value);
    
    // 创建响应
    Json::Value createResponse(bool success, const std::string& message);
};

#endif