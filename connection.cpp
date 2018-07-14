#include "connection.h"
#include <utility>
#include <vector>
#include "connectionmanager.h"
#include "requesthandler.h"
void connection::do_read()
{
	std::clog << socket_.remote_endpoint().address() << std::endl;//������־
	auto self(shared_from_this()); //this��shareptrָ��
	socket_.async_read_some(boost::asio::buffer(buffer_), //asio�첽��ȡ
		[this,self](boost::system::error_code ec, std::size_t bytes_transferred) 
		{
			if (!ec) //û�д���
			{
				requestparser::result_type result; 
				std::tie(result,std::ignore)=request_parser_.parse(request_, buffer_.data(), buffer_.data()+bytes_transferred);//���result
				if (result==requestparser::good) //����
				{
					request_handler_.handlerequest(request_, reply_);//��������
					do_write();
				}
				else
				if (result==requestparser::bad) //����
				{
					reply_=reply::stock_reply(reply::bad_request); //����http400
					do_write();
				}
				else do_read(); //û����ɶ�ȡ(interdemined)
			}
			else
			if (ec!=boost::asio::error::operation_aborted)
			connection_manager_.stop(shared_from_this()); //�ر�����	
		}
	);
}
void connection::do_write()
{
	auto self(shared_from_this()); //this��shareptrָ��
	boost::asio::async_write(socket_,reply_.to_buffers(), //asio�첽д��
		[this, self](boost::system::error_code ec, std::size_t)
		{
			if (!ec)
				{
					boost::system::error_code ignored_ec;
					socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both,ignored_ec); //�ر�socket����
				}
				if (ec!=boost::asio::error::operation_aborted) connection_manager_.stop(shared_from_this()); //ֹͣ����
		}
	);
}