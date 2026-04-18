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
				if ((*dumpFrame->GetClearedPipe()) != nullptr)
				{
					exec->FreeFrameRecursive((*dumpFrame->GetClearedPipe()), true);
					(*dumpFrame->GetClearedPipe()) = nullptr;
				}

				dumpFrame->CreatePipe();
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
				if ((*dumpFrame->GetClearedPipe()) == nullptr) { exec->SetErrorCode(CantAccessFrameInExecPopScope); return false; }

				IstackStackFrame* dumpFrameBeta = new IstackStackFrame(); //the dump frame
				bool success = exec->ExacuteFrame((*dumpFrame->GetClearedPipe()), dumpFrameBeta); //exacutes the dump frame
				
				exec->FreeFrameRecursive((*dumpFrame->GetClearedPipe())); //deletes the code frame
				(*dumpFrame->GetClearedPipe()) = nullptr;

				if (dumpFrameBeta->Length() > 0) //inserts the dump frame into the code frames memory space or deletes the dump frame.
				{
					(*dumpFrame->GetClearedPipe()) = dumpFrameBeta; //inserts because theres dater in the dump which may be useful
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
				if ((*dumpFrame->GetClearedPipe()) == nullptr) { exec->SetErrorCode(CantAccessFrameInExecScope); return false; }

				IstackStackFrame codeFrameBeta = IstackStackFrame();
				IstackStackFrame dumpFrameBeta = IstackStackFrame();

				//(*dumpFrame->GetClearedPipe())->CopyIStackTo(&codeFrameBeta);
				exec->CopyIstackFrameAndModuleDataFromAndTo((*dumpFrame->GetClearedPipe()), &codeFrameBeta);

				bool success = exec->ExacuteFrame(&codeFrameBeta, &dumpFrameBeta);

				exec->FreeFrameRecursive(&dumpFrameBeta);
				exec->FreeFrameRecursive(&codeFrameBeta);

				return success;
			}
		

			bool ValidateStack_PullData(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->Length() < 1) { exec->SetErrorCode(StackEmptyPullDataScope); return false; }
				if (dumpFrame->Top().m_data == nullptr) { exec->SetErrorCode(DataIsNullPullDataScope); return false; }

				int popAmount = (*(int*)(dumpFrame->Top().m_data)); //get amount
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();

				IstackStackFrame codeFrameBeta = IstackStackFrame();
				exec->CopyIstackFrameAndModuleDataFromAndTo((*dumpFrame->GetClearedPipe()), &codeFrameBeta); //access a copy of the scope

				for (int i = 0; i < popAmount; i++) //pop untill amount is reached or untill failure
				{
					codeFrameBeta.Pop();
					if (codeFrameBeta.Length() < 1) { exec->SetErrorCode(PullIsBeyondStackLengthScope); return false; }
				}

				if (codeFrameBeta.Top().m_data == nullptr) { exec->SetErrorCode(PullIsNullPullDataScope); return false; } //is data valid

				IstackUnit newUnit = IstackUnit();
				exec->CopyUnitFromAndTo(codeFrameBeta.TopPtr(), &newUnit);

				dumpFrame->Push(newUnit); //copy data to dump
				exec->FreeFrame(&codeFrameBeta);


				return true;
			}

			bool ValidateStack_PullDataPop(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->Length() < 1) { exec->SetErrorCode(StackEmptyPullDataScope); return false; }
				if (dumpFrame->Top().m_data == nullptr) { exec->SetErrorCode(DataIsNullPullDataScope); return false; }

				int popAmount = (*(int*)(dumpFrame->Top().m_data)); //get amount
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();

				for (int i = 0; i < popAmount; i++) //pop untill amount is reached or untill failure in live dump
				{
					(*dumpFrame->GetClearedPipe())->Pop();
					if ((*dumpFrame->GetClearedPipe())->Length() < 1) { exec->SetErrorCode(PullIsBeyondStackLengthScope); return false; }
				}

				if ((*dumpFrame->GetClearedPipe())->Top().m_data == nullptr) { exec->SetErrorCode(PullIsNullPullDataScope); return false; } //is data valid

				dumpFrame->Push(dumpFrame->Top()); //move data to dump
				(*dumpFrame->GetClearedPipe())->Pop();

				if ((*dumpFrame->GetClearedPipe())->Length() > 0) //deletes the scope if theres no longer stuff inside
				{
					exec->FreeFrameRecursive((*dumpFrame->GetClearedPipe()));
					(*dumpFrame->GetClearedPipe()) = nullptr;
				}

				return true;
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


			ist::IstackModuleType pullData = ist::IstackModuleType();
			pullData.ValidateStack = raw::ValidateStack_PullData;
			pullData.ValidateSelf = raw::ValidateSelf_Fail;

			module->AddModule(pullData);
			if (parser != nullptr) { parser->AddWords("iPullDataFromScope"); }


			ist::IstackModuleType pullDataPop = ist::IstackModuleType();
			pullDataPop.ValidateStack = raw::ValidateStack_PullDataPop;
			pullDataPop.ValidateSelf = raw::ValidateSelf_Fail;

			module->AddModule(pullDataPop);
			if (parser != nullptr) { parser->AddWords("iPullDataFromScopePop"); }

		}
	}
}
