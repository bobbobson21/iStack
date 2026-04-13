#include <string>

#include "istack/istack.h"

#include "generics.h"

namespace ist
{
	namespace modules
	{
		namespace raw
		{
			bool ValidateStack_If(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if ((*dumpFrame->GetClearedPipe()) == nullptr) { return false; }
				if (dumpFrame->Length() < 1) { return false; }

				bool canRunIf = (*(bool*)(dumpFrame->Top().m_data));
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();

				if (canRunIf == true)
				{
					IstackStackFrame dumpFrameBeta = IstackStackFrame();

					bool success = exec->ExacuteFrame((*dumpFrame->GetClearedPipe()), &dumpFrameBeta);

					exec->FreeFrameRecursive(&dumpFrameBeta);
					exec->FreeFrameRecursive((*dumpFrame->GetClearedPipe()));

					(*dumpFrame->GetClearedPipe()) = nullptr;

					return success;
				}
	
				return true;
			}

			bool ValidateStack_Not(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->Length() < 1) { return false; }
				if (dumpFrame->Top().m_data == nullptr) { return false; }

				bool A = (*(bool*)(dumpFrame->Top().m_data));
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();


				delete (*data);

				(*data) = new bool;
				(*(bool*)(*data)) = (!A);

				return true;
			}

			bool ValidateStack_Or(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->Length() < 2) { return false; }
				if (dumpFrame->Top().m_data == nullptr) { return false; }

				bool A = (*(bool*)(dumpFrame->Top().m_data));
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();

				if (dumpFrame->Top().m_data == nullptr) { return false; }

				bool B = (*(bool*)(dumpFrame->Top().m_data));
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();


				delete (*data);

				(*data) = new bool;
				(*(bool*)(*data)) = (A || B);

				return true;
			}

			bool ValidateStack_And(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->Length() < 2) { return false; }
				if (dumpFrame->Top().m_data == nullptr) { return false; }

				bool A = (*(bool*)(dumpFrame->Top().m_data));
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();

				if (dumpFrame->Top().m_data == nullptr) { return false; }

				bool B = (*(bool*)(dumpFrame->Top().m_data));
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();


				delete (*data);

				(*data) = new bool;
				(*(bool*)(*data)) = (A && B);

				return true;
			}


			bool ValidateStack_StringEqualThan(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->Length() < 2) { return false; }
				if (dumpFrame->Top().m_data == nullptr) { return false; }

				std::string A = (*(std::string*)(dumpFrame->Top().m_data));
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();

				if (dumpFrame->Top().m_data == nullptr) { return false; }

				std::string B = (*(std::string*)(dumpFrame->Top().m_data));
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();

				delete (*data);

				(*data) = new bool;
				(*(bool*)(*data)) = (A == B);

				return true;
			}


			bool ValidateStack_IntEqualThan(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
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

				(*data) = new bool;
				(*(bool*)(*data)) = (A == B);

				return true;
			}

			bool ValidateStack_IntMoreThan(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
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

				(*data) = new bool;
				(*(bool*)(*data)) = (A > B);

				return true;
			}

			bool ValidateStack_IntLessThan(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
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

				(*data) = new bool;
				(*(bool*)(*data)) = (A < B);

				return true;
			}


			bool ValidateStack_FloatEqualThan(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->Length() < 2) { return false; }
				if (dumpFrame->Top().m_data == nullptr) { return false; }

				float A = (*(float*)(dumpFrame->Top().m_data));
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();

				if (dumpFrame->Top().m_data == nullptr) { return false; }

				float B = (*(float*)(dumpFrame->Top().m_data));
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();


				delete (*data);

				(*data) = new bool;
				(*(bool*)(*data)) = (A == B);

				return true;
			}

			bool ValidateStack_FloatMoreThan(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->Length() < 2) { return false; }
				if (dumpFrame->Top().m_data == nullptr) { return false; }

				float A = (*(float*)(dumpFrame->Top().m_data));
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();

				if (dumpFrame->Top().m_data == nullptr) { return false; }

				float B = (*(float*)(dumpFrame->Top().m_data));
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();


				delete (*data);

				(*data) = new bool;
				(*(bool*)(*data)) = (A > B);

				return true;
			}

			bool ValidateStack_FloatLessThan(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->Length() < 2) { return false; }
				if (dumpFrame->Top().m_data == nullptr) { return false; }

				float A = (*(float*)(dumpFrame->Top().m_data));
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();

				if (dumpFrame->Top().m_data == nullptr) { return false; }

				float B = (*(float*)(dumpFrame->Top().m_data));
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();


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

			module->AddModule(ifMod);
			if (parser != nullptr) { parser->AddWords("If"); }


			ist::IstackModuleType notMod = ist::IstackModuleType();
			notMod.ValidateStack = raw::ValidateStack_Not;
			notMod.ValidateSelf = raw::ValidateSelf_Success;
			notMod.FreeData = raw::FreeData_Single;
			//notMod.FreeData = raw::CopyData_Char; //not needed due to validate stack exacuting before any data can be read

			module->AddModule(notMod);
			if (parser != nullptr) { parser->AddWords("Not"); }


			ist::IstackModuleType orMod = ist::IstackModuleType();
			orMod.ValidateStack = raw::ValidateStack_Or;
			orMod.ValidateSelf = raw::ValidateSelf_Success;
			orMod.FreeData = raw::FreeData_Single;

			module->AddModule(orMod);
			if (parser != nullptr) { parser->AddWords("Or"); }


			ist::IstackModuleType andMod = ist::IstackModuleType();
			andMod.ValidateStack = raw::ValidateStack_And;
			andMod.ValidateSelf = raw::ValidateSelf_Success;
			andMod.FreeData = raw::FreeData_Single;

			module->AddModule(andMod);
			if (parser != nullptr) { parser->AddWords("And"); }


			ist::IstackModuleType set = ist::IstackModuleType();
			set.ValidateStack = raw::ValidateStack_StringEqualThan;
			set.ValidateSelf = raw::ValidateSelf_Success;

			module->AddModule(set);
			if (parser != nullptr) { parser->AddWords("str=="); }


			ist::IstackModuleType iet = ist::IstackModuleType();
			iet.ValidateStack = raw::ValidateStack_IntEqualThan;
			iet.ValidateSelf = raw::ValidateSelf_Success;

			module->AddModule(iet);
			if (parser != nullptr) { parser->AddWords("i=="); }


			ist::IstackModuleType imt = ist::IstackModuleType();
			imt.ValidateStack = raw::ValidateStack_IntMoreThan;
			imt.ValidateSelf = raw::ValidateSelf_Success;

			module->AddModule(imt);
			if (parser != nullptr) { parser->AddWords("i>"); }


			ist::IstackModuleType ilt = ist::IstackModuleType();
			ilt.ValidateStack = raw::ValidateStack_IntLessThan;
			ilt.ValidateSelf = raw::ValidateSelf_Success;

			module->AddModule(ilt);
			if (parser != nullptr) { parser->AddWords("i<"); }


			ist::IstackModuleType fet = ist::IstackModuleType();
			fet.ValidateStack = raw::ValidateStack_FloatEqualThan;
			fet.ValidateSelf = raw::ValidateSelf_Success;

			module->AddModule(fet);
			if (parser != nullptr) { parser->AddWords("f=="); }


			ist::IstackModuleType fmt = ist::IstackModuleType();
			fmt.ValidateStack = raw::ValidateStack_FloatMoreThan;
			fmt.ValidateSelf = raw::ValidateSelf_Success;

			module->AddModule(fmt);
			if (parser != nullptr) { parser->AddWords("f>"); }


			ist::IstackModuleType flt = ist::IstackModuleType();
			flt.ValidateStack = raw::ValidateStack_FloatLessThan;
			flt.ValidateSelf = raw::ValidateSelf_Success;

			module->AddModule(flt);
			if (parser != nullptr) { parser->AddWords("f<"); }

		}
	}
}