#pragma once
#include<boost/asio.hpp>
#include<string>
#include"connection.h"
#include"connection_manager.h"
#include"request_handler.h"
using std::string;
using boost::asio::io_context;
using boost::asio::signal_set;
using boost::asio::ip::tcp;
class server
{
	public:
		server(const string& addr, const string&	port, const string& wwwroot);
		void run();
	private:
		void do_accept();
		void do_await();
		io_context iocontest;
		signal_set signals;
		tcp::acceptor acceptor1;
		connection_mananger con1;
		request_handler req1;
};