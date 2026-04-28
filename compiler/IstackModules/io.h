#pragma once

#include <iostream>
#include <string>

#include "generics.h"

namespace ist
{
	namespace modules
	{
		enum moduleIoErrorCodes : unsigned int
		{
			StackEmptyPopPrintIo = 401,
			DataIsNullPopPrintIo = 402,
		};

		namespace raw
		{
			bool ValidateSelf_SelfPrint(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				std::cout << *((std::string*)(*data));
				return false;
			}

			bool ValidateSelf_PrintNewLine(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				std::cout << std::endl;
				return false;
			}

			bool ValidateSelf_PrintFlush(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				std::cout << std::flush;
				return false;
			}

			bool ValidateSelf_PrintE(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				std::cout << "\033";
				return false;
			}


			bool ValidateStack_PopPrint(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 1)
				{
					exec->ErrorSetCode(StackEmptyPopPrintIo);
					return false;
				}

				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(DataIsNullPopPrintIo); return false; }

				std::cout << (*(std::string*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();

				return true;
			}

			bool ValidateSelf_Input(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				std::string inputString = "";
				std::cin >> inputString;
				
				delete (*data);

				(*data) = new std::string;
				*((std::string*)(*data)) = inputString;

				return true;
			}
		}

		void LoadIoModules(IstackModuleExacuteor* module, IstackLexParser* parser)
		{
			ist::IstackModuleType selfPrint = ist::IstackModuleType();
			selfPrint.ValidateSelf = raw::ValidateSelf_SelfPrint;
			selfPrint.FreeData = raw::FreeData_String;
			selfPrint.CopyData = raw::CopyData_String;

			module->ModuleAddType(selfPrint);
			if (parser != nullptr) { parser->AddWord("SelfPrint"); }


			ist::IstackModuleType selfPrintNewLine = ist::IstackModuleType();
			selfPrintNewLine.ValidateSelf = raw::ValidateSelf_PrintNewLine;
			//selfPrint.CopyData = raw::CopyData_String; not needed as data will beoverride before its old ptr can be reached or at least it should be

			module->ModuleAddType(selfPrintNewLine);
			if (parser != nullptr) { parser->AddWord("PrintNewLine"); }


			ist::IstackModuleType selfPrintFlush = ist::IstackModuleType();
			selfPrintFlush.ValidateSelf = raw::ValidateSelf_PrintFlush;
			//selfPrint.CopyData = raw::CopyData_String; not needed as data will beoverride before its old ptr can be reached or at least it should be

			module->ModuleAddType(selfPrintFlush);
			if (parser != nullptr) { parser->AddWord("PrintFlush"); }


			ist::IstackModuleType selfPrintE = ist::IstackModuleType();
			selfPrintE.ValidateSelf = raw::ValidateSelf_PrintE;
			//selfPrint.CopyData = raw::CopyData_String; not needed as data will beoverride before its old ptr can be reached or at least it should be

			module->ModuleAddType(selfPrintE);
			if (parser != nullptr) { parser->AddWord("PrintE"); }
			

			ist::IstackModuleType popPrint = ist::IstackModuleType();
			popPrint.ValidateStack = raw::ValidateStack_PopPrint;
			popPrint.ValidateSelf = raw::ValidateSelf_Fail;
			//popPrint.FreeData = raw::FreeData_Single;

			module->ModuleAddType(popPrint);
			if (parser != nullptr) { parser->AddWord("PopPrint"); }

			ist::IstackModuleType selfInput = ist::IstackModuleType();
			selfInput.ValidateSelf = raw::ValidateSelf_Input;
			selfInput.FreeData = raw::FreeData_String;

			module->ModuleAddType(selfInput);
			if (parser != nullptr) { parser->AddWord("Input"); }
		}
	}
}