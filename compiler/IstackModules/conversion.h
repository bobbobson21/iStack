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
			ConversionFailure = 103,
		};

		namespace raw
		{
			static unsigned int n_varLibLocationForConversionLib = 0;

			bool ValidateStack_IntToFloat(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 1) { exec->ErrorSetCode(StackEmptyConversion); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(DataIsNullConversion); return false; }


				int typeToConvertFrom = (*(int*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();

				ist::IstackUnit typeToConvertTo = ist::IstackUnit();
				typeToConvertTo.m_modualTypeCode = 1 + n_varLibLocationForConversionLib; //1 + ?: is four byte type
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
				typeToConvertTo.m_modualTypeCode = 1 + n_varLibLocationForConversionLib; //1 + ?: is four byte type
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
				typeToConvertTo.m_modualTypeCode = 2 + n_varLibLocationForConversionLib; //2 + ?: is string type
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
					typeToConvertTo.m_modualTypeCode = 1 + n_varLibLocationForConversionLib; //1 + ?: is four byte type
					typeToConvertTo.m_data = new int;
					(*((int*)typeToConvertTo.m_data)) = std::stoi(typeToConvertFrom);

					dumpFrame->UnitPush(typeToConvertTo);
				}
				catch (...)
				{
					exec->ErrorSetCode(ConversionFailure);
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
				typeToConvertTo.m_modualTypeCode = 2 + n_varLibLocationForConversionLib; //2 + ?: is string type
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
					typeToConvertTo.m_modualTypeCode = 1 + n_varLibLocationForConversionLib; //1 + ?: is four byte type
					typeToConvertTo.m_data = new float;
					(*((float*)typeToConvertTo.m_data)) = std::stof(typeToConvertFrom);

					dumpFrame->UnitPush(typeToConvertTo);
				}
				catch (...)
				{
					exec->ErrorSetCode(ConversionFailure);
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
				typeToConvertTo.m_modualTypeCode = 0 + n_varLibLocationForConversionLib; //0 + ?: is byte type
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
				typeToConvertTo.m_modualTypeCode = 2 + n_varLibLocationForConversionLib; //2 + ?: is string type
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
				typeToConvertTo.m_modualTypeCode = 1 + n_varLibLocationForConversionLib; //1 + ?: is four byte type
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
				typeToConvertTo.m_modualTypeCode = 0 + n_varLibLocationForConversionLib; //0 + ?: is byte type
				typeToConvertTo.m_data = new bool;
				(*((bool*)typeToConvertTo.m_data)) = (bool)typeToConvertFrom;

				dumpFrame->UnitPush(typeToConvertTo);

				return true;
			}
		}

		void LoadConversionModules(IstackModuleExacuteor* module, IstackLexParser* parser, unsigned int varLibOffset)
		{
			raw::n_varLibLocationForConversionLib = varLibOffset;

			
			ist::IstackModuleType ItF = ist::IstackModuleType();
			ItF.ValidateStack = raw::ValidateStack_IntToFloat;
			ItF.ValidateSelf = raw::ValidateSelf_Fail;
			//ItF.FreeData = raw::FreeData_Single; //not needed conversion has no data
			//notMod.FreeData = raw::CopyData_Char; //not needed due to validate stack exacuting before any data can be read

			module->ModuleAddType(ItF);
			if (parser != nullptr) { parser->WordsAdd("#i>>f"); }


			ist::IstackModuleType FtI = ist::IstackModuleType();
			FtI.ValidateStack = raw::ValidateStack_FloatToInt;
			FtI.ValidateSelf = raw::ValidateSelf_Fail;
			//ItF.FreeData = raw::FreeData_Single; //not needed conversion has no data
			//notMod.FreeData = raw::CopyData_Char; //not needed due to validate stack exacuting before any data can be read

			module->ModuleAddType(FtI);
			if (parser != nullptr) { parser->WordsAdd("#f>>i"); }


			ist::IstackModuleType ItS = ist::IstackModuleType();
			ItS.ValidateStack = raw::ValidateStack_IntToString;
			ItS.ValidateSelf = raw::ValidateSelf_Fail;
			//ItF.FreeData = raw::FreeData_Single; //not needed conversion has no data
			//notMod.FreeData = raw::CopyData_Char; //not needed due to validate stack exacuting before any data can be read

			module->ModuleAddType(ItS);
			if (parser != nullptr) { parser->WordsAdd("#i>>str"); }


			ist::IstackModuleType StI = ist::IstackModuleType();
			StI.ValidateStack = raw::ValidateStack_StringToInt;
			StI.ValidateSelf = raw::ValidateSelf_Fail;
			//ItF.FreeData = raw::FreeData_Single; //not needed conversion has no data
			//notMod.FreeData = raw::CopyData_Char; //not needed due to validate stack exacuting before any data can be read

			module->ModuleAddType(StI);
			if (parser != nullptr) { parser->WordsAdd("#str>>i"); }


			ist::IstackModuleType FtS = ist::IstackModuleType();
			FtS.ValidateStack = raw::ValidateStack_FloatToString;
			FtS.ValidateSelf = raw::ValidateSelf_Fail;
			//ItF.FreeData = raw::FreeData_Single; //not needed conversion has no data
			//notMod.FreeData = raw::CopyData_Char; //not needed due to validate stack exacuting before any data can be read

			module->ModuleAddType(FtS);
			if (parser != nullptr) { parser->WordsAdd("#f>>str"); }


			ist::IstackModuleType StF = ist::IstackModuleType();
			StF.ValidateStack = raw::ValidateStack_StringToFloat;
			StF.ValidateSelf = raw::ValidateSelf_Fail;
			//ItF.FreeData = raw::FreeData_Single; //not needed conversion has no data
			//notMod.FreeData = raw::CopyData_Char; //not needed due to validate stack exacuting before any data can be read

			module->ModuleAddType(StF);
			if (parser != nullptr) { parser->WordsAdd("#str>>f"); }


			ist::IstackModuleType StB = ist::IstackModuleType();
			StB.ValidateStack = raw::ValidateStack_StringToBool;
			StB.ValidateSelf = raw::ValidateSelf_Fail;
			//ItF.FreeData = raw::FreeData_Single; //not needed conversion has no data
			//notMod.FreeData = raw::CopyData_Char; //not needed due to validate stack exacuting before any data can be read

			module->ModuleAddType(StB);
			if (parser != nullptr) { parser->WordsAdd("#str>>b"); }


			ist::IstackModuleType BtS = ist::IstackModuleType();
			BtS.ValidateStack = raw::ValidateStack_BoolToString;
			BtS.ValidateSelf = raw::ValidateSelf_Fail;
			//ItF.FreeData = raw::FreeData_Single; //not needed conversion has no data
			//notMod.FreeData = raw::CopyData_Char; //not needed due to validate stack exacuting before any data can be read

			module->ModuleAddType(BtS);
			if (parser != nullptr) { parser->WordsAdd("#b>>str"); }


			ist::IstackModuleType BtI = ist::IstackModuleType();
			BtI.ValidateStack = raw::ValidateStack_BoolToInt;
			BtI.ValidateSelf = raw::ValidateSelf_Fail;
			//ItF.FreeData = raw::FreeData_Single; //not needed conversion has no data
			//notMod.FreeData = raw::CopyData_Char; //not needed due to validate stack exacuting before any data can be read

			module->ModuleAddType(BtI);
			if (parser != nullptr) { parser->WordsAdd("#b>>i"); }


			ist::IstackModuleType ItB = ist::IstackModuleType();
			ItB.ValidateStack = raw::ValidateStack_IntToBool;
			ItB.ValidateSelf = raw::ValidateSelf_Fail;
			//ItF.FreeData = raw::FreeData_Single; //not needed conversion has no data
			//notMod.FreeData = raw::CopyData_Char; //not needed due to validate stack exacuting before any data can be read

			module->ModuleAddType(ItB);
			if (parser != nullptr) { parser->WordsAdd("#i>>b"); }
		}
	}
}