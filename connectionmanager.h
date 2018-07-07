
#ifndef CONNECTIONMANAGER_HEADER
#define CONNECTIONMANAGER_HEADER
#include<set>
#include<boost/noncopyable.hpp>
#include"connection.h"
class connectionmanager:public boost::noncopyable
{
	public:
		connectionmanager();
		void start(connection_ptr c);
		void stop(connection_ptr c);
		void stop_all();
	private:
		std::set<connection_ptr> connections_;
};
#endif