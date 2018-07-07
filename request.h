#ifndef REQUEST_HEADER
#define REQUEST_HEADER
#include <string>
#include <vector>
#include "httpheader.h"
struct request
{
	std::string method;
	std::string uri;
	int http_version_major;
	int http_version_minor;
	std::vector<header> headers;
};
#endif 