#pragma once

#include <iostream>
#include <string>

#include "generics.h"

namespace ist
{
	namespace modules
	{
		namespace raw
		{
			enum moduleIoErrorCodes : unsigned int
			{
				StackEmptyPopPrintIo = 401,
				DataIsNullPopPrintIo = 402,
			};

			bool ValidateSelf_SelfPrint(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				std::cout << *((std::string*)(*data));
				return false;
			}

			bool ValidateSelf_SelfPrintNewLine(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				std::cout << std::endl;
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

			bool ValidateSelf_SelfInput(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
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
			selfPrint.FreeData = raw::FreeData_Single;
			//selfPrint.CopyData = raw::CopyData_String; not needed as data will beoverride before its old ptr can be reached or at least it should be

			module->ModuleAdd(selfPrint);
			if (parser != nullptr) { parser->AddWord("SelfPrint"); }


			ist::IstackModuleType selfPrintNewLine = ist::IstackModuleType();
			selfPrintNewLine.ValidateSelf = raw::ValidateSelf_SelfPrintNewLine;
			selfPrintNewLine.FreeData = raw::FreeData_Single;
			//selfPrint.CopyData = raw::CopyData_String; not needed as data will beoverride before its old ptr can be reached or at least it should be

			module->ModuleAdd(selfPrintNewLine);
			if (parser != nullptr) { parser->AddWord("SelfPrintNewLine"); }
			

			ist::IstackModuleType popPrint = ist::IstackModuleType();
			popPrint.ValidateStack = raw::ValidateStack_PopPrint;
			popPrint.ValidateSelf = raw::ValidateSelf_Fail;
			popPrint.FreeData = raw::FreeData_Single;

			module->ModuleAdd(popPrint);
			if (parser != nullptr) { parser->AddWord("PopPrint"); }

			ist::IstackModuleType selfInput = ist::IstackModuleType();
			selfInput.ValidateSelf = raw::ValidateSelf_SelfInput;
			selfInput.FreeData = raw::FreeData_Single;

			module->ModuleAdd(selfInput);
			if (parser != nullptr) { parser->AddWord("SelfInput"); }
		}
	}
}