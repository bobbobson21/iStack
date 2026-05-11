#pragma once

#include <iostream>
#include <string>
#include <memory>

#include "generics.h"

namespace ist
{
	namespace modules
	{
		void LoadVarModules(IstackModuleExacuteor* module, IstackLexParser* parser)
		{
			ist::IstackModuleType byte = ist::IstackModuleType();
			byte.FreeData = raw::FreeData_Single;
			byte.CopyData = raw::CopyData_Char;

			module->ModuleAddType(byte);
			if (parser != nullptr) { parser->WordsAdd("Byte"); }


			ist::IstackModuleType fourByte = ist::IstackModuleType();
			fourByte.FreeData = raw::FreeData_Single;
			fourByte.CopyData = raw::CopyData_FourChar;

			module->ModuleAddType(fourByte);
			if (parser != nullptr) { parser->WordsAdd("FourByte"); }


			ist::IstackModuleType string = ist::IstackModuleType();
			string.FreeData = raw::FreeData_String;
			string.CopyData = raw::CopyData_String;

			module->ModuleAddType(string);
			if (parser != nullptr) { parser->WordsAdd("String"); }
		}
	}
}