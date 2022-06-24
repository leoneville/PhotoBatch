#include <algorithm>

#include "ArgumentParser.hpp"
#include "Utils.hpp"


void ArgumentParser::RegisterFlag(const std::string& flag)
{
	// if the flag argument is not empty...
	// se o argumento flag não estiver vazio...
	if (!flag.empty())
	{
		// save the value in the flag key as false! Ex:. m_Flags["rename"] = false;
		// salva o valor da chave flag como false Ex:. m_Flags["rename"] = false;
		this->m_Flags[flag] = false;
	}
}

void ArgumentParser::RegisterOption(const std::string& option)
{
	if (!option.empty())
	{
		this->m_Options[option] = "";
	}
}

bool ArgumentParser::IsFlagRegistered(const std::string& flag) const
{
	if (!flag.empty())
	{
		return this->m_Flags.count(flag) == 1;
	}

	return false;
}

bool ArgumentParser::GetFlag(const std::string& flag) const
{
	// if the flag argument is not empty...
	// se o argumento flag não estiver vazio...
	if (!flag.empty())
	{
		// o iterator percorre o map buscando a chave flag...
		auto flagIt = this->m_Flags.find(flag);
		// se o iterator encontrou a chave flag no map...
		if (flagIt != std::end(m_Flags))
		{
			// retorne o valor salvo na chave!
			return flagIt->second;
		}
	}

	// se não achou a chave no map, retorne false!
	return false;
}

const std::string& ArgumentParser::GetOption(const std::string& option) const
{
	if (!option.empty())
	{
		auto optionIt = this->m_Options.find(option);

		if (optionIt != std::end(this->m_Options))
		{
			return optionIt->second;
		}
	}

	static std::string EmptyOption = "";
	return EmptyOption;
}

float ArgumentParser::GetOptionAsFloat(const std::string& option) const
{
	auto optionValue = GetOption(option);

	if (!optionValue.empty())
	{
		return std::stof(optionValue);
	}

	return -1;
}

int ArgumentParser::GetOptionAsInt(const std::string& option) const
{
	auto optionValue = GetOption(option);

	if (!optionValue.empty())
	{
		return std::stoi(optionValue);
	}

	return -1;
}

void ArgumentParser::SetHelpMessage(const std::string& helpMessage)
{
	this->m_HelpMessage = helpMessage;
}

const std::string& ArgumentParser::GetHelpMessage() const
{
	return this->m_HelpMessage;
}

void ArgumentParser::Parse(int argc, char* argv[])
{
	if (argc > 1)
	{
		for (auto i = 1; i < argc; ++i)
		{
			std::string arg = Utils::ToLower(argv[i]);

			if (arg.length() >= 3 && (arg[0] == '-' && arg[1] == '-'))
			{
				// argumentos tem que ter pelo menos 3 caracteres
				// os "--" iniciais e pelo menos um terceiro caracter

				// "--rename"
				// primeiro, vamos remover os "--" iniciais
				arg = arg.substr(2);

				// Depois do arg.substr: "rename"

				// verifica se o arg possui o caracter '='
				if (arg.find_first_of('=') != std::string::npos)
				{
					// é uma opção
					const auto equalSignPos = arg.find('=');
					if (equalSignPos != std::string::npos)
					{
						// Dividir a opção em chave e valor
						std::string optionName = arg.substr(0, equalSignPos);
						std::string optionValue = arg.substr(equalSignPos + 1);

						auto optionIt = this->m_Options.find(optionName);
						if (optionIt != std::end(this->m_Options))
						{
							// Achamos uma opção registrada
							optionIt->second = optionValue;
						}
					}
				}
				else
				{
					// é uma flag

					// o iterator percorre o map buscando a chave flag...
					auto flagIt = this->m_Flags.find(arg);
					// se o iterator encontrou a chave flag no map...
					if (flagIt != std::end(m_Flags))
					{
						// altere o valor da chave para true através do iterator
						flagIt->second = true;
					}

				}
			}
		}
	}
}