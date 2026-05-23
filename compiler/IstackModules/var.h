#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <thread>
#include <map>

#include "generics.h"

namespace ist
{
	namespace modules
	{
		enum moduleVarErrorCodes : unsigned int
		{
			StackLengthNotMetVar = 001,
			InvalidLocationVar = 002,
		};

		namespace raw
		{
			static std::map<std::thread::id, std::map<std::string, ist::IstackUnit>> n_varObjectMap = std::map<std::thread::id, std::map<std::string, ist::IstackUnit>>();

			bool ValidateStack_PushVar(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 2) { exec->ErrorSetCode(StackLengthNotMetVar); return false; }

				std::string adress = "";

				try
				{
					adress = (*(std::string*)(dumpFrame->UnitTop().m_data));
					exec->FreeUnit(dumpFrame->UnitTopPtr());
					dumpFrame->UnitPop();
				}
				catch (...)
				{
					exec->ErrorSetCode(InvalidLocationVar); return false;
				}

				ist::IstackUnit unit = dumpFrame->UnitTop();
				dumpFrame->UnitPop();

				if (n_varObjectMap.count(std::this_thread::get_id()) < 1) { n_varObjectMap[std::this_thread::get_id()] = std::map<std::string, ist::IstackUnit>(); }
				n_varObjectMap[std::this_thread::get_id()][adress];

			}

			bool ValidateStack_PopVar(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 1) { exec->ErrorSetCode(StackLengthNotMetVar); return false; }

				std::string adress = "";

				try
				{
					adress = (*(std::string*)(dumpFrame->UnitTop().m_data));
					exec->FreeUnit(dumpFrame->UnitTopPtr());
					dumpFrame->UnitPop();
				}
				catch (...)
				{
					exec->ErrorSetCode(InvalidLocationVar); return false;
				}

				while (true)
				{
					if (n_varObjectMap.count(std::this_thread::get_id()) > 0 && n_varObjectMap[std::this_thread::get_id()].count(adress) > 0)
					{
						dumpFrame->UnitPush(n_varObjectMap[std::this_thread::get_id()][adress]);
						n_varObjectMap[std::this_thread::get_id()].erase(adress);

						return true;
					}
				}

				return false;
			}

			bool ValidateStack_SelfPushVar(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 1) { exec->ErrorSetCode(StackLengthNotMetVar); return false; }

				std::string adress = (*((std::string*)(*data)));

				ist::IstackUnit unit = dumpFrame->UnitTop();
				dumpFrame->UnitPop();

				if (n_varObjectMap.count(std::this_thread::get_id()) < 1) { n_varObjectMap[std::this_thread::get_id()] = std::map<std::string, ist::IstackUnit>(); }
				n_varObjectMap[std::this_thread::get_id()][adress];

			}

			bool ValidateStack_SelfPopVar(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 1) { exec->ErrorSetCode(StackLengthNotMetVar); return false; }

				std::string adress = (*((std::string*)(*data)));

				while (true)
				{
					if (n_varObjectMap.count(std::this_thread::get_id()) > 0 && n_varObjectMap[std::this_thread::get_id()].count(adress) > 0)
					{
						dumpFrame->UnitPush(n_varObjectMap[std::this_thread::get_id()][adress]);
						n_varObjectMap[std::this_thread::get_id()].erase(adress);

						return true;
					}
				}

				return false;
			}
		}

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


			ist::IstackModuleType pushSelf = ist::IstackModuleType();
			pushSelf.ValidateStack = raw::ValidateStack_SelfPushVar;
			pushSelf.FreeData = raw::FreeData_String;
			pushSelf.CopyData = raw::CopyData_String;

			module->ModuleAddType(pushSelf);
			if (parser != nullptr) { parser->WordsAdd("SelfPushVar"); }


			ist::IstackModuleType popSelf = ist::IstackModuleType();
			popSelf.ValidateStack = raw::ValidateStack_SelfPopVar;
			popSelf.FreeData = raw::FreeData_String;
			popSelf.CopyData = raw::CopyData_String;

			module->ModuleAddType(popSelf);
			if (parser != nullptr) { parser->WordsAdd("SelfPopVar"); }


			ist::IstackModuleType push = ist::IstackModuleType();
			push.ValidateStack = raw::ValidateStack_PushVar;

			module->ModuleAddType(push);
			if (parser != nullptr) { parser->WordsAdd("PushVar"); }


			ist::IstackModuleType pop = ist::IstackModuleType();
			pop.ValidateStack = raw::ValidateStack_PopVar;
			pop.FreeData = raw::FreeData_String;
			pop.CopyData = raw::CopyData_String;

			module->ModuleAddType(pop);
			if (parser != nullptr) { parser->WordsAdd("PopVar"); }
		}
	}
}