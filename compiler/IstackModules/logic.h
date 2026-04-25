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
			ifMod.ValidateSelf = raw::ValidateSelf_Fail;
			//ifMod.FreeData = raw::FreeData_Single; //not needed as the if module can not contain data

			module->ModuleAddType(ifMod);
			if (parser != nullptr) { parser->AddWord("If"); }


			ist::IstackModuleType notMod = ist::IstackModuleType();
			notMod.ValidateStack = raw::ValidateStack_Not;
			notMod.ValidateSelf = raw::ValidateSelf_Success;
			notMod.FreeData = raw::FreeData_Single;
			//notMod.FreeData = raw::CopyData_Char; //not needed due to validate stack exacuting before any data can be read

			module->ModuleAddType(notMod);
			if (parser != nullptr) { parser->AddWord("Not"); }


			ist::IstackModuleType orMod = ist::IstackModuleType();
			orMod.ValidateStack = raw::ValidateStack_Or;
			orMod.ValidateSelf = raw::ValidateSelf_Success;
			orMod.FreeData = raw::FreeData_Single;

			module->ModuleAddType(orMod);
			if (parser != nullptr) { parser->AddWord("Or"); }


			ist::IstackModuleType andMod = ist::IstackModuleType();
			andMod.ValidateStack = raw::ValidateStack_And;
			andMod.ValidateSelf = raw::ValidateSelf_Success;
			andMod.FreeData = raw::FreeData_Single;

			module->ModuleAddType(andMod);
			if (parser != nullptr) { parser->AddWord("And"); }


			ist::IstackModuleType set = ist::IstackModuleType();
			set.ValidateStack = raw::ValidateStack_StringEqualThan;
			set.ValidateSelf = raw::ValidateSelf_Success;
			set.FreeData = raw::FreeData_Single;

			module->ModuleAddType(set);
			if (parser != nullptr) { parser->AddWord("str=="); }


			ist::IstackModuleType iet = ist::IstackModuleType();
			iet.ValidateStack = raw::ValidateStack_IntEqualThan;
			iet.ValidateSelf = raw::ValidateSelf_Success;
			iet.FreeData = raw::FreeData_Single;

			module->ModuleAddType(iet);
			if (parser != nullptr) { parser->AddWord("i=="); }


			ist::IstackModuleType imt = ist::IstackModuleType();
			imt.ValidateStack = raw::ValidateStack_IntMoreThan;
			imt.ValidateSelf = raw::ValidateSelf_Success;
			imt.FreeData = raw::FreeData_Single;

			module->ModuleAddType(imt);
			if (parser != nullptr) { parser->AddWord("i>"); }


			ist::IstackModuleType ilt = ist::IstackModuleType();
			ilt.ValidateStack = raw::ValidateStack_IntLessThan;
			ilt.ValidateSelf = raw::ValidateSelf_Success;
			ilt.FreeData = raw::FreeData_Single;

			module->ModuleAddType(ilt);
			if (parser != nullptr) { parser->AddWord("i<"); }


			ist::IstackModuleType fet = ist::IstackModuleType();
			fet.ValidateStack = raw::ValidateStack_FloatEqualThan;
			fet.ValidateSelf = raw::ValidateSelf_Success;
			fet.FreeData = raw::FreeData_Single;

			module->ModuleAddType(fet);
			if (parser != nullptr) { parser->AddWord("f=="); }


			ist::IstackModuleType fmt = ist::IstackModuleType();
			fmt.ValidateStack = raw::ValidateStack_FloatMoreThan;
			fmt.ValidateSelf = raw::ValidateSelf_Success;
			fmt.FreeData = raw::FreeData_Single;

			module->ModuleAddType(fmt);
			if (parser != nullptr) { parser->AddWord("f>"); }


			ist::IstackModuleType flt = ist::IstackModuleType();
			flt.ValidateStack = raw::ValidateStack_FloatLessThan;
			flt.ValidateSelf = raw::ValidateSelf_Success;
			flt.FreeData = raw::FreeData_Single;

			module->ModuleAddType(flt);
			if (parser != nullptr) { parser->AddWord("f<"); }

		}
	}
}