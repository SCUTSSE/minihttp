#ifndef CONNECTION_HEADER
#define CONNECTION_HEADER
#include <array>
#include <memory>
#include <boost/asio.hpp>
#include "svr_reply.h"
#include "request.h"
#include "requesthandler.h"
#include "requestparser.h"
class connectionmanager; //forward use
class connection: public std::enable_shared_from_this<connection>,boost::noncopyable
{
	public:
		explicit connection(boost::asio::ip::tcp::socket socket,connectionmanager& manager, requesthandler& handler);
		void start();
		void stop();
	private:
		void do_read();
		void do_write();
		boost::asio::ip::tcp::socket socket_;
		connectionmanager& connection_manager_;
		requesthandler& request_handler_;
		std::array<char, 8192> buffer_;
		request request_;
		requestparser request_parser_;
		reply reply_;
};
typedef std::shared_ptr<connection> connection_ptr;
#endif