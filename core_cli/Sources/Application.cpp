#include "Application.hpp"

#include "Library.hpp"
#include "Runtime.hpp"
#include "Console.hpp"
#include "Exception.hpp"

#include "gnuplot-iostream.h"

namespace cr = CppReadline;
using ret = cr::Console::ReturnCode;

int main(int argc, char *args[])
{
	try
	{
		Core::Application* app = new Core::Application("path.sc", "config.sc");
		app->go();
	} catch (Core::Exception& e)
	{
		Core::Exception::die(e.getDescription(), "error.log");
		return 1;
	}
	return 0;
}


unsigned info(const std::vector<std::string> &)
{
	std::cout
			<< "Welcome to the example console. This command does not really\n"
			<< "do anything aside from printing this statement. Thus it does\n"
			<< "not need to look into the arguments that are passed to it.\n";
	return ret::Ok;
}

// In this command we implement a basic calculator
unsigned calc(const std::vector<std::string> & input)
{
	if (input.size() != 4)
	{
		// The first element of the input array is always the name of the
		// command as registered in the console.
		std::cout << "Usage: " << input[0] << " num1 operator num2\n";
		// We can return an arbitrary error code, which we can catch later
		// as Console will return it.
		return 1;
	}
	double num1 = std::stod(input[1]), num2 = std::stod(input[3]);

	char op = input[2][0];

	double result;
	switch (op)
	{
	case '*':
		result = num1 * num2;
		break;
	case '+':
		result = num1 + num2;
		break;
	case '/':
		result = num1 / num2;
		break;
	case '-':
		result = num1 - num2;
		break;
	default:
		std::cout << "The inserted operator is not supported\n";
		// Again, we can return an arbitrary error code to catch it later.
		return 2;
	}
	std::cout << "Result: " << result << '\n';
	return 0;
}

namespace Core
{

namespace cr = CppReadline;
using ret = cr::Console::ReturnCode;

unsigned info(const std::vector<std::string> &)
{
	std::cout
			<< "Welcome to the example console. This command does not really\n"
			<< "do anything aside from printing this statement. Thus it does\n"
			<< "not need to look into the arguments that are passed to it.\n";
	return ret::Ok;
}

// In this command we implement a basic calculator
unsigned calc(const std::vector<std::string> & input)
{
	if (input.size() != 4)
	{
		// The first element of the input array is always the name of the
		// command as registered in the console.
		std::cout << "Usage: " << input[0] << " num1 operator num2\n";
		// We can return an arbitrary error code, which we can catch later
		// as Console will return it.
		return 1;
	}
	double num1 = std::stod(input[1]), num2 = std::stod(input[3]);

	char op = input[2][0];

	double result;
	switch (op)
	{
	case '*':
		result = num1 * num2;
		break;
	case '+':
		result = num1 + num2;
		break;
	case '/':
		result = num1 / num2;
		break;
	case '-':
		result = num1 - num2;
		break;
	default:
		std::cout << "The inserted operator is not supported\n";
		// Again, we can return an arbitrary error code to catch it later.
		return 2;
	}
	std::cout << "Result: " << result << '\n';
	return 0;
}

using namespace CppReadline;

//static Application singletonApplication;

#define errorNULL throw Exception( "null pointer");

Application::Application(std::string path, std::string configFile) :
		Console(">> ")
{
	_exit = false;
	this->path = path;
	this->config = configFile;
}

Application::~Application()
{
	// empty
}

void Application::init()
{
	Library::getSingletonPtr()->loadConfigFile("config.conf");
	// We create a console. The '>' character is used as the prompt.
	// Note that multiple Consoles can exist at once, as they automatically
	// manage the underlying global readline state.

//	const char* prompt = ">>> ";
//    cr::Console c(prompt);

	// Here we register a new command. The string "info" names the command that
	// the user will have to type in in order to trigger this command (it can
	// be different from the function name).
	registerCommand("info", info);
	registerCommand("calc", calc);

	// Here we call one of the defaults command of the console, "help". It lists
	// all currently registered commands within the console, so that the user
	// can know which commands are available.
	executeCommand("help");

	// Here we try to call a script. The script is read line by line, and each line
	// (be it empty or not) is treated as a separate command. The execution is stopped
	// as soon as any command returns an error.
//    c.executeFile("exampleScript");

	// This basic loops continues to read input from the user until a command returns
	// the termination code (ret::Quit). Here it would be one of the default
	// quitting commands ("quit" or "exit").
	/*
	 * while ( c.readLine() != ret::Quit );
	 */

	// Otherwise we can modify the code to catch Console error code
}

void Application::quit()
{
	this->_exit = true;
}

void Application::loop()
{
	std::string in, in_prev;
//	Runtime* tt = Runtime::getSingletonPtr();

	int retCode;
	do
	{
		retCode = readLine();
		// We can also change the prompt based on last return value:
		if (retCode == ret::Ok)
			setGreeting(">> ");
		else
			setGreeting(">> ");

		if (retCode == 1)
		{
			std::cout << "Received error code 1\n";
		}
		else if (retCode == 2)
		{
			std::cout << "Received error code 2\n";
		}
	} while (retCode != ret::Quit);

	quit();

//	while (_exit != true) {
//		printf("> ");
//		std::cin >> in;
////		tt->stop(in_prev);
////		tt->start(in);
//		in_prev = in;
//		if (in == "exit") {
//			quit();
//		} else if (in == "add") {
//			std::string x, y;
//			std::cin >> x;
//			std::cin >> y;
//			if (!x.empty() && !y.empty()) {
//				Library::getSingletonPtr()->addParam(x, y);
//			}
//		} else if (in == "show") {
//			Library::getSingletonPtr()->printAll();
//		} else if (in == "get") {
//			std::string x;
//			std::cin >> x;
//			std::cout << Library::getSingletonPtr()->getParam(x) << std::endl;
//		} else if (in == "start") {
//			std::string x;
//			std::cin >> x;
//			tt->start(x);
//		} else if (in == "stop") {
//			std::string x;
//			std::cin >> x;
//			tt->stop(x);
//		} else if (in == "time") {
//			tt->print();
//		} else {
//			std::cout << "LOL:" << std::endl;
//		}
	//handle(in)
}

void Application::handle(std::string msg)
{
	if (msg == "exit")
	{
		quit();
	}
	else if (msg.empty() || msg != "exit")
	{
		std::cout << "Wrong word!" << std::endl;
	}
}

void Application::kill()
{
	//empty
}

void Application::clear(void)
{
//	delete Log::getSingletonPtr();
//	delete PathList::getSingletonPtr();
//	delete Runtime::getSingletonPtr();
//	delete CfgTable::getSingletonPtr();
}

void Application::go(void)
{
	init();
	loop();
	clear();
	kill();
}

}



//int main()
//{
//	Gnuplot gp;
//
//	std::vector<std::pair<double, double> > xy_pts_A;
//	for(double x=-2; x<2; x+=0.01) {
//		double y = x*x*x;
//		xy_pts_A.push_back(std::make_pair(x, y));
//	}
//
//	std::vector<std::pair<double, double> > xy_pts_B;
//	for(double alpha=0; alpha<1; alpha+=1.0/24.0) {
//		double theta = alpha*2.0*3.14159;
//		xy_pts_B.push_back(std::make_pair(cos(theta), sin(theta)));
//	}
//
//	gp << "set xrange [-2:2]\nset yrange [-2:2]\n";
//	// Data will be sent via a temporary file.  These are erased when you call
//	// gp.clearTmpfiles() or when gp goes out of scope.  If you pass a filename
//	// (e.g. "gp.file1d(pts, 'mydata.dat')"), then the named file will be created
//	// and won't be deleted (this is useful when creating a script).
//	gp << "plot" << gp.file1d(xy_pts_A) << "with lines title 'cubic',"
//		<< gp.file1d(xy_pts_B) << "with points title 'circle'" << std::endl;
//
//
//	return 0;
//}
