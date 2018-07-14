#pragma once
#include<set>
#include<boost/noncopyable.hpp>
#include"connection.h"
class connectionmanager:public boost::noncopyable //���ӹ���
{
	public:
		connectionmanager(){ };
		void start(connection_ptr c)  //����һ��������
		{
			connections_.insert(c);
			c->start();
		}
		void stop(connection_ptr c) //�ر�һ������
		{
			connections_.erase(c);
			c->stop();
		}
		void stop_all() //�Ͽ�ȫ������
		{
			for (auto c:connections_) c->stop();
			connections_.clear();
		}
		std::set<connection_ptr> connections_; //���ӵ�ָ�����(shared_ptr)
};
