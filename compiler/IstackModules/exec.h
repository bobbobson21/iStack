#pragma once

#include <iostream>
#include <string>

#include "generics.h"

//add a execdump ooption and a end module

namespace ist
{
	namespace modules
	{
		enum moduleExecErrorCodes : unsigned int
		{
			CantAccessFrameInExecPopScope = 301,
			CantAccessFrameInExecScope = 302,

			StackEmptyPullDataScope = 303,
			DataIsNullPullDataScope = 304,
			PullIsNullPullDataScope = 305,
			PullIsBeyondStackLengthScope = 306,
		};

		namespace raw
		{
			unsigned int n_switchExecIndex = 0;


			bool ValidateStack_ScopeExecReturn(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if ((*dumpFrame->PipeGetCleared()) == nullptr) { exec->ErrorSetCode(CantAccessFrameInExecScope); return false; }

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
				if ((*dumpFrame->PipeGetCleared()) == nullptr) { exec->ErrorSetCode(CantAccessFrameInExecScope); return false; }
				if ((*(int*)(*data)) != n_switchExecIndex)
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
				if (dumpFrame->UnitLength() < 1) { exec->ErrorSetCode(StackEmptyPullDataScope); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(DataIsNullPullDataScope); return false; }

				int switchIndex = (*(int*)(dumpFrame->UnitTop().m_data)); //get amount
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();

				n_switchExecIndex = switchIndex;
			}
		}

		void LoadScopeModules(IstackModuleExacuteor* module, IstackLexParser* parser)
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
			scopeExecSwitchReturn.ValidateStack = raw::ValidateStack_ScopeSelfSwitchExecReturn;
			scopeExecSwitchReturn.ValidateSelf = raw::ValidateSelf_Fail;
			scopeExecSwitchReturn.FreeData = raw::FreeData_Single;
			scopeExecSwitchReturn.CopyData = raw::CopyData_FourChar;

			module->ModuleAddType(scopeExecSwitchReturn);
			if (parser != nullptr) { parser->WordsAdd("SelfExecSwitchReturn"); }

		}
	}
}
