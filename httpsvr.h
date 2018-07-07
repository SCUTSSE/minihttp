#ifndef HTTPSVR_HEADER
#define HTTPSVR_HEADER
#include <boost/asio.hpp>
#include <boost/noncopyable.hpp>
#include <string>
#include "connection.h"
#include "connectionmanager.h"
#include "requesthandler.h"
class httpsvr:public boost::noncopyable
{
	public:
		explicit httpsvr(const std::string& address, const std::string& port,const std::string& doc_root);
		void run();
	private:
		void do_accept();
		void do_await_stop();
		boost::asio::io_context io_context_;
		boost::asio::signal_set signals_;
		boost::asio::ip::tcp::acceptor acceptor_;
		connectionmanager connection_manager_;
		requesthandler request_handler_;
};
#endif 