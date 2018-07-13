#include"requesthandler.h"
#include<fstream>
#include<sstream>
#include<string>
#include"mime_types.h"
#include"svr_reply.h"
#include"request.h"
#define default_pages "index.html"
void requesthandler::handlerequest(const request& req, reply& rep)
{
	std::string request_path;
	if (!url_decode(req.uri, request_path)|| request_path.empty() || request_path[0] != '/' || request_path.find("..") != std::string::npos)
	{
		rep=reply::stock_reply(reply::bad_request);
		return;
	}
	if (request_path[request_path.size() - 1] == '/') request_path+=default_pages;
	std::size_t last_slash=request_path.find_last_of("/");
	std::size_t last_dot=request_path.find_last_of(".");
	std::string extension;
	if (last_dot!=std::string::npos && last_dot>last_slash) extension=request_path.substr(last_dot+1);
	std::string full_path=doc_root_+request_path;
	std::ifstream is(full_path.c_str(),std::ios::in|std::ios::binary);
	if (!is)
	{
		rep=reply::stock_reply(reply::not_found); //404错误
		return;
	}
	rep.status = reply::ok;//http 200
	char buf[512];
	while (is.read(buf,sizeof(buf)).gcount()>0) rep.content.append(buf,is.gcount()); //getfile
	rep.headers.resize(2); //标准http响应标头
	rep.headers[0].name = "Content-Length";
	rep.headers[0].value = std::to_string(rep.content.size());
	rep.headers[1].name = "Content-Type";
	rep.headers[1].value = mime_types::extension_to_type(extension);
}
bool requesthandler::url_decode(const std::string& in, std::string& out) 
{
	out.clear();
	out.reserve(in.size());
	for (int i=0;i<in.size();++i)
	{
		if (in[i]=='%')
		{
			if (i+3<=in.size())
			{
				int prime = 0;
				std::istringstream is(in.substr(i + 1,2));
				if (is>>std::hex>>prime)
				{
					out+=static_cast<char>(prime);
					i+=2;
				}
				else return false;
			}
			else return false;	
		}
		else if (in[i]=='+') out+=' ';else out+=in[i];	
	}
	return true;
}