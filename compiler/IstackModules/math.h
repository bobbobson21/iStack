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

				int A = (*(int*)(dumpFrame->Top().m_data));
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();

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

				int A = (*(int*)(dumpFrame->Top().m_data));
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();

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

				int A = (*(int*)(dumpFrame->Top().m_data));
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();

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

				int A = (*(int*)(dumpFrame->Top().m_data));
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();

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

				int A = (*(int*)(dumpFrame->Top().m_data));
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();

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

				int A = (*(int*)(dumpFrame->Top().m_data));
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();

				int B = (*(int*)(dumpFrame->Top().m_data));
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();


				delete (*data);

				(*data) = new int;
				(*(int*)(*data)) = (A ^ B);

				return true;
			}


		}

		void LoadMathModules(IstackModuleExacuteor* module, IstackLexParser* parser)
		{
		}
	}
}