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