#pragma once

#include <string>
#include <map>
#include <thread>

#include "generics.h"

namespace ist
{
	namespace modules
	{
		enum moduleFunctionErrorCodes : unsigned int
		{
			InvalidFunctionNameFunction = 801,
			FunctionNameAlreadyInUse = 802,

			UnableToFindFrameFunction = 803,
			UnableToFindFunctionFunction = 804,

		};

		namespace raw
		{
			static std::map<std::thread::id, std::map<std::string, ist::IstackStackFrame>> n_functionMap = std::map<std::thread::id, std::map<std::string, ist::IstackStackFrame>>();

			bool ValidateStack_CreateFunction(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if ((*dumpFrame->PipeGetCleared()) == nullptr) { exec->ErrorSetCode(UnableToFindFrameFunction); return false; }

				std::string adress = "";

				try
				{
					adress = (*(std::string*)(*data));
				}
				catch (...)
				{
					exec->ErrorSetCode(InvalidFunctionNameFunction);
					return false;
				}

				if (n_functionMap.count(std::this_thread::get_id()) < 1) { n_functionMap[std::this_thread::get_id()] = std::map<std::string, ist::IstackStackFrame>(); }
				if (n_functionMap[std::this_thread::get_id()].count(adress) > 1) { exec->ErrorSetCode(FunctionNameAlreadyInUse); return false; }
				if ((*dumpFrame->PipeGetCleared()) == nullptr) { exec->ErrorSetCode(UnableToFindFrameFunction); return false; }

				n_functionMap[std::this_thread::get_id()][adress] = ist::IstackStackFrame();
				exec->CopyIstackFrameAndModuleDataFromAndTo((*dumpFrame->PipeGetCleared()), &n_functionMap[std::this_thread::get_id()][adress]);

				return true;
			}

			bool ValidateStack_CallFunction(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				std::string adress = "";

				if ((*data) != nullptr)
				{
					try
					{
						adress = (*(std::string*)(*data));
					}
					catch (...)
					{
						exec->ErrorSetCode(InvalidFunctionNameFunction);
						return false;
					}
				}
				else
				{
					try
					{
						adress = (*(std::string*)(dumpFrame->UnitTop().m_data));
						exec->FreeUnit(dumpFrame->UnitTopPtr());
						dumpFrame->UnitPop();
					}
					catch (...)
					{
						exec->ErrorSetCode(InvalidFunctionNameFunction);
						return false;
					}
				}

				IstackStackFrame codeFrameBeta = IstackStackFrame();
				IstackStackFrame dumpFrameBeta = IstackStackFrame();

				if (n_functionMap.count(std::this_thread::get_id()) < 1) { exec->ErrorSetCode(UnableToFindFunctionFunction); return false; }
				if (n_functionMap[std::this_thread::get_id()].count(adress) < 1) { exec->ErrorSetCode(UnableToFindFunctionFunction); return false; }

				exec->CopyIstackFrameAndModuleDataFromAndTo(&n_functionMap[std::this_thread::get_id()][adress], &codeFrameBeta);

				bool success = exec->ProcessExacuteFrame(&codeFrameBeta, &dumpFrameBeta);

				exec->FreeFrameRecursive(&dumpFrameBeta);
				exec->FreeFrameRecursive(&codeFrameBeta);

				return success;
			}

			bool ValidateStack_CallFunctionWithExtange(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				std::string adress = "";

				if ((*data) != nullptr)
				{
					try
					{
						adress = (*(std::string*)(*data));
					}
					catch (...)
					{
						exec->ErrorSetCode(InvalidFunctionNameFunction);
						return false;
					}
				}
				else
				{
					try
					{
						adress = (*(std::string*)(dumpFrame->UnitTop().m_data));
						exec->FreeUnit(dumpFrame->UnitTopPtr());
						dumpFrame->UnitPop();
					}
					catch (...)
					{
						exec->ErrorSetCode(InvalidFunctionNameFunction);
						return false;
					}
				}

				IstackStackFrame codeFrameBeta = IstackStackFrame();
				IstackStackFrame dumpFrameBeta = IstackStackFrame();


				dumpFrame->UnitFlip();
				while (dumpFrame->UnitLength() > 0)
				{
					dumpFrameBeta.UnitPush(dumpFrame->UnitTop());
					dumpFrame->UnitPop();
				}
				dumpFrame->UnitFree();


				if (n_functionMap.count(std::this_thread::get_id()) < 1) { exec->ErrorSetCode(UnableToFindFunctionFunction); return false; }
				if (n_functionMap[std::this_thread::get_id()].count(adress) < 1) { exec->ErrorSetCode(UnableToFindFunctionFunction); return false; }

				exec->CopyIstackFrameAndModuleDataFromAndTo(&n_functionMap[std::this_thread::get_id()][adress], &codeFrameBeta);

				bool success = exec->ProcessExacuteFrame(&codeFrameBeta, &dumpFrameBeta);


				dumpFrameBeta.UnitFlip();
				while (dumpFrameBeta.UnitLength() > 0)
				{
					dumpFrame->UnitPush(dumpFrameBeta.UnitTop());
					dumpFrameBeta.UnitPop();
				}
				dumpFrameBeta.UnitFree();

				exec->FreeFrameRecursive(&dumpFrameBeta);
				exec->FreeFrameRecursive(&codeFrameBeta);
				return success;
			}

			bool ValidateStack_CallFunctionWithExtangeTopOnly(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				std::string adress = "";
				
				if ((*data) != nullptr)
				{
					try
					{
						adress = (*(std::string*)(*data));
					}
					catch (...)
					{
						exec->ErrorSetCode(InvalidFunctionNameFunction);
						return false;
					}
				}
				else
				{
					try
					{
						adress = (*(std::string*)(dumpFrame->UnitTop().m_data));
						exec->FreeUnit(dumpFrame->UnitTopPtr());
						dumpFrame->UnitPop();
					}
					catch (...)
					{
						exec->ErrorSetCode(InvalidFunctionNameFunction);
						return false;
					}
				}

				IstackStackFrame codeFrameBeta = IstackStackFrame();
				IstackStackFrame dumpFrameBeta = IstackStackFrame();

				if (dumpFrame->UnitLength() > 0)
				{
					IstackUnit tempUnit = IstackUnit();
					exec->CopyUnitFromAndTo(dumpFrame->UnitTopPtr(), &tempUnit);
					dumpFrameBeta.UnitPush(tempUnit);
				}

				if (n_functionMap.count(std::this_thread::get_id()) < 1) { exec->ErrorSetCode(UnableToFindFunctionFunction); return false; }
				if (n_functionMap[std::this_thread::get_id()].count(adress) < 1) { exec->ErrorSetCode(UnableToFindFunctionFunction); return false; }

				exec->CopyIstackFrameAndModuleDataFromAndTo(&n_functionMap[std::this_thread::get_id()][adress], &codeFrameBeta);

				bool success = exec->ProcessExacuteFrame(&codeFrameBeta, &dumpFrameBeta);


				if (dumpFrameBeta.UnitLength() > 0)
				{
					IstackUnit tempUnit = IstackUnit();
					exec->CopyUnitFromAndTo(dumpFrameBeta.UnitTopPtr(), &tempUnit);
					dumpFrame->UnitPush(tempUnit);
				}

				exec->FreeFrameRecursive(&dumpFrameBeta);
				exec->FreeFrameRecursive(&codeFrameBeta);
				return success;
			}
		
			bool ValidateStack_CanCallFunction(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				std::string adress = "";

				try
				{
					adress = (*(std::string*)(dumpFrame->UnitTop().m_data));
					exec->FreeUnit(dumpFrame->UnitTopPtr());
					dumpFrame->UnitPop();
				}
				catch (...)
				{
					exec->ErrorSetCode(InvalidFunctionNameFunction);
					return false;
				}

				bool result = true;

				delete (*data);
				(*data) = new bool;
				(*(bool*)(*data)) = result;

				if (n_functionMap.count(std::this_thread::get_id()) < 1) { result = false; (*(bool*)(*data)) = result; }
				if (n_functionMap[std::this_thread::get_id()].count(adress) < 1) { result = false; (*(bool*)(*data)) = result; }

				return true;
			}
		}

		void LoadFunctionModules(IstackModuleExacuteor* module, IstackLexParser* parser)
		{

			ist::IstackModuleType fn = ist::IstackModuleType();
			fn.ValidateStack = raw::ValidateStack_CreateFunction;
			fn.ValidateSelf = raw::Validate_Fail;
			fn.FreeData = raw::FreeData_String;
			fn.CopyData = raw::CopyData_String;

			module->ModuleAddType(fn);
			if (parser != nullptr) { parser->WordsAdd("Fn"); }


			ist::IstackModuleType call = ist::IstackModuleType();
			call.ValidateStack = raw::ValidateStack_CallFunction;
			call.ValidateSelf = raw::Validate_Fail;
			call.FreeData = raw::FreeData_String;
			call.CopyData = raw::CopyData_String;

			module->ModuleAddType(call);
			if (parser != nullptr) { parser->WordsAdd("Call"); }


			ist::IstackModuleType callexc = ist::IstackModuleType();
			callexc.ValidateStack = raw::ValidateStack_CallFunctionWithExtange;
			callexc.ValidateSelf = raw::Validate_Fail;
			callexc.FreeData = raw::FreeData_String;
			callexc.CopyData = raw::CopyData_String;

			module->ModuleAddType(callexc);
			if (parser != nullptr) { parser->WordsAdd("CallExc"); }


			ist::IstackModuleType callexctop = ist::IstackModuleType();
			callexctop.ValidateStack = raw::ValidateStack_CallFunctionWithExtangeTopOnly;
			callexctop.ValidateSelf = raw::Validate_Fail;
			callexctop.FreeData = raw::FreeData_String;
			callexctop.CopyData = raw::CopyData_String;

			module->ModuleAddType(callexctop);
			if (parser != nullptr) { parser->WordsAdd("CallExcTop"); }


			ist::IstackModuleType canFn = ist::IstackModuleType();
			canFn.ValidateStack = raw::ValidateStack_CanCallFunction;
			canFn.ValidateSelf = raw::Validate_Success;
			canFn.FreeData = raw::FreeData_Single;
			canFn.CopyData = raw::CopyData_Char;

			module->ModuleAddType(canFn);
			if (parser != nullptr) { parser->WordsAdd("CanCallFn"); }

		}

		void KillFunctionModule(IstackModuleExacuteor* exec)
		{
			std::map<std::thread::id, std::map<std::string, ist::IstackStackFrame>>::iterator it;
			std::map<std::string, ist::IstackStackFrame>::iterator its;

			for (it = raw::n_functionMap.begin(); it != raw::n_functionMap.end(); it++)
			{
				for (its = raw::n_functionMap[it->first].begin(); its != raw::n_functionMap[it->first].end(); its++)
				{
					exec->FreeFrameRecursive(&its->second);
				}
			}
		}

		bool CallFunctionInIstCode(std::string fnName, std::thread::id threadFunctionIsBindedTo, IstackUnit* argumentsArray, unsigned int arrayLength, IstackModuleExacuteor* exec)
		{
			IstackStackFrame codeFrameBeta = IstackStackFrame();
			IstackStackFrame dumpFrameBeta = IstackStackFrame();
			
			if (argumentsArray != nullptr)
			{
				for (unsigned int i = 0; i < arrayLength; i++)
				{
					dumpFrameBeta.UnitPush(argumentsArray[i]);
				}
			}

			exec->CopyIstackFrameAndModuleDataFromAndTo(&raw::n_functionMap[threadFunctionIsBindedTo][fnName], &codeFrameBeta);
			bool success = exec->ProcessExacuteFrame(&codeFrameBeta, &dumpFrameBeta);

			exec->FreeFrameRecursive(&dumpFrameBeta);
			exec->FreeFrameRecursive(&codeFrameBeta);
			return success;
		}
	}
}