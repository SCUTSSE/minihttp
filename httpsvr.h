#pragma once
#include<boost/asio.hpp>
#include<boost/noncopyable.hpp>
#include<string>
#include"connection.h"
#include"connectionmanager.h"
#include"requesthandler.h"
class httpsvr:boost::noncopyable
{
	public:
		httpsvr(const std::string& address, const std::string& port,const std::string& doc_root); //���캯��
		void run();  
		~httpsvr() { do_stop(); }
	private:
		void do_accept(); //��������
		void do_stop(); //ֹͣ������
		boost::asio::io_service io_svr; //asio�ĺ������
		boost::asio::ip::tcp::acceptor acceptor_; //tcp������
		connectionmanager connection_manager_; //���ӹ���
		requesthandler request_handler_; //������(POST������ʱ��֧��)
};
