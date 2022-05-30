#include <iostream>
#include <iomanip>

class ArgumentParser
{
public:
	void RegisterFlag(const std::string& flag)
	{

	}

	bool GetFlag(const std::string& flag)
	{
		return false;
	}

	void Parse(int argc, char* argv[])
	{

	}

private:

};

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "portuguese");

	auto argParser = ArgumentParser{};
	argParser.RegisterFlag("rename");
	argParser.RegisterFlag("convert");
	argParser.RegisterFlag("resize");
	argParser.RegisterFlag("scale");

	argParser.Parse(argc, argv);

	std::cout << "Rename : " << std::boolalpha << argParser.GetFlag("rename") << std::endl;
	std::cout << "Convert: " << std::boolalpha << argParser.GetFlag("convert") << std::endl;
	std::cout << "Resize : " << std::boolalpha << argParser.GetFlag("resize") << std::endl;
	std::cout << "Scale  : " << std::boolalpha << argParser.GetFlag("scale") << std::endl;


	return 0;
}