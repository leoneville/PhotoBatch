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
	
	// Obtém o valor de uma flag obtida durante o parse
	bool GetFlag(const std::string& flag) const;

	// Faz o parse da lista de argumentos em argv
	void Parse(int argc, char* argv[]);

private:
	std::map<std::string, bool> m_Flags;
};