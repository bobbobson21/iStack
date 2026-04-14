#pragma once

#include "generics.h"

namespace ist
{
	namespace modules
	{
		namespace raw
		{
			static bool m_breakingLoopsForLoopsLib = false;
			static unsigned int m_varLibLocationForLoopsLib = 0;

			bool ValidateStack_Break(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				m_breakingLoopsForLoopsLib = true;
				return true;
			}

			bool ValidateStack_For(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->Length() < 1) { return false; }
				if (dumpFrame->Top().m_data == nullptr) { return false; }

				int LoopAmount = (*(int*)(dumpFrame->Top().m_data));
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();

				m_breakingLoopsForLoopsLib = false;

				for (int i = 0; i < LoopAmount; i++)
				{
					if ((*dumpFrame->GetClearedPipe()) == nullptr) { return false; }

					IstackStackFrame codeFrameBeta = IstackStackFrame();
					IstackStackFrame dumpFrameBeta = IstackStackFrame();

					IstackUnit LoopIndexUnit = IstackUnit();
					LoopIndexUnit.m_modualTypeCode = 1 + m_varLibLocationForLoopsLib; //1 + ?: four byte module 

					LoopIndexUnit.m_data = new int;
					(*((int*)LoopIndexUnit.m_data)) = i;

					dumpFrameBeta.Push(LoopIndexUnit);

					//(*dumpFrame->GetClearedPipe())->CopyIStackTo(&codeFrameBeta);
					exec->CopyIstackAndModuleDataFromAndTo((*dumpFrame->GetClearedPipe()), &codeFrameBeta);

					bool success = exec->ExacuteFrame(&codeFrameBeta, &dumpFrameBeta);

					exec->FreeFrameRecursive(&dumpFrameBeta);
					exec->FreeFrameRecursive(&codeFrameBeta);

					if (success == false) //error has occored so pass errror on
					{
						return false;
					}

					if (m_breakingLoopsForLoopsLib == true) //a break has occored so exit loop and reset brack status
					{
						m_breakingLoopsForLoopsLib = false;
						break;
					}
				}

				return true;
			}

			bool ValidateStack_While(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				int loopIndex = 0;
				m_breakingLoopsForLoopsLib = false;

				while(true)
				{
					if ((*dumpFrame->GetClearedPipe()) == nullptr) { return false; }

					IstackStackFrame codeFrameBeta = IstackStackFrame();
					IstackStackFrame dumpFrameBeta = IstackStackFrame();

					IstackUnit LoopIndexUnit = IstackUnit();
					LoopIndexUnit.m_modualTypeCode = 1 + m_varLibLocationForLoopsLib; //1 + ?: four byte module 

					LoopIndexUnit.m_data = new int;
					(*((int*)LoopIndexUnit.m_data)) = loopIndex;
					loopIndex++;

					dumpFrameBeta.Push(LoopIndexUnit); //allows loop code to access loop index

					//(*dumpFrame->GetClearedPipe())->CopyIStackTo(&codeFrameBeta);
					exec->CopyIstackAndModuleDataFromAndTo((*dumpFrame->GetClearedPipe()), &codeFrameBeta);

					bool success = exec->ExacuteFrame(&codeFrameBeta, &dumpFrameBeta);

					exec->FreeFrameRecursive(&dumpFrameBeta);
					exec->FreeFrameRecursive(&codeFrameBeta);

					if (success == false) //error has occoured pass error on
					{
						return false;
					}

					if (m_breakingLoopsForLoopsLib == true) //a break has occored so exit loop and reset brack status
					{
						m_breakingLoopsForLoopsLib = false;
						break;
					}
				}

				return true;
			}


			bool ValidateStack_ForBreakFail(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->Length() < 1) { return false; }
				if (dumpFrame->Top().m_data == nullptr) { return false; }

				int LoopAmount = (*(int*)(dumpFrame->Top().m_data));
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();

				m_breakingLoopsForLoopsLib = false;

				for (int i = 0; i < LoopAmount; i++)
				{
					if ((*dumpFrame->GetClearedPipe()) == nullptr) { return false; }

					IstackStackFrame codeFrameBeta = IstackStackFrame();
					IstackStackFrame dumpFrameBeta = IstackStackFrame();

					IstackUnit LoopIndexUnit = IstackUnit();
					LoopIndexUnit.m_modualTypeCode = 1 + m_varLibLocationForLoopsLib; //1 + ?: four byte module 

					LoopIndexUnit.m_data = new int;
					(*((int*)LoopIndexUnit.m_data)) = i;

					dumpFrameBeta.Push(LoopIndexUnit); //allows loop code to access loop index

					//(*dumpFrame->GetClearedPipe())->CopyIStackTo(&codeFrameBeta);
					exec->CopyIstackAndModuleDataFromAndTo((*dumpFrame->GetClearedPipe()), &codeFrameBeta);

					bool success = exec->ExacuteFrame(&codeFrameBeta, &dumpFrameBeta);

					exec->FreeFrameRecursive(&dumpFrameBeta);
					exec->FreeFrameRecursive(&codeFrameBeta);

					if (m_breakingLoopsForLoopsLib == true) //a break has occoured so exit the loop and invalidate the stack
					{
						m_breakingLoopsForLoopsLib = false;
						return false;
					}
				}

				return true;
			}

			bool ValidateStack_ForEndFail(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->Length() < 1) { return false; }
				if (dumpFrame->Top().m_data == nullptr) { return false; }

				int LoopAmount = (*(int*)(dumpFrame->Top().m_data));
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();

				m_breakingLoopsForLoopsLib = false;

				for (int i = 0; i < LoopAmount; i++)
				{
					if ((*dumpFrame->GetClearedPipe()) == nullptr) { return false; }

					IstackStackFrame codeFrameBeta = IstackStackFrame();
					IstackStackFrame dumpFrameBeta = IstackStackFrame();

					IstackUnit LoopIndexUnit = IstackUnit();
					LoopIndexUnit.m_modualTypeCode = 1 + m_varLibLocationForLoopsLib; //1 + ?: four byte module 

					LoopIndexUnit.m_data = new int;
					(*((int*)LoopIndexUnit.m_data)) = i;

					dumpFrameBeta.Push(LoopIndexUnit); //so it knows the index of the loop

					//(*dumpFrame->GetClearedPipe())->CopyIStackTo(&codeFrameBeta);
					exec->CopyIstackAndModuleDataFromAndTo((*dumpFrame->GetClearedPipe()), &codeFrameBeta);

					bool success = exec->ExacuteFrame(&codeFrameBeta, &dumpFrameBeta);

					exec->FreeFrameRecursive(&dumpFrameBeta);
					exec->FreeFrameRecursive(&codeFrameBeta);

					if (m_breakingLoopsForLoopsLib == true) //exiting loop
					{
						break;
					}
				}

				if (m_breakingLoopsForLoopsLib == false) //was loop exited because it ended
				{
					return false; //if so invalidate stack
				}

				m_breakingLoopsForLoopsLib = false; //was loop exited because of break
				return true; //if so validate stack
			}

		}

		void LoadLoopsModules(IstackModuleExacuteor* module, IstackLexParser* parser, unsigned int varLibOffset)
		{
			raw::m_varLibLocationForLoopsLib = 0;

			ist::IstackModuleType breakMod = ist::IstackModuleType();
			breakMod.ValidateStack = raw::ValidateStack_Break;
			breakMod.ValidateSelf = raw::ValidateSelf_Fail;
			//ifMod.FreeData = raw::FreeData_Single; //not needed as the if module can not contain data

			module->AddModule(breakMod);
			if (parser != nullptr) { parser->AddWords("Break"); }


			ist::IstackModuleType forMod = ist::IstackModuleType();
			forMod.ValidateStack = raw::ValidateStack_For;
			forMod.ValidateSelf = raw::ValidateSelf_Fail;
			//ifMod.FreeData = raw::FreeData_Single; //not needed as the if module can not contain data

			module->AddModule(forMod);
			if (parser != nullptr) { parser->AddWords("iFor<<i"); }


			ist::IstackModuleType whileMod = ist::IstackModuleType();
			whileMod.ValidateStack = raw::ValidateStack_While;
			whileMod.ValidateSelf = raw::ValidateSelf_Fail;
			//ifMod.FreeData = raw::FreeData_Single; //not needed as the if module can not contain data

			module->AddModule(whileMod);
			if (parser != nullptr) { parser->AddWords("While<<i"); }


			ist::IstackModuleType forBreakFailMod = ist::IstackModuleType();
			forBreakFailMod.ValidateStack = raw::ValidateStack_ForBreakFail;
			forBreakFailMod.ValidateSelf = raw::ValidateSelf_Fail;
			//ifMod.FreeData = raw::FreeData_Single; //not needed as the if module can not contain data

			module->AddModule(forBreakFailMod);
			if (parser != nullptr) { parser->AddWords("iForBreakFail<<i"); }


			ist::IstackModuleType forEndFailMod = ist::IstackModuleType();
			forEndFailMod.ValidateStack = raw::ValidateStack_ForEndFail;
			forEndFailMod.ValidateSelf = raw::ValidateSelf_Fail;
			//ifMod.FreeData = raw::FreeData_Single; //not needed as the if module can not contain data

			module->AddModule(forEndFailMod);
			if (parser != nullptr) { parser->AddWords("iForEndFail<<i"); }
		}
	}
}