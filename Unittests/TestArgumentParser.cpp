#include <gtest/gtest.h>
#include "ArgumentParser.hpp"

TEST(TestArgumentParser, RegisterFlag)
{
	// Cria um objeto ArgumentParser
	ArgumentParser argParser;

	// Verifica o estado antes da operação
	EXPECT_FALSE(argParser.IsFlagRegistered("MyFlag"));

	// Registrar a flag
	// Chamar a função sendo tratada
	argParser.RegisterFlag("MyFlag");

	// Verificar o estado depois da operação
	EXPECT_TRUE(argParser.IsFlagRegistered("MyFlag"));
}

TEST(TestArgumentParser, RegisterFlag_Whitespace)
{
	ArgumentParser argParser;

	argParser.RegisterFlag("My Flag");

	EXPECT_FALSE(argParser.IsFlagRegistered("My Flag"));
}

TEST(TestArgumentParser, RegisterOption)
{
	ArgumentParser argParser;
	
	argParser.RegisterOption("MyOption");

	EXPECT_TRUE(argParser.IsOptionRegistered("MyOption"));
}

TEST(TestArgumentParser, RegisterOption_Whitespace)
{
	ArgumentParser argParser;
	
	argParser.RegisterOption("My Option");

	EXPECT_FALSE(argParser.IsOptionRegistered("My Option"));
}