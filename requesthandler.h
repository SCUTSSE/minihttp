#pragma once
#include <string>
#include<boost/noncopyable.hpp>
struct reply;
struct request;
class requesthandler:public boost::noncopyable
{
	public:
		requesthandler(const std::string& doc_root) :doc_root_(doc_root) {}; //构造函数
		void handlerequest(const request& req, reply& rep);  //请求处理
	private:
		std::string doc_root_; //文档地址
		static bool url_decode(const std::string& in, std::string& out); //url解码 16进制ascii转字符
};