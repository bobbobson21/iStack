#pragma once

#include <string>

#include "istack/istack.h"

#include "generics.h"

namespace ist
{
	namespace modules
	{
		namespace raw
		{
			bool ValidateStack_IntAdd(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->Length() < 2) { return false; }
				if (dumpFrame->Top().m_data == nullptr) { return false; }

				int A = (*(int*)(dumpFrame->Top().m_data));
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();

				if (dumpFrame->Top().m_data == nullptr) { return false; }

				int B = (*(int*)(dumpFrame->Top().m_data));
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();


				delete (*data);

				(*data) = new int;
				(*(int*)(*data)) = (A + B);

				return true;
			}

			bool ValidateStack_IntTake(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->Length() < 2) { return false; }
				if (dumpFrame->Top().m_data == nullptr) { return false; }

				int A = (*(int*)(dumpFrame->Top().m_data));
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();

				if (dumpFrame->Top().m_data == nullptr) { return false; }

				int B = (*(int*)(dumpFrame->Top().m_data));
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();


				delete (*data);

				(*data) = new int;
				(*(int*)(*data)) = (A - B);

				return true;
			}

			bool ValidateStack_IntTimes(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->Length() < 2) { return false; }
				if (dumpFrame->Top().m_data == nullptr) { return false; }

				int A = (*(int*)(dumpFrame->Top().m_data));
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();

				if (dumpFrame->Top().m_data == nullptr) { return false; }

				int B = (*(int*)(dumpFrame->Top().m_data));
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();


				delete (*data);

				(*data) = new int;
				(*(int*)(*data)) = (A * B);

				return true;
			}

			bool ValidateStack_IntDivide(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->Length() < 2) { return false; }
				if (dumpFrame->Top().m_data == nullptr) { return false; }

				int A = (*(int*)(dumpFrame->Top().m_data));
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();

				if (dumpFrame->Top().m_data == nullptr) { return false; }

				int B = (*(int*)(dumpFrame->Top().m_data));
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();


				delete (*data);

				(*data) = new int;
				(*(int*)(*data)) = (A / B);

				return true;
			}

			bool ValidateStack_IntMod(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->Length() < 2) { return false; }
				if (dumpFrame->Top().m_data == nullptr) { return false; }

				int A = (*(int*)(dumpFrame->Top().m_data));
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();

				if (dumpFrame->Top().m_data == nullptr) { return false; }

				int B = (*(int*)(dumpFrame->Top().m_data));
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();


				delete (*data);

				(*data) = new int;
				(*(int*)(*data)) = (A % B);

				return true;
			}

			bool ValidateStack_IntPow(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->Length() < 2) { return false; }
				if (dumpFrame->Top().m_data == nullptr) { return false; }

				int A = (*(int*)(dumpFrame->Top().m_data));
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();

				if (dumpFrame->Top().m_data == nullptr) { return false; }

				int B = (*(int*)(dumpFrame->Top().m_data));
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();


				delete (*data);

				(*data) = new int;
				(*(int*)(*data)) = (A ^ B);

				return true;
			}


			bool ValidateStack_FloatAdd(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->Length() < 2) { return false; }
				if (dumpFrame->Top().m_data == nullptr) { return false; }

				int A = (*(int*)(dumpFrame->Top().m_data));
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();

				if (dumpFrame->Top().m_data == nullptr) { return false; }

				int B = (*(int*)(dumpFrame->Top().m_data));
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();


				delete (*data);

				(*data) = new int;
				(*(int*)(*data)) = (A + B);

				return true;
			}

			bool ValidateStack_FloatTake(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->Length() < 2) { return false; }
				if (dumpFrame->Top().m_data == nullptr) { return false; }

				int A = (*(int*)(dumpFrame->Top().m_data));
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();

				if (dumpFrame->Top().m_data == nullptr) { return false; }

				int B = (*(int*)(dumpFrame->Top().m_data));
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();


				delete (*data);

				(*data) = new int;
				(*(int*)(*data)) = (A - B);

				return true;
			}

			bool ValidateStack_FloatTimes(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->Length() < 2) { return false; }
				if (dumpFrame->Top().m_data == nullptr) { return false; }

				int A = (*(int*)(dumpFrame->Top().m_data));
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();

				if (dumpFrame->Top().m_data == nullptr) { return false; }

				int B = (*(int*)(dumpFrame->Top().m_data));
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();


				delete (*data);

				(*data) = new int;
				(*(int*)(*data)) = (A * B);

				return true;
			}

			bool ValidateStack_FloatDivide(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->Length() < 2) { return false; }
				if (dumpFrame->Top().m_data == nullptr) { return false; }

				int A = (*(int*)(dumpFrame->Top().m_data));
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();

				if (dumpFrame->Top().m_data == nullptr) { return false; }

				int B = (*(int*)(dumpFrame->Top().m_data));
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();


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

			module->AddModule(AddF);
			if (parser != nullptr) { parser->AddWords("f+"); }


			ist::IstackModuleType TakeF = ist::IstackModuleType();
			TakeF.ValidateStack = raw::ValidateStack_FloatTake;
			TakeF.ValidateSelf = raw::ValidateSelf_Success;
			TakeF.FreeData = raw::FreeData_Single;
			//notMod.FreeData = raw::CopyData_Char; //not needed due to validate stack exacuting before any data can be read

			module->AddModule(TakeF);
			if (parser != nullptr) { parser->AddWords("f-"); }


			ist::IstackModuleType TimesF = ist::IstackModuleType();
			TimesF.ValidateStack = raw::ValidateStack_FloatTimes;
			TimesF.ValidateSelf = raw::ValidateSelf_Success;
			TimesF.FreeData = raw::FreeData_Single;
			//notMod.FreeData = raw::CopyData_Char; //not needed due to validate stack exacuting before any data can be read

			module->AddModule(TimesF);
			if (parser != nullptr) { parser->AddWords("f*"); }


			ist::IstackModuleType DivideF = ist::IstackModuleType();
			DivideF.ValidateStack = raw::ValidateStack_FloatDivide;
			DivideF.ValidateSelf = raw::ValidateSelf_Success;
			DivideF.FreeData = raw::FreeData_Single;
			//notMod.FreeData = raw::CopyData_Char; //not needed due to validate stack exacuting before any data can be read

			module->AddModule(DivideF);
			if (parser != nullptr) { parser->AddWords("f/"); }


			ist::IstackModuleType AddI = ist::IstackModuleType();
			AddI.ValidateStack = raw::ValidateStack_IntAdd;
			AddI.ValidateSelf = raw::ValidateSelf_Success;
			AddI.FreeData = raw::FreeData_Single;
			//notMod.FreeData = raw::CopyData_Char; //not needed due to validate stack exacuting before any data can be read

			module->AddModule(AddI);
			if (parser != nullptr) { parser->AddWords("i+"); }


			ist::IstackModuleType TakeI = ist::IstackModuleType();
			TakeI.ValidateStack = raw::ValidateStack_IntTake;
			TakeI.ValidateSelf = raw::ValidateSelf_Success;
			TakeI.FreeData = raw::FreeData_Single;
			//notMod.FreeData = raw::CopyData_Char; //not needed due to validate stack exacuting before any data can be read

			module->AddModule(TakeI);
			if (parser != nullptr) { parser->AddWords("i-"); }


			ist::IstackModuleType TimesI = ist::IstackModuleType();
			TimesI.ValidateStack = raw::ValidateStack_IntTimes;
			TimesI.ValidateSelf = raw::ValidateSelf_Success;
			TimesI.FreeData = raw::FreeData_Single;
			//notMod.FreeData = raw::CopyData_Char; //not needed due to validate stack exacuting before any data can be read

			module->AddModule(TimesI);
			if (parser != nullptr) { parser->AddWords("i*"); }


			ist::IstackModuleType DivideI = ist::IstackModuleType();
			DivideI.ValidateStack = raw::ValidateStack_IntDivide;
			DivideI.ValidateSelf = raw::ValidateSelf_Success;
			DivideI.FreeData = raw::FreeData_Single;
			//notMod.FreeData = raw::CopyData_Char; //not needed due to validate stack exacuting before any data can be read

			module->AddModule(DivideI);
			if (parser != nullptr) { parser->AddWords("i/"); }


			ist::IstackModuleType ModI = ist::IstackModuleType();
			ModI.ValidateStack = raw::ValidateStack_IntMod;
			ModI.ValidateSelf = raw::ValidateSelf_Success;
			ModI.FreeData = raw::FreeData_Single;
			//notMod.FreeData = raw::CopyData_Char; //not needed due to validate stack exacuting before any data can be read

			module->AddModule(ModI);
			if (parser != nullptr) { parser->AddWords("i%"); }


			ist::IstackModuleType PowI = ist::IstackModuleType();
			PowI.ValidateStack = raw::ValidateStack_IntPow;
			PowI.ValidateSelf = raw::ValidateSelf_Success;
			PowI.FreeData = raw::FreeData_Single;
			//notMod.FreeData = raw::CopyData_Char; //not needed due to validate stack exacuting before any data can be read

			module->AddModule(PowI);
			if (parser != nullptr) { parser->AddWords("i^"); }
		}
	}
}