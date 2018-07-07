#include "httpsvr.h"
#include <signal.h>
#include <utility>
httpsvr::httpsvr(const std::string& address, const std::string& port,const std::string& doc_root):io_context_(1),signals_(io_context_),acceptor_(io_context_),connection_manager_(),request_handler_(doc_root)
{
		signals_.add(SIGINT); //allow ctrl+c
		signals_.add(SIGTERM); //allow terminate signal
		#if defined(SIGQUIT)
			signals_.add(SIGQUIT);
		#endif 
		do_await_stop();
		boost::asio::ip::tcp::resolver resolver(io_context_);
		boost::asio::ip::tcp::endpoint endpoint =*resolver.resolve(address, port).begin();
		acceptor_.open(endpoint.protocol());
		acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
		acceptor_.bind(endpoint);
		acceptor_.listen();
		do_accept();
}
void httpsvr::run()
{
	io_context_.run();
}

void httpsvr::do_accept()
{
	acceptor_.async_accept
	(
		[this](boost::system::error_code ec, boost::asio::ip::tcp::socket socket) //lambda equation
		{
				if (!acceptor_.is_open())
				{
					return;
				}
				if (!ec)
				{
					connection_manager_.start(std::make_shared<connection>(std::move(socket), connection_manager_, request_handler_));
				}
				do_accept();
		}
	);
}
void httpsvr::do_await_stop()
{
	signals_.async_wait
	(
		[this](boost::system::error_code /*ec*/, int /*signo*/)
		{
			acceptor_.close();
			connection_manager_.stop_all();
		}
	);
}