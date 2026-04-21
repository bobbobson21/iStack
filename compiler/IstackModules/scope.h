#pragma once

#include <iostream>
#include <string>

#include "generics.h"

namespace ist
{
	namespace modules
	{
		enum moduleScopeErrorCodes : unsigned int
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
			bool ValidateSelf_ScopeStart(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if ((*dumpFrame->PipeGetCleared()) != nullptr)
				{
					exec->FreeFrameRecursive((*dumpFrame->PipeGetCleared()));
					(*dumpFrame->PipeGetCleared()) = nullptr;
				}

				dumpFrame->PipeCreate();
				dumpFrame->PipePushDepthContext();
				return false;
			}

			bool ValidateSelfPiped_ScopeStart(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				dumpFrame->PipePushDepthContext();
				return true;
			}


			bool ValidateSelfPiped_ScopeEndFliped(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				dumpFrame->PipePopDepthContext();

				if (dumpFrame->PipeTopDepthContext() == 0)
				{
					dumpFrame->PipeClear();
					(*dumpFrame->PipeGetCleared())->UnitFlip();
					return false;
				}

				return true;
			}


			bool ValidateStack_ScopeExecPop(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if ((*dumpFrame->PipeGetCleared()) == nullptr) { exec->ErrorSetCode(CantAccessFrameInExecPopScope); return false; }

				IstackStackFrame* dumpFrameBeta = new IstackStackFrame(); //the dump frame
				bool success = exec->ProcessExacuteFrame((*dumpFrame->PipeGetCleared()), dumpFrameBeta); //exacutes the dump frame
				
				exec->FreeFrameRecursive((*dumpFrame->PipeGetCleared())); //deletes the code frame
				(*dumpFrame->PipeGetCleared()) = nullptr;

				if (dumpFrameBeta->UnitLength() > 0) //inserts the dump frame into the code frames memory space or deletes the dump frame.
				{
					(*dumpFrame->PipeGetCleared()) = dumpFrameBeta; //inserts because theres dater in the dump which may be useful
				}
				else
				{
					exec->FreeFrameRecursive(dumpFrameBeta); //deletes
					delete dumpFrameBeta;
				}

				return success;
			}

			bool ValidateStack_ScopeExec(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if ((*dumpFrame->PipeGetCleared()) == nullptr) { exec->ErrorSetCode(CantAccessFrameInExecScope); return false; }

				IstackStackFrame codeFrameBeta = IstackStackFrame();
				IstackStackFrame dumpFrameBeta = IstackStackFrame();

				//(*dumpFrame->PipeGetCleared())->CopyIStackTo(&codeFrameBeta);
				exec->CopyIstackFrameAndModuleDataFromAndTo((*dumpFrame->PipeGetCleared()), &codeFrameBeta);

				bool success = exec->ProcessExacuteFrame(&codeFrameBeta, &dumpFrameBeta);

				exec->FreeFrameRecursive(&dumpFrameBeta);
				exec->FreeFrameRecursive(&codeFrameBeta);

				return success;
			}


			bool ValidateStack_PullData(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 1) { exec->ErrorSetCode(StackEmptyPullDataScope); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(DataIsNullPullDataScope); return false; }

				int popAmount = (*(int*)(dumpFrame->UnitTop().m_data)); //get amount
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();

				IstackStackFrame codeFrameBeta = IstackStackFrame();
				exec->CopyIstackFrameAndModuleDataFromAndTo((*dumpFrame->PipeGetCleared()), &codeFrameBeta); //access a copy of the scope

				for (int i = 0; i < popAmount; i++) //UnitPop untill amount is reached or untill failure
				{
					codeFrameBeta.UnitPop();
					if (codeFrameBeta.UnitLength() < 1) { exec->ErrorSetCode(PullIsBeyondStackLengthScope); return false; }
				}

				if (codeFrameBeta.UnitTop().m_data == nullptr) { exec->ErrorSetCode(PullIsNullPullDataScope); return false; } //is data valid

				IstackUnit newUnit = IstackUnit();
				exec->CopyUnitFromAndTo(codeFrameBeta.UnitTopPtr(), &newUnit);

				dumpFrame->UnitPush(newUnit); //copy data to dump
				exec->FreeFrame(&codeFrameBeta);


				return true;
			}

			bool ValidateStack_PullDataPop(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 1) { exec->ErrorSetCode(StackEmptyPullDataScope); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(DataIsNullPullDataScope); return false; }

				int popAmount = (*(int*)(dumpFrame->UnitTop().m_data)); //get amount
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();

				for (int i = 0; i < popAmount; i++) //UnitPop untill amount is reached or untill failure in live dump
				{
					(*dumpFrame->PipeGetCleared())->UnitPop();
					if ((*dumpFrame->PipeGetCleared())->UnitLength() < 1) { exec->ErrorSetCode(PullIsBeyondStackLengthScope); return false; }
				}

				if ((*dumpFrame->PipeGetCleared())->UnitTop().m_data == nullptr) { exec->ErrorSetCode(PullIsNullPullDataScope); return false; } //is data valid

				dumpFrame->UnitPush(dumpFrame->UnitTop()); //move data to dump
				(*dumpFrame->PipeGetCleared())->UnitPop();

				if ((*dumpFrame->PipeGetCleared())->UnitLength() > 0) //deletes the scope if theres no longer stuff inside
				{
					exec->FreeFrameRecursive((*dumpFrame->PipeGetCleared()));
					(*dumpFrame->PipeGetCleared()) = nullptr;
				}

				return true;
			}
			
		}

		void LoadScopeModules(IstackModuleExacuteor* module, IstackLexParser* parser)
		{
			ist::IstackModuleType scopeStart = ist::IstackModuleType();
			scopeStart.ValidateSelf = raw::ValidateSelf_ScopeStart;
			scopeStart.ValidateSelfPiped = raw::ValidateSelfPiped_ScopeStart;

			module->ModuleAdd(scopeStart);
			if (parser != nullptr) { parser->AddWord("}"); }


			ist::IstackModuleType scopeEndFliped = ist::IstackModuleType();
			scopeEndFliped.ValidateSelf = raw::ValidateSelf_Fail;
			scopeEndFliped.ValidateSelfPiped = raw::ValidateSelfPiped_ScopeEndFliped;

			module->ModuleAdd(scopeEndFliped);
			if (parser != nullptr) { parser->AddWord("{"); }


			ist::IstackModuleType scopeExec = ist::IstackModuleType();
			scopeExec.ValidateStack = raw::ValidateStack_ScopeExec;
			scopeExec.ValidateSelf = raw::ValidateSelf_Fail;

			module->ModuleAdd(scopeExec);
			if (parser != nullptr) { parser->AddWord("Exec"); }


			ist::IstackModuleType scopeExecPop = ist::IstackModuleType();
			scopeExecPop.ValidateStack = raw::ValidateStack_ScopeExecPop;
			scopeExecPop.ValidateSelf = raw::ValidateSelf_Fail;

			module->ModuleAdd(scopeExecPop);
			if (parser != nullptr) { parser->AddWord("ExecPop"); }


			ist::IstackModuleType pullData = ist::IstackModuleType();
			pullData.ValidateStack = raw::ValidateStack_PullData;
			pullData.ValidateSelf = raw::ValidateSelf_Fail;

			module->ModuleAdd(pullData);
			if (parser != nullptr) { parser->AddWord("iPullDataFromScope"); }


			ist::IstackModuleType pullDataPop = ist::IstackModuleType();
			pullDataPop.ValidateStack = raw::ValidateStack_PullDataPop;
			pullDataPop.ValidateSelf = raw::ValidateSelf_Fail;

			module->ModuleAdd(pullDataPop);
			if (parser != nullptr) { parser->AddWord("iPullDataFromScopePop"); }

		}
	}
}
