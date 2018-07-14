#include "connection.h"
#include <utility>
#include <vector>
#include "connectionmanager.h"
#include "requesthandler.h"
void connection::do_read()
{
	std::clog << socket_.remote_endpoint().address() << std::endl;//连接日志
	auto self(shared_from_this()); //this的shareptr指针
	socket_.async_read_some(boost::asio::buffer(buffer_), //asio异步读取
		[this,self](boost::system::error_code ec, std::size_t bytes_transferred) 
		{
			if (!ec) //没有错误
			{
				requestparser::result_type result; 
				std::tie(result,std::ignore)=request_parser_.parse(request_, buffer_.data(), buffer_.data()+bytes_transferred);//获得result
				if (result==requestparser::good) //正常
				{
					request_handler_.handlerequest(request_, reply_);//处理请求
					do_write();
				}
				else
				if (result==requestparser::bad) //错误
				{
					reply_=reply::stock_reply(reply::bad_request); //返回http400
					do_write();
				}
				else do_read(); //没有完成读取(interdemined)
			}
			else
			if (ec!=boost::asio::error::operation_aborted)
			connection_manager_.stop(shared_from_this()); //关闭连接	
		}
	);
}
void connection::do_write()
{
	auto self(shared_from_this()); //this的shareptr指针
	boost::asio::async_write(socket_,reply_.to_buffers(), //asio异步写入
		[this, self](boost::system::error_code ec, std::size_t)
		{
			if (!ec)
				{
					boost::system::error_code ignored_ec;
					socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both,ignored_ec); //关闭socket连接
				}
				if (ec!=boost::asio::error::operation_aborted) connection_manager_.stop(shared_from_this()); //停止连接
		}
	);
}