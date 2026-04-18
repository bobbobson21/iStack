// Compiler.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>

#include "IstackModules/io.h"
#include "IstackModules/scope.h"
#include "IstackModules/var.h"
#include "IstackModules/logic.h"
#include "IstackModules/math.h"
#include "IstackModules/conversion.h"
#include "IstackModules/loops.h"

#include "istack/istack.h"

#define COMPILE_MODE__FILE_UNCOMPILED 1 //compiles sourcew code files //istf
#define COMPILE_MODE__COMMAND_LINE 0 //runs command line code //istcmd
#define COMPILE_MODE__FILE_COMPILE 0 //compiles a file for faster exacution //istfc
#define COMPILE_MODE__FILE_LOAD 0 //runs a compiled file //istfe

//argument parsing has to be handled in compiler

namespace compiler
{
	std::string n_lastAguments = "";

	bool DataParse(char* string, unsigned int stringLength, ist::IstackUnit* unit)
	{
		std::string stringName = "";
		std::string stringArg = "";
		int parsingMode = 0; //parse mode 0 = parseing module name, parse mode 1 = parsing argument, parse mode 2 = null

		for (size_t i = 0; i < stringLength; i++)
		{
			if (string[i] == ')') { parsingMode = 2; }

			if (parsingMode == 1)
			{
				stringArg = stringArg + string[i];
			}

			if (string[i] == '(') { parsingMode = 1; }

			if (parsingMode == 0 && string[i] != ';')
			{
				stringName = stringName + string[i];
			}
		}

		n_lastAguments = stringArg;

		if (parsingMode == 1)
		{
			return false;
		}

		if ((stringArg[0] == '"' && stringArg[stringArg.length() - 1] == '"') || (stringArg[0] == '\'' && stringArg[stringArg.length() - 1] == '\''))
		{
			if (stringName == "Byte" || stringName == "FourByte")
			{
				return false;
			}

			unit->m_data = new std::string();
			(*((std::string*)unit->m_data)) = stringArg.substr(1, stringArg.length() - 2);
			return true;
		}



		if (stringArg == "")
		{
			return true;
		}

		if (stringArg == "true")
		{
			if (stringName == "FourByte" || stringName == "String")
			{
				return false;
			}

			unit->m_data = new bool;
			(*((bool*)unit->m_data)) = true;
			return true;
		}

		if (stringArg == "false")
		{
			if (stringName == "FourByte" || stringName == "String")
			{
				return false;
			}

			unit->m_data = new bool;
			(*((bool*)unit->m_data)) = false;
			return true;
		}

		try
		{
			int data = std::stoi(stringArg);

			unit->m_data = new int();
			(*((int*)unit->m_data)) = data;

			if (stringName == "Byte" || stringName == "String")
			{
				return false;
			}
		}
		catch (...)
		{
			try
			{
				float data = std::stof(stringArg);

				unit->m_data = new float();
				(*((float*)unit->m_data)) = data;

				if (stringName == "Byte" || stringName == "String")
				{
					return false;
				}
			}
			catch (...)
			{
				return false;
			}
		}

		return true;
	}

#if COMPILE_MODE__FILE_UNCOMPILED
	bool CompileFunc(std::string filePath, ist::IstackStackFrame* codeFrame, ist::IstackStackFrame* dumpFrame, ist::IstackLexParser* parser, ist::IstackModuleExacuteor* exec) //file uncompiled
	{
		std::ifstream fileReader = std::ifstream();
		fileReader.open(filePath, std::ios::binary);
		unsigned int currentLineInParsing = 0;

		while (fileReader.good() == true && fileReader.good() == true && fileReader.eof() == false)
		{
			std::string parserLine = "";

			std::getline(fileReader, parserLine);
			(*parser) << parserLine.c_str();

			if (parser->InputBufferOverflowed() == true)
			{
				std::cout << "error: parsing buffer of size (1024) overflowed on line (starting from line 0): " << currentLineInParsing << std::endl;

				fileReader.close();
				return false;
			}

			if (parser->IsParsingSucessful() == false)
			{
				std::cout << "error: parsing interpretation failure occoured on line (starting from line 0): " << currentLineInParsing << std::endl;

				fileReader.close();
				return false;
			}

			currentLineInParsing++;
		}

		fileReader.close();
		return true;
	}
#endif // COMPILE_MODE__FILE_UNCOMPILED

#if COMPILE_MODE__COMMAND_LINE
	bool CompileFunc(std::string filePath, ist::IstackStackFrame* codeFrame, ist::IstackStackFrame* dumpFrame, ist::IstackLexParser* parser, ist::IstackModuleExacuteor* exec) ///comand line
	{
		unsigned int currentLineInParsing = 0;

		while (true)
		{
			std::string data = "";
			std::cin >> data;

			(*parser) << data.c_str();

			if (parser->InputBufferOverflowed() == true)
			{
				std::cout << "error: parsing buffer of size (1024) overflowed on line (starting from line 0): " << currentLineInParsing << std::endl;
				return false;
			}

			if (parser->IsParsingSucessful() == false)
			{
				std::cout << "error: parsing interpretation failure occoured on line (starting from line 0): " << currentLineInParsing << std::endl;
				return false;
			}

			if (data == "RUN" || data == "run")
			{
				break;
			}

			currentLineInParsing = currentLineInParsing + 1;
		}

		return true;
	}
#endif // COMPILE_MODE__COMMAND_LINE

#if COMPILE_MODE__FILE_COMPILE
	bool CompileFunc(std::string filePath, ist::IstackStackFrame* codeFrame, ist::IstackStackFrame* dumpFrame, ist::IstackLexParser* parser, ist::IstackModuleExacuteor* exec) ///comand line
	{
		std::ifstream fileReader = std::ifstream();
		std::fstream fileWiter = std::fstream();

		fileReader.open(filePath, std::ios::binary);
		fileWiter.open(filePath + "o", std::ios::out | std::ios::in | std::ios::trunc);

		if (fileWiter.is_open() == false || fileWiter.good() == false)
		{
			std::cout << "error: could not write to output file" << std::endl;

			fileReader.close();
			fileWiter.close();
			return false;
		}

		unsigned int currentLineInParsing = 0;

		while (fileReader.good() == true && fileReader.good() == true && fileReader.eof() == false)
		{
			char charBuffer = ' ';

			fileReader.read(&charBuffer, 1);
			(*parser) << charBuffer;

			if (parser->InputBufferOverflowed() == true)
			{
				std::cout << "error: parsing buffer of size (1024) overflowed on line (starting from line 0): " << currentLineInParsing << std::endl;

				fileReader.close();
				fileWiter.close();
				return false;
			}

			if (parser->IsParsingSucessful() == false)
			{
				std::cout << "error: parsing interpretation failure occoured on line (starting from line 0): " << currentLineInParsing << std::endl;

				fileReader.close();
				fileWiter.close();
				return false;
			}

			if (codeFrame->Length() > 0)
			{
				fileWiter << codeFrame->Top().m_modualTypeCode << ",(" << n_lastAguments << ");";
				codeFrame->Pop();
			}

			currentLineInParsing++;
		}

		fileReader.close();
		fileWiter.close();
		return false;
	}
#endif // COMPILE_MODE__FILE_COMPILE

#if COMPILE_MODE__FILE_LOAD
	bool CompileFunc(std::string filePath, ist::IstackStackFrame* codeFrame, ist::IstackStackFrame* dumpFrame, ist::IstackLexParser* parser, ist::IstackModuleExacuteor* exec) ///comand line
	{
		std::ifstream fileReader = std::ifstream();
		std::string fileContents = "";

		fileReader.open(filePath, std::ios::binary);

		while (fileReader.good() == true && fileReader.good() == true && fileReader.eof() == false)
		{
			std::string tempFileData = "";
			std::getline(fileReader, tempFileData);
			fileContents = fileContents + tempFileData;
		}

		std::string blockInProcessing = "";
		for (size_t i = 0; i < fileContents.length(); i++)
		{
			blockInProcessing = blockInProcessing +fileContents[i];

			if (fileContents[i] == ';')
			{
				size_t separator = blockInProcessing.find(",");
				ist::IstackUnit newUnit = ist::IstackUnit();

				newUnit.m_modualTypeCode = std::stoi(blockInProcessing.substr(0, separator));
				
				DataParse((char*)blockInProcessing.c_str(), blockInProcessing.length(), &newUnit);
				
				codeFrame->Push(newUnit);
				blockInProcessing = "";
			}
		}

		return true;
	}
#endif // COMPILE_MODE__FILE_COMPILE
}

int main(int argc, char* argv[])
{
	std::string filePath = "";

	for (int i = 1; i < argc; i++)
	{
		for (unsigned int o = 0; argv[i][o] != '\0'; o++)
		{
			filePath = filePath + argv[i][o];
		}
	}

	//set up contents
	ist::IstackStackFrame codeScope = ist::IstackStackFrame();
	ist::IstackStackFrame dump = ist::IstackStackFrame();

	ist::IstackLexParser parser = ist::IstackLexParser();
	parser.SetFrame(&codeScope);
	parser.SetDataParse(compiler::DataParse);

	ist::IstackModuleExacuteor exec = ist::IstackModuleExacuteor();
	
	//load modules
	ist::modules::LoadVarModules(&exec, &parser);
	ist::modules::LoadConversionModules(&exec, &parser, 0);
	ist::modules::LoadLoopsModules(&exec, &parser, 0);
	ist::modules::LoadScopeModules(&exec, &parser);
	ist::modules::LoadIoModules(&exec, &parser);
	ist::modules::LoadLogicModules(&exec, &parser);
	ist::modules::LoadMathModules(&exec, &parser);

	//read in contents of istack file
	bool canExacuteCodeFrame = compiler::CompileFunc(filePath, &codeScope, &dump, &parser, &exec);

	if (canExacuteCodeFrame == true)
	{
		//exacute istack code
		bool success = exec.ExacuteFrame(&codeScope, &dump);

		//error repoarting
		if (success == false)
		{
			std::cout << "error: stack exacition failed with error code: " << exec.GetErrorCode() << std::endl;
		}
	}

	//free data
	exec.FreeFrame(&codeScope);
	exec.FreeFrameRecursive(&dump);

	return 0;
}

