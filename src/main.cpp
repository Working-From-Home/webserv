#include "ServerConfig.hpp"
#include "Server.hpp"

#include <iostream>
#include <iomanip>
#include <vector>
#include <csignal>

#ifdef __linux__
	#define DEFAULT_PATH "config/ubuntu_webserv.conf";
#else
	#define DEFAULT_PATH "config/macos_webserv.conf";
#endif

static bool run = true;

std::string getUsage()
{
	return "usage: \n  ./webserv\n  ./webserv file.conf\n";
}

void parseArgs(int ac, char **av)
{
	std::string path = DEFAULT_PATH;
	if (ac == 2)
		path = av[1];
	else if (ac > 2)
	{
		std::cerr << "To many arguments." << std::endl;
		std::cerr << getUsage();
		exit(1);
	}
	try
	{
		ServerConfig::getInstance(path, "./mime.types");
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what();
		exit(1);
	}
}

void solidLine(int width, char ornament)
{
	std::cout << std::setw(width) << std::setfill(ornament);
	std::cout << ornament << std::endl;
}

void emptyLine(int width, char ornament)
{
	std::cout << ornament << std::setw(width - 2) << std::setfill(' ');
	std::cout << ' ' << ornament << std::endl;
}

void textLine(int width, char ornament, std::string text)
{
	int fillWidth = (width - 2 - text.size()) / 2;
	bool fill = (text.size() % 2 == 0 ? false : true);
	
	std::cout << ornament << std::setw(fillWidth) << std::setfill(' ');
	std::cout << ' ' << text;
	std::cout << std::setw(fillWidth) << std::setfill(' ');
	if (fill)
		std::cout << ' ' << ' ' << ornament << std::endl;
	else
		std::cout << ' ' << ornament << std::endl;
}

void prompt()
{
	int		width = 70;
	char	ornament = '.';

	std::cout << std::endl;
	solidLine(width, ornament);
	emptyLine(width, ornament);
	textLine(width, ornament, "Webserv - 42");
	emptyLine(width, ornament);
	textLine(width, ornament, "authors: hwinston, juligonz");
	emptyLine(width, ornament);
	solidLine(width, ornament);
	std::cout << std::endl;
}

void signalCallback(int signum) {
	std::cout << std::endl;
	if (signum == SIGTERM)
		std::cout << "SIGTERM signal received. ";
	else if (signum == SIGINT)
		std::cout << "SIGINT signal received. ";
	std::cout << "Shutting down..." << std::endl;
	std::cout << std::endl;
	run = false;
}

int main(int ac, char** av)
{
	parseArgs(ac, av);
	web::Server sh;
	signal(SIGINT, signalCallback);
	signal(SIGTERM, signalCallback);
	sh.setup();
	prompt();
	while (run)
		sh.routine();
	ServerConfig::__delete_singleton_instance(); // useless, but don't want to discuss about it during eval
	return 0;
}