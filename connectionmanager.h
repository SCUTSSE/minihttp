
#ifndef CONNECTIONMANAGER_HEADER
#define CONNECTIONMANAGER_HEADER
#include<set>
#include<boost/noncopyable.hpp>
#include"connection.h"
class connectionmanager:public boost::noncopyable
{
	public:
		connectionmanager(){ };
		void start(connection_ptr c)
		{
			connections_.insert(c);
			c->start();
		}
		void stop(connection_ptr c)
		{
			connections_.erase(c);
			c->stop();
		}
		void stop_all()
		{
			for (auto c:connections_) c->stop();
			connections_.clear();
		}
	private:
		std::set<connection_ptr> connections_;
};
#endif