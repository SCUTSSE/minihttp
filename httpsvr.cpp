#include "httpsvr.h"
#include <utility>
httpsvr::httpsvr(const std::string& address, const std::string& port,const std::string& doc_root):io_svr(1),acceptor_(io_svr),connection_manager_(),request_handler_(doc_root)
{
	do_await_stop(); //关闭之前的连接
	boost::asio::ip::tcp::resolver resolver(io_svr);  
	boost::asio::ip::tcp::endpoint endpoint =*resolver.resolve(address,port).begin(); //tcp终结点（接收点）
	acceptor_.open(endpoint.protocol()); //以对应服务打开 (tcp)
	acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true)); //设置地址复用
	acceptor_.bind(endpoint); //绑定
	acceptor_.listen(); //监听端口
	do_accept();//开始接送数据
}
void httpsvr::run()
{
	io_svr.run();//启动
}
void httpsvr::do_accept()
{
	acceptor_.async_accept(
		[this](boost::system::error_code ec, boost::asio::ip::tcp::socket socket) //lambda表达式
		{
				if (!acceptor_.is_open()) return; //如果没有启动接受器
				if (!ec) //如果没有错误
				{
					connection_manager_.start(std::make_shared<connection>(std::move(socket), connection_manager_, request_handler_));
				}
				do_accept();
		}
	);
}
void httpsvr::do_await_stop() //关闭服务器
{
	acceptor_.close(); //关闭接受器
	connection_manager_.stop_all(); //停止所有连接
}
