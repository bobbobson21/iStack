#include <string>

#include "istack/istack.h"

#include "generics.h"

namespace ist
{
	namespace modules
	{
		enum moduleLogicErrorCodes : unsigned int
		{
			PipeCantBeFoundLogic = 501,
			StackEmptyIfLogic = 502,
			DataIsNullIfLogic = 503,

			StackElementSizeNotMetLogic = 502,
			StackElementFirstInvalidLogic = 503,
			StackElementSecondInvalidLogic = 504,
		};

		namespace raw
		{
			bool ValidateStack_If(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if ((*dumpFrame->PipeGetCleared()) == nullptr) { exec->ErrorSetCode(PipeCantBeFoundLogic); return false; }
				if (dumpFrame->UnitLength() < 1) { exec->ErrorSetCode(StackEmptyIfLogic); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(DataIsNullIfLogic); return false; }

				bool canRunIf = (*(bool*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();

				if (canRunIf == true)
				{
					IstackStackFrame dumpFrameBeta = IstackStackFrame();

					bool success = exec->ProcessExacuteFrame((*dumpFrame->PipeGetCleared()), &dumpFrameBeta);

					exec->FreeFrameRecursive(&dumpFrameBeta); //there is no way to acesss the dump frames cotents for an if
					exec->FreeFrameRecursive((*dumpFrame->PipeGetCleared()));

					(*dumpFrame->PipeGetCleared()) = nullptr;

					return success;
				}
	
				return true;
			}

			bool ValidateStack_Not(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 1) { exec->ErrorSetCode(StackElementSizeNotMetLogic); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StackElementFirstInvalidLogic); return false; }

				bool A = (*(bool*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();


				delete (*data);

				(*data) = new bool;
				(*(bool*)(*data)) = (!A);

				return true;
			}

			bool ValidateStack_Or(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 2) { exec->ErrorSetCode(StackElementSizeNotMetLogic); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StackElementFirstInvalidLogic); return false; }

				bool A = (*(bool*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();

				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StackElementSecondInvalidLogic); return false; }

				bool B = (*(bool*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();


				delete (*data);

				(*data) = new bool;
				(*(bool*)(*data)) = (A || B);

				return true;
			}

			bool ValidateStack_And(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 2) { exec->ErrorSetCode(StackElementSizeNotMetLogic); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StackElementFirstInvalidLogic); return false; }

				bool A = (*(bool*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();

				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StackElementSecondInvalidLogic); return false; }

				bool B = (*(bool*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();


				delete (*data);

				(*data) = new bool;
				(*(bool*)(*data)) = (A && B);

				return true;
			}


			bool ValidateStack_StringEqualThan(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 2) { exec->ErrorSetCode(StackElementSizeNotMetLogic); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StackElementFirstInvalidLogic); return false; }

				std::string A = (*(std::string*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();

				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StackElementSecondInvalidLogic); return false; }

				std::string B = (*(std::string*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();

				delete (*data);

				(*data) = new bool;
				(*(bool*)(*data)) = (A == B);

				return true;
			}


			bool ValidateStack_IntEqualThan(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 2) { exec->ErrorSetCode(StackElementSizeNotMetLogic); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StackElementFirstInvalidLogic); return false; }

				int A = (*(int*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();

				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StackElementSecondInvalidLogic); return false; }

				int B = (*(int*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();


				delete (*data);

				(*data) = new bool;
				(*(bool*)(*data)) = (A == B);

				return true;
			}

			bool ValidateStack_IntMoreThan(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 2) { exec->ErrorSetCode(StackElementSizeNotMetLogic); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StackElementFirstInvalidLogic); return false; }

				int A = (*(int*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();

				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StackElementSecondInvalidLogic); return false; }

				int B = (*(int*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();


				delete (*data);

				(*data) = new bool;
				(*(bool*)(*data)) = (A > B);

				return true;
			}

			bool ValidateStack_IntLessThan(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 2) { exec->ErrorSetCode(StackElementSizeNotMetLogic); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StackElementFirstInvalidLogic); return false; }

				int A = (*(int*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();

				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StackElementSecondInvalidLogic); return false; }

				int B = (*(int*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();


				delete (*data);

				(*data) = new bool;
				(*(bool*)(*data)) = (A < B);

				return true;
			}


			bool ValidateStack_FloatEqualThan(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 2) { exec->ErrorSetCode(StackElementSizeNotMetLogic); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StackElementFirstInvalidLogic); return false; }

				float A = (*(float*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();

				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StackElementSecondInvalidLogic); return false; }

				float B = (*(float*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();


				delete (*data);

				(*data) = new bool;
				(*(bool*)(*data)) = (A == B);

				return true;
			}

			bool ValidateStack_FloatMoreThan(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 2) { exec->ErrorSetCode(StackElementSizeNotMetLogic); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StackElementFirstInvalidLogic); return false; }

				float A = (*(float*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();

				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StackElementSecondInvalidLogic); return false; }

				float B = (*(float*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();


				delete (*data);

				(*data) = new bool;
				(*(bool*)(*data)) = (A > B);

				return true;
			}

			bool ValidateStack_FloatLessThan(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 2) { exec->ErrorSetCode(StackElementSizeNotMetLogic); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StackElementFirstInvalidLogic); return false; }

				float A = (*(float*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();

				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StackElementSecondInvalidLogic); return false; }

				float B = (*(float*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();


				delete (*data);

				(*data) = new bool;
				(*(bool*)(*data)) = (A < B);

				return true;
			}
		}

		void LoadLogicModules(IstackModuleExacuteor* module, IstackLexParser* parser)
		{
			ist::IstackModuleType ifMod = ist::IstackModuleType();
			ifMod.ValidateStack = raw::ValidateStack_If;
			ifMod.ValidateSelf = raw::Validate_Fail;
			//ifMod.FreeData = raw::FreeData_Single; //not needed as the if module can not contain data

			module->ModuleAddType(ifMod);
			if (parser != nullptr) { parser->WordsAdd("If"); }


			ist::IstackModuleType notMod = ist::IstackModuleType();
			notMod.ValidateStack = raw::ValidateStack_Not;
			notMod.ValidateSelf = raw::Validate_Success;
			notMod.FreeData = raw::FreeData_Single;
			notMod.CopyData = raw::CopyData_Char;

			module->ModuleAddType(notMod);
			if (parser != nullptr) { parser->WordsAdd("Not"); }


			ist::IstackModuleType orMod = ist::IstackModuleType();
			orMod.ValidateStack = raw::ValidateStack_Or;
			orMod.ValidateSelf = raw::Validate_Success;
			orMod.FreeData = raw::FreeData_Single;
			orMod.CopyData = raw::CopyData_Char;

			module->ModuleAddType(orMod);
			if (parser != nullptr) { parser->WordsAdd("Or"); }


			ist::IstackModuleType andMod = ist::IstackModuleType();
			andMod.ValidateStack = raw::ValidateStack_And;
			andMod.ValidateSelf = raw::Validate_Success;
			andMod.FreeData = raw::FreeData_Single;
			andMod.CopyData = raw::CopyData_Char;

			module->ModuleAddType(andMod);
			if (parser != nullptr) { parser->WordsAdd("And"); }


			ist::IstackModuleType set = ist::IstackModuleType();
			set.ValidateStack = raw::ValidateStack_StringEqualThan;
			set.ValidateSelf = raw::Validate_Success;
			set.FreeData = raw::FreeData_Single;
			set.CopyData = raw::CopyData_Char;

			module->ModuleAddType(set);
			if (parser != nullptr) { parser->WordsAdd("str=="); }


			ist::IstackModuleType iet = ist::IstackModuleType();
			iet.ValidateStack = raw::ValidateStack_IntEqualThan;
			iet.ValidateSelf = raw::Validate_Success;
			iet.FreeData = raw::FreeData_Single;
			iet.CopyData = raw::CopyData_CopyFail;

			module->ModuleAddType(iet);
			if (parser != nullptr) { parser->WordsAdd("i=="); }


			ist::IstackModuleType imt = ist::IstackModuleType();
			imt.ValidateStack = raw::ValidateStack_IntMoreThan;
			imt.ValidateSelf = raw::Validate_Success;
			imt.FreeData = raw::FreeData_Single;
			imt.CopyData = raw::CopyData_Char;

			module->ModuleAddType(imt);
			if (parser != nullptr) { parser->WordsAdd("i>"); }


			ist::IstackModuleType ilt = ist::IstackModuleType();
			ilt.ValidateStack = raw::ValidateStack_IntLessThan;
			ilt.ValidateSelf = raw::Validate_Success;
			ilt.FreeData = raw::FreeData_Single;
			ilt.CopyData = raw::CopyData_Char;

			module->ModuleAddType(ilt);
			if (parser != nullptr) { parser->WordsAdd("i<"); }


			ist::IstackModuleType fet = ist::IstackModuleType();
			fet.ValidateStack = raw::ValidateStack_FloatEqualThan;
			fet.ValidateSelf = raw::Validate_Success;
			fet.FreeData = raw::FreeData_Single;
			fet.CopyData = raw::CopyData_Char;

			module->ModuleAddType(fet);
			if (parser != nullptr) { parser->WordsAdd("f=="); }


			ist::IstackModuleType fmt = ist::IstackModuleType();
			fmt.ValidateStack = raw::ValidateStack_FloatMoreThan;
			fmt.ValidateSelf = raw::Validate_Success;
			fmt.FreeData = raw::FreeData_Single;
			fmt.CopyData = raw::CopyData_Char;

			module->ModuleAddType(fmt);
			if (parser != nullptr) { parser->WordsAdd("f>"); }


			ist::IstackModuleType flt = ist::IstackModuleType();
			flt.ValidateStack = raw::ValidateStack_FloatLessThan;
			flt.ValidateSelf = raw::Validate_Success;
			flt.FreeData = raw::FreeData_Single;
			flt.CopyData = raw::CopyData_Char;

			module->ModuleAddType(flt);
			if (parser != nullptr) { parser->WordsAdd("f<"); }

		}
	}
}