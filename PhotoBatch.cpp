#include "ArgumentParser.hpp"

#include <array>
#include <iomanip>
#include <iostream>

namespace Args 
{
	namespace Flags 
	{
		static constexpr const char* Rename = "rename";
		static constexpr const char* Convert = "convert";
		static constexpr const char* Resize = "resize";
		static constexpr const char* Scale = "scale";
	}
}

void ValidateArguments(const ArgumentParser& argParser)
{
	// Ler as flags que o ArgumentParser identificou
	const auto bRenameMode = argParser.GetFlag(Args::Flags::Rename);
	const auto bConvertMode = argParser.GetFlag(Args::Flags::Convert);
	const auto bResizeMode = argParser.GetFlag(Args::Flags::Resize);
	const auto bScaleMode = argParser.GetFlag(Args::Flags::Scale);

	const auto modes = std::array<bool, 4>{bRenameMode, bConvertMode, bResizeMode, bScaleMode};
	const auto numActiveModes = std::count(std::begin(modes), std::end(modes), true);

	// Verificar se somente um modo do PhotoBatch está ativo com OU Exclusivo
	/*if (!(bRenameMode ^ bConvertMode ^ bResizeMode ^ bScaleMode))*/
	if (numActiveModes != 1)
	{
		// se houver mais de um modo ativo, lança uma exceção.
		throw std::invalid_argument("Somente um modo pode estar ativo!");
	}
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "pt_BR");
	setlocale(LC_NUMERIC, "en_US");

	auto argParser = ArgumentParser{};
	argParser.RegisterFlag(Args::Flags::Rename);
	argParser.RegisterFlag(Args::Flags::Convert);
	argParser.RegisterFlag(Args::Flags::Resize);
	argParser.RegisterFlag(Args::Flags::Scale);

	argParser.Parse(argc, argv);

	try
	{
		ValidateArguments(argParser);
		std::cout << "Não deu erro";
	}
	catch (const std::exception& exception)
	{
		std::cerr << exception.what() << '\n';
	}
	
	return 0;
}