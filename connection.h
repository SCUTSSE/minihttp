#pragma once
#include<iostream>
#include <array>
#include <memory>
#include <boost/asio.hpp>
#include "svr_reply.h"
#include "request.h"
#include "requesthandler.h"
#include "requestparser.h"
class connectionmanager; //提前引用
class connection: public std::enable_shared_from_this<connection>,boost::noncopyable
{
	public:
		explicit connection(boost::asio::ip::tcp::socket socket, connectionmanager& manager, requesthandler& handler) :socket_(std::move(socket)), connection_manager_(manager), request_handler_(handler) {};
		void start() { do_read(); } //开始读取
		void stop() { do_write(); } //写入返回 
		void do_read(); //读取http请求
		void do_write(); //写入http返回数据包
		boost::asio::ip::tcp::socket socket_;  //socket套接字传输控制
		connectionmanager& connection_manager_; //连接管理
		request request_; //连接请求
		requestparser request_parser_; //请求解析
		requesthandler& request_handler_; //处理请求
		std::array<char,8192> buffer_; //缓存 一次8192字节内容
		reply reply_; //返回包
};
typedef std::shared_ptr<connection> connection_ptr;