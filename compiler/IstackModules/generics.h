#pragma once

#include <string>

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

			void FreeData_String(void** data)
			{
				delete (std::string*)(*data);
			}

			void FreeData_Fail(void** data)
			{

			}


			void CopyData_Char(void** copyFrom, void** copyTo)
			{
				delete (*copyTo);
				char* buffer = new char;

				memcpy(buffer, (*copyFrom), sizeof(char) * 1);
				(*copyTo) = buffer;
			}

			void CopyData_FourChar(void** copyFrom, void** copyTo)
			{
				delete (*copyTo);
				char* buffer = new char[4];

				memcpy(buffer, (*copyFrom), sizeof(char) * 4);
				(*copyTo) = buffer;
			}

			void CopyData_CopyFail(void** copyFrom, void** copyTo)
			{

			}


			//void FreeData_Array(void** data)
			//{
			//	delete[](*data);
			//}
		}
	}
}