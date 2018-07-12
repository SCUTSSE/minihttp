#include<iostream>
#include<string>
#include<boost/asio.hpp>
#include <boost/program_options.hpp>
#include"httpsvr.h"
using namespace std;
namespace bpo = boost::program_options;
int main(int argc, char const* argv[])
{
	string address,port,docroot; //address ipaddress(ip地址) port 端口 docroot documentroot(文档地址)
	bpo::options_description opt("all allowed options");//提示信息
	bpo::variables_map vm;//变量储存容器
	opt.add_options()
		("address", bpo::value<string>(&address)->default_value("0.0.0.0"), "ip address")
		("port", bpo::value<string>(&port)->default_value("80"), "server port")
		("docroot", bpo::value<string>(&docroot)->default_value("."), "website root")
		("help", "get help information");//加入要处理的变量参数
	try
	{
		bpo::store(parse_command_line(argc, argv, opt), vm); //储存变量
	}
	catch(...) //异常处理
	{ 
		cerr << "Illegal argument" << endl;
		cerr << "use --help to see all allowed options" << endl;
		return 0;
	}
	bpo::notify(vm); //解析
	if (vm.empty()) //无参数
	{
		cerr << "Illegal argument" << endl;
		cerr << "use --help to see all allowed options" << endl;
		return 0;
	}
	if (vm.count("help")) //--help参数
	{
		cout << opt << endl;
		return 0;
	}
	cout << "server info" << endl;
	cout << address << endl;
	cout << port << endl;
	cout << docroot << endl; //服务器当前信息打印
	httpsvr svr(address, port, docroot); //初始化http服务器
	svr.run(); //http服务器启动
	return 0;
}