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
			static unsigned int m_varLibLocationForConversionLib = 0;

			bool ValidateStack_IntToFloat(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->Length() < 1) { return false; }
				if (dumpFrame->Top().m_data == nullptr) { return false; }

				int typeToConvertFrom = (*(int*)(dumpFrame->Top().m_data));
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();

				ist::IstackUnit typeToConvertTo = ist::IstackUnit();
				typeToConvertTo.m_modualTypeCode = 1 + m_varLibLocationForConversionLib; //1 + ?: is four byte type
				typeToConvertTo.m_data = new float;
				(*((float*)typeToConvertTo.m_data)) = (float)typeToConvertFrom;

				dumpFrame->Push(typeToConvertTo);

				return true;
			}

			bool ValidateStack_FloatToInt(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->Length() < 1) { return false; }
				if (dumpFrame->Top().m_data == nullptr) { return false; }

				float typeToConvertFrom = (*(float*)(dumpFrame->Top().m_data));
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();

				ist::IstackUnit typeToConvertTo = ist::IstackUnit();
				typeToConvertTo.m_modualTypeCode = 1 + m_varLibLocationForConversionLib; //1 + ?: is four byte type
				typeToConvertTo.m_data = new float;
				(*((int*)typeToConvertTo.m_data)) = (int)typeToConvertFrom;

				dumpFrame->Push(typeToConvertTo);

				return true;
			}

			bool ValidateStack_IntToString(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->Length() < 1) { return false; }
				if (dumpFrame->Top().m_data == nullptr) { return false; }

				int typeToConvertFrom = (*(int*)(dumpFrame->Top().m_data));
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();

				ist::IstackUnit typeToConvertTo = ist::IstackUnit();
				typeToConvertTo.m_modualTypeCode = 2 + m_varLibLocationForConversionLib; //2 + ?: is string type
				typeToConvertTo.m_data = new std::string;
				(*((std::string*)typeToConvertTo.m_data)) = std::to_string( typeToConvertFrom );

				dumpFrame->Push(typeToConvertTo);

				return true;
			}

			bool ValidateStack_StringToInt(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->Length() < 1) { return false; }
				if (dumpFrame->Top().m_data == nullptr) { return false; }

				std::string typeToConvertFrom = (*(std::string*)(dumpFrame->Top().m_data));
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();

				try
				{
					ist::IstackUnit typeToConvertTo = ist::IstackUnit();
					typeToConvertTo.m_modualTypeCode = 1 + m_varLibLocationForConversionLib; //1 + ?: is four byte type
					typeToConvertTo.m_data = new int;
					(*((int*)typeToConvertTo.m_data)) = std::stoi(typeToConvertFrom);

					dumpFrame->Push(typeToConvertTo);
				}
				catch (...)
				{
					return false;
				}

				return true;
			}


			bool ValidateStack_FloatToString(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->Length() < 1) { return false; }
				if (dumpFrame->Top().m_data == nullptr) { return false; }

				float typeToConvertFrom = (*(float*)(dumpFrame->Top().m_data));
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();

				ist::IstackUnit typeToConvertTo = ist::IstackUnit();
				typeToConvertTo.m_modualTypeCode = 2 + m_varLibLocationForConversionLib; //2 + ?: is string type
				typeToConvertTo.m_data = new std::string;
				(*((std::string*)typeToConvertTo.m_data)) = std::to_string(typeToConvertFrom);

				dumpFrame->Push(typeToConvertTo);

				return true;
			}

			bool ValidateStack_StringToFloat(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->Length() < 1) { return false; }
				if (dumpFrame->Top().m_data == nullptr) { return false; }

				std::string typeToConvertFrom = (*(std::string*)(dumpFrame->Top().m_data));
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();

				try
				{
					ist::IstackUnit typeToConvertTo = ist::IstackUnit();
					typeToConvertTo.m_modualTypeCode = 1 + m_varLibLocationForConversionLib; //1 + ?: is four byte type
					typeToConvertTo.m_data = new float;
					(*((float*)typeToConvertTo.m_data)) = std::stof(typeToConvertFrom);

					dumpFrame->Push(typeToConvertTo);
				}
				catch (...)
				{
					return false;
				}

				return true;
			}

			bool ValidateStack_StringToBool(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->Length() < 1) { return false; }
				if (dumpFrame->Top().m_data == nullptr) { return false; }

				std::string typeToConvertFrom = (*(std::string*)(dumpFrame->Top().m_data));
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();

				ist::IstackUnit typeToConvertTo = ist::IstackUnit();
				typeToConvertTo.m_modualTypeCode = 0 + m_varLibLocationForConversionLib; //0 + ?: is byte type
				typeToConvertTo.m_data = new bool;
				
				(*((bool*)typeToConvertTo.m_data)) = false;

				if (typeToConvertFrom == "1") { (*((bool*)typeToConvertTo.m_data)) = true; }
				if (typeToConvertFrom == "true") { (*((bool*)typeToConvertTo.m_data)) = true; }

				dumpFrame->Push(typeToConvertTo);

				return true;
			}


			bool ValidateStack_BoolToString(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->Length() < 1) { return false; }
				if (dumpFrame->Top().m_data == nullptr) { return false; }

				bool typeToConvertFrom = (*(bool*)(dumpFrame->Top().m_data));
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();

				ist::IstackUnit typeToConvertTo = ist::IstackUnit();
				typeToConvertTo.m_modualTypeCode = 2 + m_varLibLocationForConversionLib; //2 + ?: is string type
				typeToConvertTo.m_data = new std::string;
				(*((std::string*)typeToConvertTo.m_data)) = "false";

				if (typeToConvertFrom == true) { (*((std::string*)typeToConvertTo.m_data)) = "true"; }

				dumpFrame->Push(typeToConvertTo);

				return true;
			}

			bool ValidateStack_BoolToInt(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->Length() < 1) { return false; }
				if (dumpFrame->Top().m_data == nullptr) { return false; }

				bool typeToConvertFrom = (*(bool*)(dumpFrame->Top().m_data));
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();

				ist::IstackUnit typeToConvertTo = ist::IstackUnit();
				typeToConvertTo.m_modualTypeCode = 1 + m_varLibLocationForConversionLib; //1 + ?: is four byte type
				typeToConvertTo.m_data = new float;
				(*((int*)typeToConvertTo.m_data)) = (int)typeToConvertFrom;

				dumpFrame->Push(typeToConvertTo);

				return true;
			}

			bool ValidateStack_IntToBool(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->Length() < 1) { return false; }
				if (dumpFrame->Top().m_data == nullptr) { return false; }

				int typeToConvertFrom = (*(int*)(dumpFrame->Top().m_data));
				exec->FreeUnit(dumpFrame->TopPtr());
				dumpFrame->Pop();

				ist::IstackUnit typeToConvertTo = ist::IstackUnit();
				typeToConvertTo.m_modualTypeCode = 0 + m_varLibLocationForConversionLib; //0 + ?: is byte type
				typeToConvertTo.m_data = new bool;
				(*((bool*)typeToConvertTo.m_data)) = (bool)typeToConvertFrom;

				dumpFrame->Push(typeToConvertTo);

				return true;
			}

		}

		void LoadConversionModules(IstackModuleExacuteor* module, IstackLexParser* parser, unsigned int varLibOffset)
		{
			raw::m_varLibLocationForConversionLib = varLibOffset;


		}
	}
}