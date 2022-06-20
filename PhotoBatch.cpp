#include <array>
#include <filesystem>
#include <iomanip>
#include <iostream>
#include <exception>

#include "ArgumentParser.hpp"


namespace Args 
{
	namespace Flags 
	{
		static constexpr const char* Rename = "rename";
		static constexpr const char* Convert = "convert";
		static constexpr const char* Resize = "resize";
		static constexpr const char* Scale = "scale";
	}

	namespace Options 
	{
		static constexpr const char* Folder = "folder";
		static constexpr const char* Filter = "filter";
		static constexpr const char* Width = "width";
		static constexpr const char* Height = "height";
		static constexpr const char* Amount = "amount";
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

	// Validar a pasta passada como a opção Folder
	const auto folder = argParser.GetOptionAs<const std::string&>(Args::Options::Folder);

	if (folder.empty())
	{
		throw std::invalid_argument("A pasta não pode estar em branco");
	}

	if (!std::filesystem::exists(folder))
	{
		throw std::invalid_argument("A pasta informada não existe!");
	}

	// Validar se o filtro é uma string válida
	const auto filter = argParser.GetOptionAs<const std::string&>(Args::Options::Filter);

	if (!filter.empty())
	{
		const auto invalidCharacters = std::string{ "\\/*?\"<>|:" };
		if (filter.find_first_of(invalidCharacters) != std::string::npos)
		{
			throw std::invalid_argument("O filtro não pode conter nenhum dos seguintes caracteres: " + invalidCharacters);
		}
	}

	// Validar o modo resize
	if (bResizeMode)
	{
		auto width = 0, height = 0;

		try
		{
			width = argParser.GetOptionAs<int>(Args::Options::Width);
			height = argParser.GetOptionAs<int>(Args::Options::Height);
		}
		catch (const std::invalid_argument&)
		{
			throw std::invalid_argument("O valor informado para Width ou Height não são números válidos.");
		}

		// No modo resize, o comprimento e a altura devem ser maiores que 0
		if (width <= 0 || height <= 0)
		{
			throw std::invalid_argument("Width e Height devem ser maiores que zero");
		}

		if (filter.empty())
		{
			throw std::invalid_argument("Filter não pode estar em branco no modo Resize");
		}
	}

	// Validar o modo Scale
	if (bScaleMode)
	{
		auto amount = 0.0f;

		try
		{
			amount = argParser.GetOptionAs<float>(Args::Options::Amount);
		} 
		catch (const std::invalid_argument&)
		{
			throw std::invalid_argument("O valor informado para Amount não é um número válido");
		}


		

		// No modo escala o amount deve ser maior do que zero
		if (amount <= 0.0f)
		{
			throw std::invalid_argument("Amount deve ser maior do que zero");
		}

		if (filter.empty())
		{
			throw std::invalid_argument("Filter não pode estar em branco no modo Scale");
		}
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
	argParser.RegisterOption(Args::Options::Folder);
	argParser.RegisterOption(Args::Options::Filter);
	argParser.RegisterOption(Args::Options::Width);
	argParser.RegisterOption(Args::Options::Height);
	argParser.RegisterOption(Args::Options::Amount);

	argParser.Parse(argc, argv);

	try
	{
		ValidateArguments(argParser);
	}
	catch (const std::exception& exception)
	{
		std::cerr << exception.what() << '\n';
	}
	
	return 0;
}