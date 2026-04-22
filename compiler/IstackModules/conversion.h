#pragma once

#include <string>

#include "generics.h"

namespace ist
{
	namespace modules
	{
		enum moduleConversionErrorCodes : unsigned int
		{
			StackEmptyConversion = 101,
			DataIsNullConversion = 102,
		};

		namespace raw
		{
			static unsigned int m_varLibLocationForConversionLib = 0;

			bool ValidateStack_IntToFloat(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 1) { exec->ErrorSetCode(StackEmptyConversion); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(DataIsNullConversion); return false; }


				int typeToConvertFrom = (*(int*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();

				ist::IstackUnit typeToConvertTo = ist::IstackUnit();
				typeToConvertTo.m_modualTypeCode = 1 + m_varLibLocationForConversionLib; //1 + ?: is four byte type
				typeToConvertTo.m_data = new float;
				(*((float*)typeToConvertTo.m_data)) = (float)typeToConvertFrom;

				dumpFrame->UnitPush(typeToConvertTo);

				return true;
			}

			bool ValidateStack_FloatToInt(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 1) { exec->ErrorSetCode(StackEmptyConversion); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(DataIsNullConversion); return false; }

				float typeToConvertFrom = (*(float*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();

				ist::IstackUnit typeToConvertTo = ist::IstackUnit();
				typeToConvertTo.m_modualTypeCode = 1 + m_varLibLocationForConversionLib; //1 + ?: is four byte type
				typeToConvertTo.m_data = new float;
				(*((int*)typeToConvertTo.m_data)) = (int)typeToConvertFrom;

				dumpFrame->UnitPush(typeToConvertTo);

				return true;
			}

			bool ValidateStack_IntToString(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 1) { exec->ErrorSetCode(StackEmptyConversion); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(DataIsNullConversion); return false; }

				int typeToConvertFrom = (*(int*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();

				ist::IstackUnit typeToConvertTo = ist::IstackUnit();
				typeToConvertTo.m_modualTypeCode = 2 + m_varLibLocationForConversionLib; //2 + ?: is string type
				typeToConvertTo.m_data = new std::string;
				(*((std::string*)typeToConvertTo.m_data)) = std::to_string( typeToConvertFrom );

				dumpFrame->UnitPush(typeToConvertTo);

				return true;
			}

			bool ValidateStack_StringToInt(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 1) { exec->ErrorSetCode(StackEmptyConversion); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(DataIsNullConversion); return false; }

				std::string typeToConvertFrom = (*(std::string*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();

				try
				{
					ist::IstackUnit typeToConvertTo = ist::IstackUnit();
					typeToConvertTo.m_modualTypeCode = 1 + m_varLibLocationForConversionLib; //1 + ?: is four byte type
					typeToConvertTo.m_data = new int;
					(*((int*)typeToConvertTo.m_data)) = std::stoi(typeToConvertFrom);

					dumpFrame->UnitPush(typeToConvertTo);
				}
				catch (...)
				{
					return false;
				}

				return true;
			}


			bool ValidateStack_FloatToString(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 1) { exec->ErrorSetCode(StackEmptyConversion); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(DataIsNullConversion); return false; }

				float typeToConvertFrom = (*(float*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();

				ist::IstackUnit typeToConvertTo = ist::IstackUnit();
				typeToConvertTo.m_modualTypeCode = 2 + m_varLibLocationForConversionLib; //2 + ?: is string type
				typeToConvertTo.m_data = new std::string;
				(*((std::string*)typeToConvertTo.m_data)) = std::to_string(typeToConvertFrom);

				dumpFrame->UnitPush(typeToConvertTo);

				return true;
			}

			bool ValidateStack_StringToFloat(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 1) { exec->ErrorSetCode(StackEmptyConversion); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(DataIsNullConversion); return false; }

				std::string typeToConvertFrom = (*(std::string*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();

				try
				{
					ist::IstackUnit typeToConvertTo = ist::IstackUnit();
					typeToConvertTo.m_modualTypeCode = 1 + m_varLibLocationForConversionLib; //1 + ?: is four byte type
					typeToConvertTo.m_data = new float;
					(*((float*)typeToConvertTo.m_data)) = std::stof(typeToConvertFrom);

					dumpFrame->UnitPush(typeToConvertTo);
				}
				catch (...)
				{
					return false;
				}

				return true;
			}

			bool ValidateStack_StringToBool(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 1) { exec->ErrorSetCode(StackEmptyConversion); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(DataIsNullConversion); return false; }

				std::string typeToConvertFrom = (*(std::string*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();

				ist::IstackUnit typeToConvertTo = ist::IstackUnit();
				typeToConvertTo.m_modualTypeCode = 0 + m_varLibLocationForConversionLib; //0 + ?: is byte type
				typeToConvertTo.m_data = new bool;
				
				(*((bool*)typeToConvertTo.m_data)) = false;

				if (typeToConvertFrom == "1") { (*((bool*)typeToConvertTo.m_data)) = true; }
				if (typeToConvertFrom == "true") { (*((bool*)typeToConvertTo.m_data)) = true; }

				dumpFrame->UnitPush(typeToConvertTo);

				return true;
			}


			bool ValidateStack_BoolToString(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 1) { exec->ErrorSetCode(StackEmptyConversion); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(DataIsNullConversion); return false; }

				bool typeToConvertFrom = (*(bool*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();

				ist::IstackUnit typeToConvertTo = ist::IstackUnit();
				typeToConvertTo.m_modualTypeCode = 2 + m_varLibLocationForConversionLib; //2 + ?: is string type
				typeToConvertTo.m_data = new std::string;
				(*((std::string*)typeToConvertTo.m_data)) = "false";

				if (typeToConvertFrom == true) { (*((std::string*)typeToConvertTo.m_data)) = "true"; }

				dumpFrame->UnitPush(typeToConvertTo);

				return true;
			}

			bool ValidateStack_BoolToInt(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 1) { exec->ErrorSetCode(StackEmptyConversion); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(DataIsNullConversion); return false; }

				bool typeToConvertFrom = (*(bool*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();

				ist::IstackUnit typeToConvertTo = ist::IstackUnit();
				typeToConvertTo.m_modualTypeCode = 1 + m_varLibLocationForConversionLib; //1 + ?: is four byte type
				typeToConvertTo.m_data = new float;
				(*((int*)typeToConvertTo.m_data)) = (int)typeToConvertFrom;

				dumpFrame->UnitPush(typeToConvertTo);

				return true;
			}

			bool ValidateStack_IntToBool(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 1) { exec->ErrorSetCode(StackEmptyConversion); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(DataIsNullConversion); return false; }

				int typeToConvertFrom = (*(int*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();

				ist::IstackUnit typeToConvertTo = ist::IstackUnit();
				typeToConvertTo.m_modualTypeCode = 0 + m_varLibLocationForConversionLib; //0 + ?: is byte type
				typeToConvertTo.m_data = new bool;
				(*((bool*)typeToConvertTo.m_data)) = (bool)typeToConvertFrom;

				dumpFrame->UnitPush(typeToConvertTo);

				return true;
			}


			bool ValidateStack_DupeUniversalCopy(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data) ///not recommened for use as it will mess around with memory, in reguards to what unit owns what memory, if it is unable to copy something, which will happen if a module dosent have a copy func
			{
				if (dumpFrame->UnitLength() < 1) { exec->ErrorSetCode(StackEmptyConversion); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(DataIsNullConversion); return false; }


				ist::IstackUnit typeToAdd = ist::IstackUnit();
				exec->CopyUnitFromAndTo(dumpFrame->UnitTopPtr(), &typeToAdd);

				dumpFrame->UnitPush(typeToAdd);

				return true;
			}

			bool ValidateStack_DupeByte(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 1) { exec->ErrorSetCode(StackEmptyConversion); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(DataIsNullConversion); return false; }


				ist::IstackUnit typeToAdd = ist::IstackUnit();
				typeToAdd.m_modualTypeCode = 0 + m_varLibLocationForConversionLib; //0 + ?: is byte type
				typeToAdd.m_data = new char;

				memcpy(typeToAdd.m_data, dumpFrame->UnitTop().m_data, sizeof(char) * 1);

				dumpFrame->UnitPush(typeToAdd);

				return true;
			}

			bool ValidateStack_DupeFourByte(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 1) { exec->ErrorSetCode(StackEmptyConversion); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(DataIsNullConversion); return false; }


				ist::IstackUnit typeToAdd = ist::IstackUnit();
				typeToAdd.m_modualTypeCode = 1 + m_varLibLocationForConversionLib; //1 + ?: is four byte type
				typeToAdd.m_data = new char[4];
				
				memcpy(typeToAdd.m_data, dumpFrame->UnitTop().m_data, sizeof(char) * 4);

				dumpFrame->UnitPush(typeToAdd);

				return true;
			}

			bool ValidateStack_DupeString(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 1) { exec->ErrorSetCode(StackEmptyConversion); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(DataIsNullConversion); return false; }


				ist::IstackUnit typeToAdd = ist::IstackUnit();
				typeToAdd.m_modualTypeCode = 1 + m_varLibLocationForConversionLib; //1 + ?: is four byte type
				typeToAdd.m_data = new std::string;

				for (size_t i = 0; i < (*(std::string*)(dumpFrame->UnitTop().m_data)).size(); i++)
				{
					(*(std::string*)(typeToAdd.m_data)) += (*(std::string*)(dumpFrame->UnitTop().m_data))[i];
				}

				dumpFrame->UnitPush(typeToAdd);

				return true;
			}
		}

		void LoadConversionModules(IstackModuleExacuteor* module, IstackLexParser* parser, unsigned int varLibOffset)
		{
			raw::m_varLibLocationForConversionLib = varLibOffset;

			
			ist::IstackModuleType ItF = ist::IstackModuleType();
			ItF.ValidateStack = raw::ValidateStack_IntToFloat;
			ItF.ValidateSelf = raw::ValidateSelf_Fail;
			//ItF.FreeData = raw::FreeData_Single; //not needed conversion has no data
			//notMod.FreeData = raw::CopyData_Char; //not needed due to validate stack exacuting before any data can be read

			module->ModuleAdd(ItF);
			if (parser != nullptr) { parser->AddWord("#i>>f"); }


			ist::IstackModuleType FtI = ist::IstackModuleType();
			FtI.ValidateStack = raw::ValidateStack_FloatToInt;
			FtI.ValidateSelf = raw::ValidateSelf_Fail;
			//ItF.FreeData = raw::FreeData_Single; //not needed conversion has no data
			//notMod.FreeData = raw::CopyData_Char; //not needed due to validate stack exacuting before any data can be read

			module->ModuleAdd(FtI);
			if (parser != nullptr) { parser->AddWord("#f>>i"); }


			ist::IstackModuleType ItS = ist::IstackModuleType();
			ItS.ValidateStack = raw::ValidateStack_IntToString;
			ItS.ValidateSelf = raw::ValidateSelf_Fail;
			//ItF.FreeData = raw::FreeData_Single; //not needed conversion has no data
			//notMod.FreeData = raw::CopyData_Char; //not needed due to validate stack exacuting before any data can be read

			module->ModuleAdd(ItS);
			if (parser != nullptr) { parser->AddWord("#i>>str"); }


			ist::IstackModuleType StI = ist::IstackModuleType();
			StI.ValidateStack = raw::ValidateStack_StringToInt;
			StI.ValidateSelf = raw::ValidateSelf_Fail;
			//ItF.FreeData = raw::FreeData_Single; //not needed conversion has no data
			//notMod.FreeData = raw::CopyData_Char; //not needed due to validate stack exacuting before any data can be read

			module->ModuleAdd(StI);
			if (parser != nullptr) { parser->AddWord("#str>>i"); }


			ist::IstackModuleType FtS = ist::IstackModuleType();
			FtS.ValidateStack = raw::ValidateStack_FloatToString;
			FtS.ValidateSelf = raw::ValidateSelf_Fail;
			//ItF.FreeData = raw::FreeData_Single; //not needed conversion has no data
			//notMod.FreeData = raw::CopyData_Char; //not needed due to validate stack exacuting before any data can be read

			module->ModuleAdd(FtS);
			if (parser != nullptr) { parser->AddWord("#f>>str"); }


			ist::IstackModuleType StF = ist::IstackModuleType();
			StF.ValidateStack = raw::ValidateStack_StringToFloat;
			StF.ValidateSelf = raw::ValidateSelf_Fail;
			//ItF.FreeData = raw::FreeData_Single; //not needed conversion has no data
			//notMod.FreeData = raw::CopyData_Char; //not needed due to validate stack exacuting before any data can be read

			module->ModuleAdd(StF);
			if (parser != nullptr) { parser->AddWord("#str>>f"); }


			ist::IstackModuleType StB = ist::IstackModuleType();
			StB.ValidateStack = raw::ValidateStack_StringToBool;
			StB.ValidateSelf = raw::ValidateSelf_Fail;
			//ItF.FreeData = raw::FreeData_Single; //not needed conversion has no data
			//notMod.FreeData = raw::CopyData_Char; //not needed due to validate stack exacuting before any data can be read

			module->ModuleAdd(StB);
			if (parser != nullptr) { parser->AddWord("#str>>b"); }


			ist::IstackModuleType BtS = ist::IstackModuleType();
			BtS.ValidateStack = raw::ValidateStack_BoolToString;
			BtS.ValidateSelf = raw::ValidateSelf_Fail;
			//ItF.FreeData = raw::FreeData_Single; //not needed conversion has no data
			//notMod.FreeData = raw::CopyData_Char; //not needed due to validate stack exacuting before any data can be read

			module->ModuleAdd(BtS);
			if (parser != nullptr) { parser->AddWord("#b>>str"); }


			ist::IstackModuleType BtI = ist::IstackModuleType();
			BtI.ValidateStack = raw::ValidateStack_BoolToInt;
			BtI.ValidateSelf = raw::ValidateSelf_Fail;
			//ItF.FreeData = raw::FreeData_Single; //not needed conversion has no data
			//notMod.FreeData = raw::CopyData_Char; //not needed due to validate stack exacuting before any data can be read

			module->ModuleAdd(BtI);
			if (parser != nullptr) { parser->AddWord("#b>>i"); }


			ist::IstackModuleType ItB = ist::IstackModuleType();
			ItB.ValidateStack = raw::ValidateStack_IntToBool;
			ItB.ValidateSelf = raw::ValidateSelf_Fail;
			//ItF.FreeData = raw::FreeData_Single; //not needed conversion has no data
			//notMod.FreeData = raw::CopyData_Char; //not needed due to validate stack exacuting before any data can be read

			module->ModuleAdd(ItB);
			if (parser != nullptr) { parser->AddWord("#i>>b"); }


			ist::IstackModuleType Bcpy = ist::IstackModuleType();
			Bcpy.ValidateStack = raw::ValidateStack_DupeByte;
			Bcpy.ValidateSelf = raw::ValidateSelf_Fail;
			//ItF.FreeData = raw::FreeData_Single; //not needed conversion has no data
			//notMod.FreeData = raw::CopyData_Char; //not needed due to validate stack exacuting before any data can be read

			module->ModuleAdd(Bcpy);
			if (parser != nullptr) { parser->AddWord("#Byte<<"); }


			ist::IstackModuleType FBcpy = ist::IstackModuleType();
			FBcpy.ValidateStack = raw::ValidateStack_DupeFourByte;
			FBcpy.ValidateSelf = raw::ValidateSelf_Fail;
			//ItF.FreeData = raw::FreeData_Single; //not needed conversion has no data
			//notMod.FreeData = raw::CopyData_Char; //not needed due to validate stack exacuting before any data can be read

			module->ModuleAdd(FBcpy);
			if (parser != nullptr) { parser->AddWord("#FourByte<<"); }


			ist::IstackModuleType STRcpy = ist::IstackModuleType();
			STRcpy.ValidateStack = raw::ValidateStack_DupeString;
			STRcpy.ValidateSelf = raw::ValidateSelf_Fail;
			//ItF.FreeData = raw::FreeData_Single; //not needed conversion has no data
			//notMod.FreeData = raw::CopyData_Char; //not needed due to validate stack exacuting before any data can be read

			module->ModuleAdd(STRcpy);
			if (parser != nullptr) { parser->AddWord("#String<<"); }


			ist::IstackModuleType CPYcpy = ist::IstackModuleType();
			CPYcpy.ValidateStack = raw::ValidateStack_DupeUniversalCopy;
			CPYcpy.ValidateSelf = raw::ValidateSelf_Fail;
			//ItF.FreeData = raw::FreeData_Single; //not needed conversion has no data
			//notMod.FreeData = raw::CopyData_Char; //not needed due to validate stack exacuting before any data can be read

			module->ModuleAdd(CPYcpy);
			if (parser != nullptr) { parser->AddWord("#DataCpyOrMoveIfFail<<"); }
		}
	}
}