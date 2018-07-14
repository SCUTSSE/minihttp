#include "httpsvr.h"
#include <utility>
httpsvr::httpsvr(const std::string& address, const std::string& port,const std::string& doc_root):io_svr(1),acceptor_(io_svr),connection_manager_(),request_handler_(doc_root)
{
	do_stop(); //ִ��������
	boost::asio::ip::tcp::resolver resolver(io_svr);  
	boost::asio::ip::tcp::endpoint endpoint =*resolver.resolve(address,port).begin(); //tcp�ս��
	acceptor_.open(endpoint.protocol()); //�Զ�ӦЭ��򿪽�����(tcp)
	acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true)); //������ַ���ã���ֹlinuxϵͳ��ip��Դ����ʧ�����⣩
	acceptor_.bind(endpoint); //���ս��
	acceptor_.listen(); //��ʼ����
	do_accept();//�����յ������ݰ�
}
void httpsvr::run()
{
	io_svr.run();//����io_service
}
void httpsvr::do_accept()
{
	acceptor_.async_accept(
		[this](boost::system::error_code ec, boost::asio::ip::tcp::socket socket) //lambda���ʽ������������
		{
				if (!acceptor_.is_open()) return; //�����������ʧ��
				if (!ec) //û�г��ִ���
				{
					connection_manager_.start(std::make_shared<connection>(std::move(socket), connection_manager_, request_handler_));
				}
				do_accept();
		}
	);
}
void httpsvr::do_stop() //ֹͣ����������
{
	acceptor_.close(); //�رս�������ֹͣ�������ݣ�
	connection_manager_.stop_all(); //�ر���������
}
