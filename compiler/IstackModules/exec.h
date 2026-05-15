#pragma once

#include <iostream>
#include <string>

#include <map>
#include <thread>

#include "generics.h"


namespace ist
{
	namespace modules
	{
		enum moduleExecErrorCodes : unsigned int
		{
			CantAccessFrameInExec = 300,
			CantObtainSwitchIndexExec = 301,

			StackIsEmptyExec = 302,
			DataIsNullExec = 303,
		};

		namespace raw
		{
			static std::map<std::thread::id, unsigned int> n_switchExecIndex = std::map<std::thread::id, unsigned int>();

			bool ValidateStack_ScopeExecReturn(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if ((*dumpFrame->PipeGetCleared()) == nullptr) { exec->ErrorSetCode(CantAccessFrameInExec); return false; }

				IstackStackFrame codeFrameBeta = IstackStackFrame();
				IstackStackFrame dumpFrameBeta = IstackStackFrame();

				//(*dumpFrame->PipeGetCleared())->CopyIStackTo(&codeFrameBeta);
				exec->CopyIstackFrameAndModuleDataFromAndTo((*dumpFrame->PipeGetCleared()), &codeFrameBeta);

				bool success = exec->ProcessExacuteFrame(&codeFrameBeta, &dumpFrameBeta);

				exec->FreeFrameRecursive(&dumpFrameBeta);
				exec->FreeFrameRecursive(&codeFrameBeta);

				dumpFrameBeta.UnitFlip();
				while (dumpFrameBeta.UnitLength() > 0)
				{
					dumpFrame->UnitPush(dumpFrameBeta.UnitTop());
					dumpFrameBeta.UnitPop();
				}
				dumpFrameBeta.UnitFree();

				return success;
			}

			bool ValidateStack_ScopeSelfSwitchExecReturn(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if ((*dumpFrame->PipeGetCleared()) == nullptr) { exec->ErrorSetCode(CantAccessFrameInExec); return false; }
				if (n_switchExecIndex.count(std::this_thread::get_id()) < 0) { exec->ErrorSetCode(CantObtainSwitchIndexExec); return false; }

				if ((*(int*)(*data)) != n_switchExecIndex[std::this_thread::get_id()])
				{
					return true;
				}

				IstackStackFrame codeFrameBeta = IstackStackFrame();
				IstackStackFrame dumpFrameBeta = IstackStackFrame();

				//(*dumpFrame->PipeGetCleared())->CopyIStackTo(&codeFrameBeta);
				exec->CopyIstackFrameAndModuleDataFromAndTo((*dumpFrame->PipeGetCleared()), &codeFrameBeta);

				bool success = exec->ProcessExacuteFrame(&codeFrameBeta, &dumpFrameBeta);

				exec->FreeFrameRecursive((*dumpFrameBeta.PipeGetCleared()));
				exec->FreeFrameRecursive((*dumpFrameBeta.PipeGet()));
				exec->FreeFrameRecursive(&codeFrameBeta);

				dumpFrameBeta.UnitFlip();
				while (dumpFrameBeta.UnitLength() > 0)
				{
					dumpFrame->UnitPush(dumpFrameBeta.UnitTop());
					dumpFrameBeta.UnitPop();
				}
				dumpFrameBeta.UnitFree();

				return success;
			}

			bool ValidateStack_ScopeSetSwitchIndex(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 1) { exec->ErrorSetCode(StackIsEmptyExec); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(DataIsNullExec); return false; }

				int switchIndex = (*(int*)(dumpFrame->UnitTop().m_data)); //get amount
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();

				n_switchExecIndex[std::this_thread::get_id()] = switchIndex;
			}
		}

		void LoadExecModules(IstackModuleExacuteor* module, IstackLexParser* parser)
		{
			ist::IstackModuleType scopeExecReturn = ist::IstackModuleType();
			scopeExecReturn.ValidateStack = raw::ValidateStack_ScopeExecReturn;
			scopeExecReturn.ValidateSelf = raw::ValidateSelf_Fail;

			module->ModuleAddType(scopeExecReturn);
			if (parser != nullptr) { parser->WordsAdd("ExecReturn"); }


			ist::IstackModuleType scopeExecSwitchReturn = ist::IstackModuleType();
			scopeExecSwitchReturn.ValidateStack = raw::ValidateStack_ScopeSelfSwitchExecReturn;
			scopeExecSwitchReturn.ValidateSelf = raw::ValidateSelf_Fail;
			scopeExecSwitchReturn.FreeData = raw::FreeData_Single;
			scopeExecSwitchReturn.CopyData = raw::CopyData_FourChar;

			module->ModuleAddType(scopeExecSwitchReturn);
			if (parser != nullptr) { parser->WordsAdd("SelfExecSwitchReturn"); }


			ist::IstackModuleType scopeExecSwitchReturn = ist::IstackModuleType();
			scopeExecSwitchReturn.ValidateStack = raw::ValidateStack_ScopeSetSwitchIndex;
			scopeExecSwitchReturn.ValidateSelf = raw::ValidateSelf_Fail;
			scopeExecSwitchReturn.FreeData = raw::FreeData_Single;
			scopeExecSwitchReturn.CopyData = raw::CopyData_FourChar;

			module->ModuleAddType(scopeExecSwitchReturn);
			if (parser != nullptr) { parser->WordsAdd("SelfSetSwitchIndex"); }
		}
	}
}
