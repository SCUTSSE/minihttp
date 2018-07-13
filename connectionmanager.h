#pragma once
#include<set>
#include<boost/noncopyable.hpp>
#include"connection.h"
class connectionmanager:public boost::noncopyable //连接管理
{
	public:
		connectionmanager(){ };
		void start(connection_ptr c)  //加入一个新连接
		{
			connections_.insert(c);
			c->start();
		}
		void stop(connection_ptr c) //关闭一个连接
		{
			connections_.erase(c);
			c->stop();
		}
		void stop_all() //断开全部连接
		{
			for (auto c:connections_) c->stop();
			connections_.clear();
		}
		std::set<connection_ptr> connections_; //连接的指针管理(shared_ptr)
};
