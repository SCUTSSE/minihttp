#include<iostream>
#include<string>
#include<boost/asio.hpp>
#include <boost/program_options.hpp>
#include"httpsvr.h"
using namespace std;
namespace bpo = boost::program_options;
int main(int argc, char const* argv[])
{
	string address,port,docroot;
	bpo::options_description opt("all allowed options");
	bpo::variables_map vm;
	opt.add_options()
		("address", bpo::value<string>(&address)->default_value("0.0.0.0"), "ip address")
		("port", bpo::value<string>(&port)->default_value("80"), "server port")
		("docroot", bpo::value<string>(&docroot)->default_value("."), "website root")
		("help", "get help information");
	try
	{
		bpo::store(parse_command_line(argc, argv, opt), vm);
	}
	catch(...)
	{
		cerr << "Illegal argument" << endl;
		cerr << "use --help to see all allowed options" << endl;
		return 0;
	}
	bpo::notify(vm);
	if (vm.empty())
	{
		cerr << "Illegal argument" << endl;
		cerr << "use --help to see all allowed options" << endl;
		return 0;
	}
	if (vm.count("help"))
	{
		cout << opt << endl;
		return 0;
	}
	cout << "server info" << endl;
	cout << address << endl;
	cout << port << endl;
	cout << docroot << endl;
	httpsvr svr(address, port, docroot);
	svr.run();
	return 0;
}