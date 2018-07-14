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
		httpsvr(const std::string& address, const std::string& port,const std::string& doc_root); //构造函数
		void run();  
		~httpsvr() { do_stop(); }
	private:
		void do_accept(); //接受数据
		void do_stop(); //停止服务器
		boost::asio::io_service io_svr; //asio的核心组件
		boost::asio::ip::tcp::acceptor acceptor_; //tcp接收器
		connectionmanager connection_manager_; //连接管理
		requesthandler request_handler_; //请求处理(POST操作暂时不支持)
};
