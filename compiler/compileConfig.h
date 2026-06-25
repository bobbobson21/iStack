#pragma once

#include <iostream>
#include <string>

#include "compileParsering.h"

#include "istack/istack.h"

#define COMPILE_MODE__FILE_UNCOMPILED 1 //compiles sourcew code files //istf
#define COMPILE_MODE__COMMAND_LINE 0 //runs command line code //istcmd
#define COMPILE_MODE__FILE_COMPILE 0 //compiles a file for faster exacution //istfc
#define COMPILE_MODE__FILE_LOAD 0 //runs a compiled file //istfe

namespace compiler
{
#if COMPILE_MODE__FILE_UNCOMPILED
	bool CompileFunc(std::string filePath, ist::IstackStackFrame* codeFrame, ist::IstackStackFrame* dumpFrame, ist::IstackLexParser* parser, ist::IstackModuleExacuteor* exec) //file uncompiled
	{
		std::ifstream fileReader = std::ifstream();
		fileReader.open(filePath, std::ios::binary);
		unsigned int currentLineInParsing = 0;

		while (fileReader.is_open() == true && fileReader.good() == true && fileReader.eof() == false)
		{
			std::string parserLine = "";
			std::getline(fileReader, parserLine);

			(*parser) << parserLine.c_str();

			if (parser->ErrorInputBufferOverflowed() == true)
			{
				std::cout << "error: parser: parsing buffer of size (1024) overflowed on line (starting from line 0): " << currentLineInParsing << std::endl;

				fileReader.close();
				return false;
			}

			if (parser->ErrorIsParsingUnsucessful() == true)
			{
				std::cout << "error: parser: parsing interpretation failure occoured on line (starting from line 0): " << currentLineInParsing << std::endl;

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
			std::getline(std::cin, data);

			(*parser) << data.c_str();

			if (parser->ErrorInputBufferOverflowed() == true)
			{
				std::cout << "error: parser: parsing buffer of size (1024) overflowed on line (starting from line 0): " << currentLineInParsing << std::endl;
				return false;
			}

			if (parser->ErrorIsParsingUnsucessful() == true)
			{
				std::cout << "error: parser: parsing interpretation failure occoured on line (starting from line 0): " << currentLineInParsing << std::endl;
				return false;
			}

			if (data == "run" || data == "RUN" || data == "Run")
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

		if (fileReader.is_open() == false || fileReader.good() == false)
		{
			std::cout << "error: parser: could not read from input file" << std::endl;

			fileReader.close();
			return false;
		}

		fileWiter.open(filePath + "o", std::ios::out | std::ios::in | std::ios::trunc);

		if (fileWiter.is_open() == false || fileWiter.good() == false)
		{
			std::cout << "error: parser: could not write to output file" << std::endl;

			fileReader.close();
			fileWiter.close();
			return false;
		}

		while (fileReader.is_open() == true && fileReader.good() == true && fileReader.eof() == false)
		{
			std::string parserLine = "";
			std::getline(fileReader, parserLine);

			for (size_t i = 0; i < parserLine.length(); i++)
			{
				(*parser) << parserLine[i];

				if (parser->ErrorInputBufferOverflowed() == true)
				{
					std::cout << "error: parsing buffer of size (1024) overflowed" << std::endl;

					fileReader.close();
					fileWiter.close();
					return false;
				}

				if (parser->ErrorIsParsingUnsucessful() == true)
				{
					std::cout << "error: parsing interpretation failure occoured" << std::endl;

					fileReader.close();
					fileWiter.close();
					return false;
				}

				if (codeFrame->UnitLength() > 0)
				{
					fileWiter << codeFrame->UnitTop().m_modualTypeCode << ",(" << n_lastAguments << ");";
					codeFrame->UnitPop();
				}
			}
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
			blockInProcessing = blockInProcessing + fileContents[i];

			if (fileContents[i] == ';')
			{
				size_t separator = blockInProcessing.find(",");
				ist::IstackUnit newUnit = ist::IstackUnit();

				newUnit.m_modualTypeCode = std::stoi(blockInProcessing.substr(0, separator));

				DataParse((char*)blockInProcessing.c_str(), blockInProcessing.length(), &newUnit);

				codeFrame->UnitPush(newUnit);
				blockInProcessing = "";
			}
		}

		return true;
	}
#endif // COMPILE_MODE__FILE_COMPILE
}
