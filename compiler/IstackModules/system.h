#pragma once

#include <string>

#include "generics.h"

namespace ist
{
	namespace modules
	{
		enum moduleSystemErrorCodes : unsigned int
		{
			StackEmptySystem = 701,
			DataIsNullSystem = 703,
		};

		namespace raw
		{
			bool ValidateStack_strSystem(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 1) { exec->ErrorSetCode(StackEmptySystem); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(DataIsNullSystem); return false; }

				std::string command = (*(std::string*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();

				return (system(command.c_str()) == 0);
			}

			bool ValidateStack_strSelfSystem(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				std::string command = (*(std::string*)(*data));

				return (system(command.c_str()) == 0);
			}
		}

		void LoadSystemModules(IstackModuleExacuteor* module, IstackLexParser* parser)
		{
			ist::IstackModuleType sys = ist::IstackModuleType();
			sys.ValidateStack = raw::ValidateStack_strSystem;
			sys.ValidateSelf = raw::Validate_Fail;
			//ItF.FreeData = raw::FreeData_Single; //not needed conversion has no data
			//notMod.FreeData = raw::CopyData_Char; //not needed due to validate stack exacuting before any data can be read

			module->ModuleAddType(sys);
			if (parser != nullptr) { parser->WordsAdd("strSystem"); }


			ist::IstackModuleType selfSys = ist::IstackModuleType();
			selfSys.ValidateStack = raw::ValidateStack_strSelfSystem;
			selfSys.ValidateSelf = raw::Validate_Fail;
			selfSys.FreeData = raw::FreeData_String;
			selfSys.CopyData = raw::CopyData_String; //not needed due to validate stack exacuting before any data can be read

			module->ModuleAddType(selfSys);
			if (parser != nullptr) { parser->WordsAdd("SelfSystem"); }
		}
	}
}