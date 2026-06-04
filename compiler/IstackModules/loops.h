#pragma once

#include <map>
#include <thread>

#include "generics.h"

namespace ist
{
	namespace modules
	{
		enum moduleLoopsErrorCodes : unsigned int
		{
			StackEmptyLoops = 201,
			DataIsNullLoops = 202,
			PipeCantBeFoundLoops = 203,

			BreakInBreakFailureLoops = 204,
			ExitInEndFailureLoops = 205,
		};

		namespace raw
		{
			static std::map<std::thread::id, bool> n_breakingLoopsForLoopsLib = std::map<std::thread::id, bool>();
			static unsigned int n_varLibLocationForLoopsLib = 0;

			bool ValidateStack_Break(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				n_breakingLoopsForLoopsLib[std::this_thread::get_id()] = true;
				return true;
			}

			bool ValidateStack_For(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 1) { 
					exec->ErrorSetCode(StackEmptyLoops); return false; 
				}
				if (dumpFrame->UnitTop().m_data == nullptr) {
					exec->ErrorSetCode(DataIsNullLoops); return false;
				}

				int LoopAmount = (*(int*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();

				n_breakingLoopsForLoopsLib[std::this_thread::get_id()] = false;

				for (int i = 0; i < LoopAmount; i++)
				{
					if ((*dumpFrame->PipeGetCleared()) == nullptr) {
						exec->ErrorSetCode(PipeCantBeFoundLoops); return false; 
					}

					IstackStackFrame codeFrameBeta = IstackStackFrame();
					IstackStackFrame dumpFrameBeta = IstackStackFrame();

					IstackUnit LoopIndexUnit = IstackUnit();
					LoopIndexUnit.m_modualTypeCode = 1 + n_varLibLocationForLoopsLib; //1 + ?: four byte module 

					LoopIndexUnit.m_data = new int;
					(*((int*)LoopIndexUnit.m_data)) = i;

					dumpFrameBeta.UnitPush(LoopIndexUnit);

					//(*dumpFrame->PipeGetCleared())->CopyIStackTo(&codeFrameBeta);
					exec->CopyIstackFrameAndModuleDataFromAndTo((*dumpFrame->PipeGetCleared()), &codeFrameBeta);

					bool success = exec->ProcessExacuteFrame(&codeFrameBeta, &dumpFrameBeta);

					exec->FreeFrameRecursive(&dumpFrameBeta);
					exec->FreeFrameRecursive(&codeFrameBeta);

					if (success == false) //error has occored so pass errror on
					{
						//no error codes here
						return false;
					}

					if (n_breakingLoopsForLoopsLib.count(std::this_thread::get_id()) > 0 && n_breakingLoopsForLoopsLib[std::this_thread::get_id()] == true) //a break has occored so exit loop and reset brack status
					{
						n_breakingLoopsForLoopsLib[std::this_thread::get_id()] = false;
						break;
					}
				}

				return true;
			}

			bool ValidateStack_While(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				int loopIndex = 0;
				n_breakingLoopsForLoopsLib[std::this_thread::get_id()] = false;

				while(true)
				{
					if ((*dumpFrame->PipeGetCleared()) == nullptr) { exec->ErrorSetCode(PipeCantBeFoundLoops);  return false; }

					IstackStackFrame codeFrameBeta = IstackStackFrame();
					IstackStackFrame dumpFrameBeta = IstackStackFrame();

					IstackUnit LoopIndexUnit = IstackUnit();
					LoopIndexUnit.m_modualTypeCode = 1 + n_varLibLocationForLoopsLib; //1 + ?: four byte module 

					LoopIndexUnit.m_data = new int;
					(*((int*)LoopIndexUnit.m_data)) = loopIndex;
					loopIndex++;

					dumpFrameBeta.UnitPush(LoopIndexUnit); //allows loop code to access loop index

					//(*dumpFrame->PipeGetCleared())->CopyIStackTo(&codeFrameBeta);
					exec->CopyIstackFrameAndModuleDataFromAndTo((*dumpFrame->PipeGetCleared()), &codeFrameBeta);

					bool success = exec->ProcessExacuteFrame(&codeFrameBeta, &dumpFrameBeta);

					exec->FreeFrameRecursive(&dumpFrameBeta);
					exec->FreeFrameRecursive(&codeFrameBeta);

					if (success == false) //error has occoured pass error on
					{
						return false;
					}

					if (n_breakingLoopsForLoopsLib.count(std::this_thread::get_id()) > 0 && n_breakingLoopsForLoopsLib[std::this_thread::get_id()] == true) //a break has occored so exit loop and reset brack status
					{
						n_breakingLoopsForLoopsLib[std::this_thread::get_id()] = false;
						break;
					}
				}

				return true;
			}


			bool ValidateStack_ForBreakFail(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 1) { exec->ErrorSetCode(StackEmptyLoops); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(DataIsNullLoops); return false; }

				int LoopAmount = (*(int*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();

				n_breakingLoopsForLoopsLib[std::this_thread::get_id()] = false;

				for (int i = 0; i < LoopAmount; i++)
				{
					if ((*dumpFrame->PipeGetCleared()) == nullptr) { exec->ErrorSetCode(PipeCantBeFoundLoops); return false; }

					IstackStackFrame codeFrameBeta = IstackStackFrame();
					IstackStackFrame dumpFrameBeta = IstackStackFrame();

					IstackUnit LoopIndexUnit = IstackUnit();
					LoopIndexUnit.m_modualTypeCode = 1 + n_varLibLocationForLoopsLib; //1 + ?: four byte module 

					LoopIndexUnit.m_data = new int;
					(*((int*)LoopIndexUnit.m_data)) = i;

					dumpFrameBeta.UnitPush(LoopIndexUnit); //allows loop code to access loop index

					//(*dumpFrame->PipeGetCleared())->CopyIStackTo(&codeFrameBeta);
					exec->CopyIstackFrameAndModuleDataFromAndTo((*dumpFrame->PipeGetCleared()), &codeFrameBeta);

					bool success = exec->ProcessExacuteFrame(&codeFrameBeta, &dumpFrameBeta);

					exec->FreeFrameRecursive(&dumpFrameBeta);
					exec->FreeFrameRecursive(&codeFrameBeta);

					if (n_breakingLoopsForLoopsLib.count(std::this_thread::get_id()) > 0 && n_breakingLoopsForLoopsLib[std::this_thread::get_id()] == true) //a break has occoured so exit the loop and invalidate the stack
					{
						n_breakingLoopsForLoopsLib[std::this_thread::get_id()] = false;
						exec->ErrorSetCode(BreakInBreakFailureLoops);
						return false;
					}
				}

				return true;
			}

			bool ValidateStack_ForEndFail(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 1) { exec->ErrorSetCode(StackEmptyLoops); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(DataIsNullLoops); return false; }

				int LoopAmount = (*(int*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();

				n_breakingLoopsForLoopsLib[std::this_thread::get_id()] = false;

				for (int i = 0; i < LoopAmount; i++)
				{
					if ((*dumpFrame->PipeGetCleared()) == nullptr) { exec->ErrorSetCode(PipeCantBeFoundLoops); return false; }

					IstackStackFrame codeFrameBeta = IstackStackFrame();
					IstackStackFrame dumpFrameBeta = IstackStackFrame();

					IstackUnit LoopIndexUnit = IstackUnit();
					LoopIndexUnit.m_modualTypeCode = 1 + n_varLibLocationForLoopsLib; //1 + ?: four byte module 

					LoopIndexUnit.m_data = new int;
					(*((int*)LoopIndexUnit.m_data)) = i;

					dumpFrameBeta.UnitPush(LoopIndexUnit); //so it knows the index of the loop

					//(*dumpFrame->PipeGetCleared())->CopyIStackTo(&codeFrameBeta);
					exec->CopyIstackFrameAndModuleDataFromAndTo((*dumpFrame->PipeGetCleared()), &codeFrameBeta);

					bool success = exec->ProcessExacuteFrame(&codeFrameBeta, &dumpFrameBeta);

					exec->FreeFrameRecursive(&dumpFrameBeta);
					exec->FreeFrameRecursive(&codeFrameBeta);

					if (n_breakingLoopsForLoopsLib.count(std::this_thread::get_id()) > 0 && n_breakingLoopsForLoopsLib[std::this_thread::get_id()] == true) //exiting loop
					{
						break;
					}
				}

				if (n_breakingLoopsForLoopsLib.count(std::this_thread::get_id()) == true && n_breakingLoopsForLoopsLib[std::this_thread::get_id()] == false) //was loop exited because it ended
				{
					exec->ErrorSetCode(ExitInEndFailureLoops);
					return false; //if so invalidate stack
				}

				n_breakingLoopsForLoopsLib[std::this_thread::get_id()] = false; //was loop exited because of break
				return true; //if so validate stack
			}

		}

		void LoadLoopsModules(IstackModuleExacuteor* module, IstackLexParser* parser, unsigned int varLibOffset)
		{
			raw::n_varLibLocationForLoopsLib = 0;

			ist::IstackModuleType breakMod = ist::IstackModuleType();
			breakMod.ValidateStack = raw::ValidateStack_Break;
			breakMod.ValidateSelf = raw::Validate_Fail;
			//ifMod.FreeData = raw::FreeData_Single; //not needed as the if module can not contain data

			module->ModuleAddType(breakMod);
			if (parser != nullptr) { parser->WordsAdd("Break"); }


			ist::IstackModuleType forMod = ist::IstackModuleType();
			forMod.ValidateStack = raw::ValidateStack_For;
			forMod.ValidateSelf = raw::Validate_Fail;
			//ifMod.FreeData = raw::FreeData_Single; //not needed as the if module can not contain data

			module->ModuleAddType(forMod);
			if (parser != nullptr) { parser->WordsAdd("iFor<<i"); }


			ist::IstackModuleType whileMod = ist::IstackModuleType();
			whileMod.ValidateStack = raw::ValidateStack_While;
			whileMod.ValidateSelf = raw::Validate_Fail;
			//ifMod.FreeData = raw::FreeData_Single; //not needed as the if module can not contain data

			module->ModuleAddType(whileMod);
			if (parser != nullptr) { parser->WordsAdd("While<<i"); }


			ist::IstackModuleType forBreakFailMod = ist::IstackModuleType();
			forBreakFailMod.ValidateStack = raw::ValidateStack_ForBreakFail;
			forBreakFailMod.ValidateSelf = raw::Validate_Fail;
			//ifMod.FreeData = raw::FreeData_Single; //not needed as the if module can not contain data

			module->ModuleAddType(forBreakFailMod);
			if (parser != nullptr) { parser->WordsAdd("iForBreakFail<<i"); }


			ist::IstackModuleType forEndFailMod = ist::IstackModuleType();
			forEndFailMod.ValidateStack = raw::ValidateStack_ForEndFail;
			forEndFailMod.ValidateSelf = raw::Validate_Fail;
			//ifMod.FreeData = raw::FreeData_Single; //not needed as the if module can not contain data

			module->ModuleAddType(forEndFailMod);
			if (parser != nullptr) { parser->WordsAdd("iForEndFail<<i"); }
		}
	}
}