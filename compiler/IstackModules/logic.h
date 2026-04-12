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

				bool A = (*(bool*)(dumpFrame->Top().m_data));
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();

				bool B = (*(bool*)(dumpFrame->Top().m_data));
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();


				delete (*data);

				(*data) = new bool;
				(*(bool*)(*data)) = (A || B);

				return true;
			}


			bool ValidateStack_StringEqualThan(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->Length() < 2) { return false; }

				std::string A = (*(std::string*)(dumpFrame->Top().m_data));
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();

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

				int A = (*(int*)(dumpFrame->Top().m_data));
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();

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

				int A = (*(int*)(dumpFrame->Top().m_data));
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();

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

				int A = (*(int*)(dumpFrame->Top().m_data));
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();

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

				float A = (*(float*)(dumpFrame->Top().m_data));
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();

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

				float A = (*(float*)(dumpFrame->Top().m_data));
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();

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

				float A = (*(float*)(dumpFrame->Top().m_data));
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();

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

			module->AddModule(ifMod);
			if (parser != nullptr) { parser->AddWords("If"); }


			ist::IstackModuleType notMod = ist::IstackModuleType();
			notMod.ValidateStack = raw::ValidateStack_Not;
			notMod.ValidateSelf = raw::ValidateSelf_Success;

			module->AddModule(notMod);
			if (parser != nullptr) { parser->AddWords("Not"); }


			ist::IstackModuleType orMod = ist::IstackModuleType();
			orMod.ValidateStack = raw::ValidateStack_Or;
			orMod.ValidateSelf = raw::ValidateSelf_Success;

			module->AddModule(orMod);
			if (parser != nullptr) { parser->AddWords("Or"); }

		}
	}
}