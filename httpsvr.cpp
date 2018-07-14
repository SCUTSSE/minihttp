#include "httpsvr.h"
#include <utility>
httpsvr::httpsvr(const std::string& address, const std::string& port,const std::string& doc_root):io_svr(1),acceptor_(io_svr),connection_manager_(),request_handler_(doc_root)
{
	do_stop(); //执行清理工作
	boost::asio::ip::tcp::resolver resolver(io_svr);  
	boost::asio::ip::tcp::endpoint endpoint =*resolver.resolve(address,port).begin(); //tcp终结点
	acceptor_.open(endpoint.protocol()); //以对应协议打开接收器(tcp)
	acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true)); //启动地址复用（防止linux系统上ip资源申请失败问题）
	acceptor_.bind(endpoint); //绑定终结点
	acceptor_.listen(); //开始监听
	do_accept();//处理收到的数据包
}
void httpsvr::run()
{
	io_svr.run();//启动io_service
}
void httpsvr::do_accept()
{
	acceptor_.async_accept(
		[this](boost::system::error_code ec, boost::asio::ip::tcp::socket socket) //lambda表达式（匿名函数）
		{
				if (!acceptor_.is_open()) return; //如果接收器打开失败
				if (!ec) //没有出现错误
				{
					connection_manager_.start(std::make_shared<connection>(std::move(socket), connection_manager_, request_handler_));
				}
				do_accept();
		}
	);
}
void httpsvr::do_stop() //停止服务器运行
{
	acceptor_.close(); //关闭接收器（停止接受数据）
	connection_manager_.stop_all(); //关闭所有连接
}
