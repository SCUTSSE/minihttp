#ifndef REQUESTHANDLER_HEADER
#define REQUESTHANDLER_HEADER
#include <string>
#include<boost/noncopyable.hpp>
struct reply;
struct request;
class requesthandler:public boost::noncopyable
{
	public:
		explicit requesthandler(const std::string& doc_root);
		void handlerequest(const request& req, reply& rep);
	private:
		std::string doc_root_;
		static bool url_decode(const std::string& in, std::string& out);
};
#endif 