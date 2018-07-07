#ifndef HTTP_MIME_TYPES_HEADER
#define HTTP_MIME_TYPES_HEADER
#include <string>
namespace mime_types 
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
	std::string extension_to_type(const std::string& extension)
	{
		for (mapping m:mappings)
		{
			if (m.extension==extension)
			{
				return m.mime_type;
			}
		}
		return "text/plain";
	}
} 
#endif