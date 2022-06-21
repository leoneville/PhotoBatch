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
		static constexpr const char* Help = "help";
	}

	namespace Options 
	{
		static constexpr const char* Folder = "folder";
		static constexpr const char* Filter = "filter";
		static constexpr const char* Width = "width";
		static constexpr const char* Height = "height";
		static constexpr const char* Amount = "amount";
		static constexpr const char* Prefix = "prefix";
		static constexpr const char* StartNumber = "startnumber";
		static constexpr const char* From = "from";
		static constexpr const char* To = "to";
	}
}

const std::string& GetInvalidChars()
{
	static const auto invalidCharacters = std::string{ "\\/*?\"<>|:" };
	return invalidCharacters;
}

bool HasInvalidChars(const std::string& str)
{
	const auto bHasInvalidChars = str.find_first_of(GetInvalidChars()) != std::string::npos;
	return bHasInvalidChars;
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
	if (numActiveModes == 0)
	{
		throw std::invalid_argument("Nenhum modo está ativo!");
	}

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

	if (!filter.empty() && HasInvalidChars(filter))
	{
		throw std::invalid_argument("O filtro não pode conter nenhum dos seguintes caracteres: " + GetInvalidChars());
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

	// Validar o modo Rename
	if (bRenameMode)
	{
		auto startNumber = -1;

		try
		{
			startNumber = argParser.GetOptionAs<int>(Args::Options::StartNumber);
		}
		catch (const std::invalid_argument&)
		{
			throw std::invalid_argument("O valor informado para StartNumber não é um número válido");
		}

		auto prefix = argParser.GetOptionAs<const std::string&>(Args::Options::Prefix);

		if (startNumber < 0)
		{
			throw std::invalid_argument("StartNumber deve ser maior ou igual a zero");
		}

		if (prefix.empty() || HasInvalidChars(prefix))
		{
			throw std::invalid_argument("Prefix não pode estar em branco e não pode conter os seguintes caracteres: " + GetInvalidChars());
		}
	}

	// Validar o modo Convert

	if (bConvertMode)
	{
		const auto from = argParser.GetOptionAs<const std::string&>(Args::Options::From);
		const auto to = argParser.GetOptionAs<const std::string&>(Args::Options::To);
		const auto convertOptions = std::array<std::string, 2>{ "jpg", "png" };

		const auto bIsFromValid = find(std::begin(convertOptions), std::end(convertOptions), from) != std::end(convertOptions);
		const auto bIsToValid = find(std::begin(convertOptions), std::end(convertOptions), to) != std::end(convertOptions);

		if (from.empty() || to.empty())
		{
			throw std::invalid_argument("From e To não podem estar em branco");
		}

		if (!bIsFromValid || !bIsToValid)
		{
			throw std::invalid_argument("From e To devem ser jpg ou png");
		}

		if (from == to)
		{
			throw std::invalid_argument("From e To deve ser diferentes");
		}
	}
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "pt_BR");
	setlocale(LC_NUMERIC, "en_US");

	auto argParser = ArgumentParser{};

	// Registra as flags do PhotoBatch
	argParser.RegisterFlag(Args::Flags::Rename);
	argParser.RegisterFlag(Args::Flags::Convert);
	argParser.RegisterFlag(Args::Flags::Resize);
	argParser.RegisterFlag(Args::Flags::Scale);
	argParser.RegisterFlag(Args::Flags::Help);

	// Registra as options do PhotoBatch
	argParser.RegisterOption(Args::Options::Folder);
	argParser.RegisterOption(Args::Options::Filter);
	argParser.RegisterOption(Args::Options::Width);
	argParser.RegisterOption(Args::Options::Height);
	argParser.RegisterOption(Args::Options::Amount);
	argParser.RegisterOption(Args::Options::Prefix);
	argParser.RegisterOption(Args::Options::StartNumber);
	argParser.RegisterOption(Args::Options::From);
	argParser.RegisterOption(Args::Options::To);

	argParser.SetHelpMessage(R"(USO: PhotoBatch --[Rename|Convert|Resize|Scale] [Opções]

    O PhotoBatch possui 4 modos de operação. Somente um modo pode estar ativo.
    Para ativar um modo escolha uma das seguintes flags:

    --Rename  : Ativa o modo para renomear arquivos
    --Convert : Ativa o modo para converter arquivos
    --Resize  : Ativa o modo para redimensionar arquivos
    --Scale   : Ativa o modo para escalar arquivos

As seguintes opções são comuns a todos os modos:
    --Folder  : Especifica a pasta onde o PhotoBatch irá atuar
    --Filter  : Especifica o filtro usado para selecionar arquivos

Opções do modo Rename:

    No modo Rename, cada arquivo selecionado será renomeado para o formato
    <Prefix>_<N>.<ext>, onde <Prefix> e <N> são especificados através de opções.
    <ext> é a extensão do arquivo que permanece inalterada.

    --Prefix=<Prefix> : Prefixo usado ao renomear os arquivos
    --StartNumber=<N> : Número inicial a ser adicionado em cada arquivo que for renomeado

Opções do modo Convert:

    No modo Convert, cada arquivo selecionado será convertido do formato <from> para
    o formato <to>. <from> e <to> não podem ser iguais. O nome do arquivo permanece
    inalterado.

    --From=<jpg|png> : Extensão de origem para conversão
    --To=<jpg|png>   : Extensão de destino para conversão

Opções do modo Resize:

    No modo Resize, cada arquivo selecionado será redimensionado para as dimensões
    especificadas nas seguintes opções. Note que N >= 1.

    --Width=<N>  : Novo comprimento da imagem
    --Height=<N> : Nova altura da imagem

Opções do modo Scale:

    No modo Scale, cada arquivo selecionado será escalado uniformemente pelo
    fator especificado pelas seguintes opções. Note que N > 0 e será interpretado
    como um número em ponto flutuante.

    --Amount=<N> : Fator de escala a ser aplicado em cada imagem selecionada.

Exemplos de uso:

    Renomear todos os arquivos da pasta "C:\Viagem" com a extensão ".png" para Viagem_N.png, onde N começa do 0

	    PhotoBatch --Rename --Folder="C:\Viagem" --Filter=".png" --StartNumber=0

    Redimensionar todos os arquivos na pasta "C:\Viagem" com a extensão ".jpg" para o tamanho 500x500

        PhotoBatch --Resize --Folder="C:\Viagem" --Filter=".jpg" --Width=500 --Height=500

    Converter todos os arquivos da pasta "C:\Viagem" de "png" para "jpg"

        PhotoBatch --Convert --Folder="C:\Viagem" --From=png --To=jpg

    Reduzir o pela metade o tamanho de todos os arquivos "png" da pasta "C:\Viagem"

        PhotoBatch --Scale --Folder="C:\Viagem" --Filter=".png" --Amount=0.5)");


	argParser.Parse(argc, argv);

	if (argParser.GetFlag(Args::Flags::Help))
	{
		std::cout << argParser.GetHelpMessage() << '\n';
	}
	else
	{
		try
		{
			ValidateArguments(argParser);
		}
		catch (const std::exception& exception)
		{
			std::cerr << "Erro: " << exception.what() << '\n';
			std::cerr << "Para mais informações, rode o PhotoBatch com a flag --help" << '\n';
		}
	}
	
	return 0;
}