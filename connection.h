#pragma once
#include<iostream>
#include <array>
#include <memory>
#include <boost/asio.hpp>
#include "svr_reply.h"
#include "request.h"
#include "requesthandler.h"
#include "requestparser.h"
class connectionmanager; //��ǰ����
class connection: public std::enable_shared_from_this<connection>,boost::noncopyable
{
	public:
		explicit connection(boost::asio::ip::tcp::socket socket, connectionmanager& manager, requesthandler& handler) :socket_(std::move(socket)), connection_manager_(manager), request_handler_(handler) {};
		void start() { do_read(); } //��ʼ��ȡ
		void stop() { do_write(); } //д�뷵�� 
	private:
		void do_read(); //��ȡhttp����
		void do_write(); //д��http�������ݰ�
		boost::asio::ip::tcp::socket socket_;  //socket�׽��ִ������
		connectionmanager& connection_manager_; //���ӹ���
		request request_; //��������
		requestparser request_parser_; //�������
		requesthandler& request_handler_; //��������
		std::array<char,8192> buffer_; //���� һ��8192�ֽ�����
		reply reply_; //���ذ�
};
typedef std::shared_ptr<connection> connection_ptr;