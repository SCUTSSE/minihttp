#pragma once
#include <string>
namespace mime_types //http1.1 mime 类型定义
{
	struct mapping
	{
		const char* extension;
		const char* mime_type;
	} 
	mappings[] =
	{
		{ "gif","image/gif" },
		{ "htm","text/html" },
		{ "html","text/html" },
		{ "jpg","image/jpeg" },
		{ "png","image/png" }
	};//http 1.1 standard non css 
	std::string extension_to_type(const std::string& extension) //简单地通过扩展名推断mime类型
	{
		for (mapping m:mappings)
		{
			if (m.extension==extension) //找到对应类型
			{
				return m.mime_type;
			}
		}
		return "text/plain"; //css will be regarded as plain text
	}
} 