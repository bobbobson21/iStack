#pragma once

#include "istack/istack.h"

namespace ist
{
	namespace modules
	{
		namespace raw
		{
			bool ValidateSelf_Fail(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				return false;
			}

			bool ValidateSelf_Success(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				return true;
			}

			void FreeData_Single(void** data)
			{
				delete (*data);
			}

			void CopyData_Char(void** copyFrom, void** copyTo)
			{
				delete (*copyTo);
				memcpy((*copyFrom), (*copyTo), 1);
			}

			void CopyData_TwoChar(void** copyFrom, void** copyTo)
			{
				delete (*copyTo);
				memcpy((*copyFrom), (*copyTo), 2);
			}

			void CopyData_ThreeChar(void** copyFrom, void** copyTo)
			{
				delete (*copyTo);
				memcpy((*copyFrom), (*copyTo), 3);
			}

			void CopyData_FourChar(void** copyFrom, void** copyTo)
			{
				delete (*copyTo);
				memcpy((*copyFrom), (*copyTo), 4);
			}

			//void FreeData_Array(void** data)
			//{
			//	delete[](*data);
			//}
		}
	}
}