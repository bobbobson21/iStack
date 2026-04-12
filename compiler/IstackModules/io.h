#pragma once

#include <iostream>
#include <string>

#include "istack/istack.h"

#include "generics.h"

namespace ist
{
	namespace modules
	{
		namespace raw
		{
			bool ValidateSelf_SelfPrint(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				std::cout << "output: " << *((std::string*)(*data)) << std::endl;
				return false;
			}

			bool ValidateStack_PopPrint(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->Length() < 1)
				{
					return false;
				}

				std::cout << "output: " << (*(std::string*)(dumpFrame->Top().m_data)) << std::endl;
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();

				return true;
			}

			bool ValidateSelf_SelfInput(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				std::cout << "input: " << std::flush;
				
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

			module->AddModule(selfPrint);
			if (parser != nullptr) { parser->AddWords("SelfPrint"); }
			

			ist::IstackModuleType popPrint = ist::IstackModuleType();
			popPrint.ValidateStack = raw::ValidateStack_PopPrint;
			popPrint.ValidateSelf = raw::ValidateSelf_Fail;
			popPrint.FreeData = raw::FreeData_Single;

			module->AddModule(popPrint);
			if (parser != nullptr) { parser->AddWords("PopPrint"); }

			ist::IstackModuleType selfInput = ist::IstackModuleType();
			selfInput.ValidateSelf = raw::ValidateSelf_SelfInput;
			selfInput.FreeData = raw::FreeData_Single;

			module->AddModule(selfInput);
			if (parser != nullptr) { parser->AddWords("SelfInput"); }
		}
	}
}