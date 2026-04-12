#pragma once

#include <iostream>
#include <string>
#include <memory>

#include "istack/istack.h"

#include "generics.h"

namespace ist
{
	namespace modules
	{
		namespace raw
		{
			void CopyData_String(void** copyFrom, void** copyTo)
			{
				delete (*copyTo);
				(*copyTo) = new std::string;

				for (size_t i = 0; i < (*(std::string*)(*copyFrom)).size(); i++)
				{
					(*(std::string*)(*copyTo)) += (*(std::string*)(*copyFrom))[i];
				}
			}
		}

		void LoadVarModules(IstackModuleExacuteor* module, IstackLexParser* parser)
		{
			ist::IstackModuleType byte = ist::IstackModuleType();
			byte.FreeData = raw::FreeData_Single;
			byte.CopyData = raw::CopyData_Char;

			module->AddModule(byte);
			if (parser != nullptr) { parser->AddWords("Byte"); }


			ist::IstackModuleType fourByte = ist::IstackModuleType();
			fourByte.FreeData = raw::FreeData_Single;
			fourByte.CopyData = raw::CopyData_FourChar;

			module->AddModule(fourByte);
			if (parser != nullptr) { parser->AddWords("FourByte"); }


			ist::IstackModuleType string = ist::IstackModuleType();
			string.FreeData = raw::FreeData_Single;
			string.CopyData = raw::CopyData_String;

			module->AddModule(string);
			if (parser != nullptr) { parser->AddWords("String"); }
		}
	}
}