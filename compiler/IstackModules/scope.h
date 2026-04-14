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
			bool ValidateSelf_ScopeStart(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if ((*dumpFrame->GetClearedPipe()) != nullptr)
				{
					exec->FreeFrameRecursive((*dumpFrame->GetClearedPipe()), true);
					(*dumpFrame->GetClearedPipe()) = nullptr;
				}

				dumpFrame->SetPipe(new IstackStackFrame());
				dumpFrame->PushPipeDepthContext();
				return false;
			}

			bool ValidateSelfPiped_ScopeStart(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				dumpFrame->PushPipeDepthContext();
				return true;
			}


			bool ValidateSelfPiped_ScopeEndFliped(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				dumpFrame->PopPipeDepthContext();

				if (dumpFrame->TopPipeDepthContext() == 0)
				{
					dumpFrame->ClearPipe();
					(*dumpFrame->GetClearedPipe())->Flip();
					return false;
				}

				return true;
			}


			bool ValidateStack_ScopeExecPop(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if ((*dumpFrame->GetClearedPipe()) == nullptr) { return false; }

				IstackStackFrame dumpFrameBeta = IstackStackFrame();

				bool success = exec->ExacuteFrame((*dumpFrame->GetClearedPipe()), &dumpFrameBeta);
				
				exec->FreeFrameRecursive(&dumpFrameBeta);
				exec->FreeFrameRecursive((*dumpFrame->GetClearedPipe()));

				(*dumpFrame->GetClearedPipe()) = nullptr;

				return success;
			}

			bool ValidateStack_ScopeExec(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if ((*dumpFrame->GetClearedPipe()) == nullptr) { return false; }

				IstackStackFrame codeFrameBeta = IstackStackFrame();
				IstackStackFrame dumpFrameBeta = IstackStackFrame();

				//(*dumpFrame->GetClearedPipe())->CopyIStackTo(&codeFrameBeta);
				exec->CopyIstackAndModuleDataFromAndTo((*dumpFrame->GetClearedPipe()), &codeFrameBeta);

				bool success = exec->ExacuteFrame(&codeFrameBeta, &dumpFrameBeta);

				exec->FreeFrameRecursive(&dumpFrameBeta);
				exec->FreeFrameRecursive(&codeFrameBeta);

				return success;
			}
		

			bool ValidateStack_PullData(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->Length() < 1) { return false; }
				if (dumpFrame->Top().m_data == nullptr) { return false; }

				int popAmount = (*(int*)(dumpFrame->Top().m_data));
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();

				IstackStackFrame codeFrameBeta = IstackStackFrame();
				exec->CopyIstackAndModuleDataFromAndTo((*dumpFrame->GetClearedPipe()), &codeFrameBeta);

				exec->FreeFrame(&codeFrameBeta);

				for (int i = 0; i < popAmount; i++)
				{
					codeFrameBeta.Pop();
				}

				IstackUnit newUnit = IstackUnit();
				newUnit.m_modualTypeCode = codeFrameBeta.Top().m_modualTypeCode;
				exec->CopyUnitFromAndTo(codeFrameBeta.TopPtr(), &newUnit);

				dumpFrame->Push(newUnit);
			}

			bool ValidateStack_PullDataPop(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->Length() < 1) { return false; }
				if (dumpFrame->Top().m_data == nullptr) { return false; }

				int popAmount = (*(int*)(dumpFrame->Top().m_data));
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();

				for (int i = 0; i < popAmount; i++)
				{
					(*dumpFrame->GetClearedPipe())->Pop();
				}

				IstackUnit newUnit = IstackUnit();
				newUnit.m_modualTypeCode = dumpFrame->Top().m_modualTypeCode;
				exec->CopyUnitFromAndTo(dumpFrame->TopPtr(), &newUnit);

				dumpFrame->Push(newUnit);
			}
			
		}

		void LoadScopeModules(IstackModuleExacuteor* module, IstackLexParser* parser)
		{
			ist::IstackModuleType scopeStart = ist::IstackModuleType();
			scopeStart.ValidateSelf = raw::ValidateSelf_ScopeStart;
			scopeStart.ValidateSelfPiped = raw::ValidateSelfPiped_ScopeStart;

			module->AddModule(scopeStart);
			if (parser != nullptr) { parser->AddWords("}"); }


			ist::IstackModuleType scopeEndFliped = ist::IstackModuleType();
			scopeEndFliped.ValidateStack = raw::ValidateSelf_Fail;
			scopeEndFliped.ValidateSelfPiped = raw::ValidateSelfPiped_ScopeEndFliped;

			module->AddModule(scopeEndFliped);
			if (parser != nullptr) { parser->AddWords("{"); }


			ist::IstackModuleType scopeExec = ist::IstackModuleType();
			scopeExec.ValidateSelf = raw::ValidateStack_ScopeExec;

			module->AddModule(scopeExec);
			if (parser != nullptr) { parser->AddWords("Exec"); }


			ist::IstackModuleType scopeExecPop = ist::IstackModuleType();
			scopeExecPop.ValidateSelf = raw::ValidateStack_ScopeExecPop;

			module->AddModule(scopeExecPop);
			if (parser != nullptr) { parser->AddWords("ExecPop"); }

		}
	}
}
