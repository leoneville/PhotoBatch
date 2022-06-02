#include "ArgumentParser.hpp"

#include <iostream>
#include <iomanip>

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "pt_BR");
	setlocale(LC_NUMERIC, "en_US");

	auto argParser = ArgumentParser{};
	argParser.RegisterFlag("rename");
	argParser.RegisterFlag("convert");
	argParser.RegisterFlag("resize");
	argParser.RegisterFlag("scale");
	argParser.RegisterOption("folder");
	argParser.RegisterOption("amount");

	argParser.Parse(argc, argv);

	std::cout << "Rename        : " << std::boolalpha << argParser.GetFlag("rename") << '\n';
	std::cout << "Convert       : " << std::boolalpha << argParser.GetFlag("convert") << '\n';
	std::cout << "Resize        : " << std::boolalpha << argParser.GetFlag("resize") << '\n';
	std::cout << "Scale         : " << std::boolalpha << argParser.GetFlag("scale") << '\n';
	std::cout << "Folder        : " << argParser.GetOptionAs<const std::string&>("folder") << '\n';
	std::cout << "Amount(float) : " << argParser.GetOptionAs<float>("amount") << '\n';
	std::cout << "Amount(int)   : " << argParser.GetOptionAs<int>("amount") << '\n';

	return 0;
}