#pragma once

#include <string>

#include "generics.h"

namespace ist
{
	namespace modules
	{
		enum moduleMathErrorCodes : unsigned int
		{
			StackElementSizeNotMetMath = 601,
			StackElementFirstInvalidMath = 602,
			StackElementSecondInvalidMath = 603,
		};

		namespace raw
		{
			bool ValidateStack_IntAdd(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 2) { exec->ErrorSetCode(StackElementSizeNotMetMath); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StackElementFirstInvalidMath); return false; }

				int A = (*(int*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();

				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StackElementSecondInvalidMath); return false; }

				int B = (*(int*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();


				delete (*data);

				(*data) = new int;
				(*(int*)(*data)) = (A + B);

				return true;
			}

			bool ValidateStack_IntTake(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 2) { exec->ErrorSetCode(StackElementSizeNotMetMath); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StackElementFirstInvalidMath); return false; }

				int A = (*(int*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();

				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StackElementSecondInvalidMath); return false; }

				int B = (*(int*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();


				delete (*data);

				(*data) = new int;
				(*(int*)(*data)) = (A - B);

				return true;
			}

			bool ValidateStack_IntTimes(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 2) { exec->ErrorSetCode(StackElementSizeNotMetMath); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StackElementFirstInvalidMath); return false; }

				int A = (*(int*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();

				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StackElementSecondInvalidMath); return false; }

				int B = (*(int*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();


				delete (*data);

				(*data) = new int;
				(*(int*)(*data)) = (A * B);

				return true;
			}

			bool ValidateStack_IntDivide(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 2) { exec->ErrorSetCode(StackElementSizeNotMetMath); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StackElementFirstInvalidMath); return false; }

				int A = (*(int*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();

				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StackElementSecondInvalidMath); return false; }

				int B = (*(int*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();


				delete (*data);

				(*data) = new int;
				(*(int*)(*data)) = (A / B);

				return true;
			}

			bool ValidateStack_IntMod(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 2) { exec->ErrorSetCode(StackElementSizeNotMetMath); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StackElementFirstInvalidMath); return false; }

				int A = (*(int*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();

				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StackElementSecondInvalidMath); return false; }

				int B = (*(int*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();


				delete (*data);

				(*data) = new int;
				(*(int*)(*data)) = (A % B);

				return true;
			}

			bool ValidateStack_IntPow(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 2) { exec->ErrorSetCode(StackElementSizeNotMetMath); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StackElementFirstInvalidMath); return false; }

				int A = (*(int*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();

				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StackElementSecondInvalidMath); return false; }

				int B = (*(int*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();


				delete (*data);

				(*data) = new int;
				(*(int*)(*data)) = (A ^ B);

				return true;
			}


			bool ValidateStack_FloatAdd(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 2) { exec->ErrorSetCode(StackElementSizeNotMetMath); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StackElementFirstInvalidLogic); return false; }

				int A = (*(int*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();

				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StackElementSecondInvalidMath); return false; }

				int B = (*(int*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();


				delete (*data);

				(*data) = new int;
				(*(int*)(*data)) = (A + B);

				return true;
			}

			bool ValidateStack_FloatTake(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 2) { exec->ErrorSetCode(StackElementSizeNotMetMath); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StackElementFirstInvalidMath); return false; }

				int A = (*(int*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();

				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StackElementSecondInvalidMath); return false; }

				int B = (*(int*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();


				delete (*data);

				(*data) = new int;
				(*(int*)(*data)) = (A - B);

				return true;
			}

			bool ValidateStack_FloatTimes(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 2) { exec->ErrorSetCode(StackElementSizeNotMetMath); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StackElementFirstInvalidMath); return false; }

				int A = (*(int*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();

				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StackElementSecondInvalidMath); return false; }

				int B = (*(int*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();


				delete (*data);

				(*data) = new int;
				(*(int*)(*data)) = (A * B);

				return true;
			}

			bool ValidateStack_FloatDivide(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 2) { exec->ErrorSetCode(StackElementSizeNotMetMath); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StackElementFirstInvalidMath); return false; }

				int A = (*(int*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();

				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StackElementSecondInvalidMath); return false; }

				int B = (*(int*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();


				delete (*data);

				(*data) = new int;
				(*(int*)(*data)) = (A / B);

				return true;
			}
		}

		void LoadMathModules(IstackModuleExacuteor* module, IstackLexParser* parser)
		{
			ist::IstackModuleType AddF = ist::IstackModuleType();
			AddF.ValidateStack = raw::ValidateStack_FloatAdd;
			AddF.ValidateSelf = raw::ValidateSelf_Success;
			AddF.FreeData = raw::FreeData_Single;
			//notMod.FreeData = raw::CopyData_Char; //not needed due to validate stack exacuting before any data can be read

			module->ModuleAddType(AddF);
			if (parser != nullptr) { parser->AddWord("f+"); }


			ist::IstackModuleType TakeF = ist::IstackModuleType();
			TakeF.ValidateStack = raw::ValidateStack_FloatTake;
			TakeF.ValidateSelf = raw::ValidateSelf_Success;
			TakeF.FreeData = raw::FreeData_Single;
			//notMod.FreeData = raw::CopyData_Char; //not needed due to validate stack exacuting before any data can be read

			module->ModuleAddType(TakeF);
			if (parser != nullptr) { parser->AddWord("f-"); }


			ist::IstackModuleType TimesF = ist::IstackModuleType();
			TimesF.ValidateStack = raw::ValidateStack_FloatTimes;
			TimesF.ValidateSelf = raw::ValidateSelf_Success;
			TimesF.FreeData = raw::FreeData_Single;
			//notMod.FreeData = raw::CopyData_Char; //not needed due to validate stack exacuting before any data can be read

			module->ModuleAddType(TimesF);
			if (parser != nullptr) { parser->AddWord("f*"); }


			ist::IstackModuleType DivideF = ist::IstackModuleType();
			DivideF.ValidateStack = raw::ValidateStack_FloatDivide;
			DivideF.ValidateSelf = raw::ValidateSelf_Success;
			DivideF.FreeData = raw::FreeData_Single;
			//notMod.FreeData = raw::CopyData_Char; //not needed due to validate stack exacuting before any data can be read

			module->ModuleAddType(DivideF);
			if (parser != nullptr) { parser->AddWord("f/"); }


			ist::IstackModuleType AddI = ist::IstackModuleType();
			AddI.ValidateStack = raw::ValidateStack_IntAdd;
			AddI.ValidateSelf = raw::ValidateSelf_Success;
			AddI.FreeData = raw::FreeData_Single;
			//notMod.FreeData = raw::CopyData_Char; //not needed due to validate stack exacuting before any data can be read

			module->ModuleAddType(AddI);
			if (parser != nullptr) { parser->AddWord("i+"); }


			ist::IstackModuleType TakeI = ist::IstackModuleType();
			TakeI.ValidateStack = raw::ValidateStack_IntTake;
			TakeI.ValidateSelf = raw::ValidateSelf_Success;
			TakeI.FreeData = raw::FreeData_Single;
			//notMod.FreeData = raw::CopyData_Char; //not needed due to validate stack exacuting before any data can be read

			module->ModuleAddType(TakeI);
			if (parser != nullptr) { parser->AddWord("i-"); }


			ist::IstackModuleType TimesI = ist::IstackModuleType();
			TimesI.ValidateStack = raw::ValidateStack_IntTimes;
			TimesI.ValidateSelf = raw::ValidateSelf_Success;
			TimesI.FreeData = raw::FreeData_Single;
			//notMod.FreeData = raw::CopyData_Char; //not needed due to validate stack exacuting before any data can be read

			module->ModuleAddType(TimesI);
			if (parser != nullptr) { parser->AddWord("i*"); }


			ist::IstackModuleType DivideI = ist::IstackModuleType();
			DivideI.ValidateStack = raw::ValidateStack_IntDivide;
			DivideI.ValidateSelf = raw::ValidateSelf_Success;
			DivideI.FreeData = raw::FreeData_Single;
			//notMod.FreeData = raw::CopyData_Char; //not needed due to validate stack exacuting before any data can be read

			module->ModuleAddType(DivideI);
			if (parser != nullptr) { parser->AddWord("i/"); }


			ist::IstackModuleType ModI = ist::IstackModuleType();
			ModI.ValidateStack = raw::ValidateStack_IntMod;
			ModI.ValidateSelf = raw::ValidateSelf_Success;
			ModI.FreeData = raw::FreeData_Single;
			//notMod.FreeData = raw::CopyData_Char; //not needed due to validate stack exacuting before any data can be read

			module->ModuleAddType(ModI);
			if (parser != nullptr) { parser->AddWord("i%"); }


			ist::IstackModuleType PowI = ist::IstackModuleType();
			PowI.ValidateStack = raw::ValidateStack_IntPow;
			PowI.ValidateSelf = raw::ValidateSelf_Success;
			PowI.FreeData = raw::FreeData_Single;
			//notMod.FreeData = raw::CopyData_Char; //not needed due to validate stack exacuting before any data can be read

			module->ModuleAddType(PowI);
			if (parser != nullptr) { parser->AddWord("i^"); }
		}
	}
}