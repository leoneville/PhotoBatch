#pragma once

#include <string>
#include <map>

/*
 * Classe usada para ler os argumentos da linha de comando
 * 
 * Ex:.
 *	auto argParser = ArgumentParser{};
 *  argParser.RegisterFlag("rename");
 *  argParser.Parse(argc, argv);
 *  argParser.GetFlag("rename")
*/

class ArgumentParser
{
public:
	// Registra uma flag usada durante o parse
	void RegisterFlag(const std::string& flag);

	// Registra uma option usada durante o parse
	void RegisterOption(const std::string& flag);
	
	// Obtém o valor de uma flag obtida durante o parse
	bool GetFlag(const std::string& flag) const;

	template<typename T>
	T GetOptionAs(const std::string& option) const;

	template<>
	const std::string& GetOptionAs(const std::string& option) const { return GetOption(option); }

	template<>
	float GetOptionAs(const std::string& option) const { return GetOptionAsFloat(option); }

	template<>
	int GetOptionAs(const std::string& option) const { return GetOptionAsInt(option); }

	// Faz o parse da lista de argumentos em argv
	void Parse(int argc, char* argv[]);

private:
	std::map<std::string, bool> m_Flags;
	std::map<std::string, std::string> m_Options;

	// Obtém o valor de uma option obtida durante o parse
	const std::string& GetOption(const std::string& option) const;

	// Obtém o valor de uma option convertida para float
	float GetOptionAsFloat(const std::string& option) const;

	// Obtém o valor de uma option convertida para int
	int GetOptionAsInt(const std::string& option) const;
};