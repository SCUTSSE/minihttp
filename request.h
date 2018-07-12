#pragma once
#include <string>
#include <vector>
#include "httpheader.h"
struct request //url 
{
	std::string method; //请求协议(post/get等）
	std::string uri; //(uniform resource indentifier)统一资源标识符
	int http_version_major; //http主版本号 1/2 目前几乎全为1
	int http_version_minor; //http副版本号 一般也为1 即http1.1
	std::vector<header> headers; //请求头部格式 name=value
};