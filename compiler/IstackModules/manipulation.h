#pragma once

#include <string>

#include "generics.h"

namespace ist
{
	namespace modules
	{
		enum moduleManipulationErrorCodes : unsigned int
		{
			StackEmptyManipulation = 701,
			StackSizeInvalidManipulation = 702,
			DataIsNullManipulation = 703,
		};

		namespace raw
		{
			static unsigned int m_varLibLocationForManipulationLib = 0;

			bool ValidateStack_DupeUniversalCopy(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data) ///not recommened for use as it will mess around with memory, in reguards to what unit owns what memory, if it is unable to copy something, which will happen if a module dosent have a copy func
			{
				if (dumpFrame->UnitLength() < 1) { exec->ErrorSetCode(StackEmptyManipulation); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(DataIsNullManipulation); return false; }


				ist::IstackUnit typeToAdd = ist::IstackUnit();
				exec->CopyUnitFromAndTo(dumpFrame->UnitTopPtr(), &typeToAdd);

				dumpFrame->UnitPush(typeToAdd);

				return true;
			}

			bool ValidateStack_DupeByte(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 1) { exec->ErrorSetCode(StackEmptyManipulation); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(DataIsNullManipulation); return false; }


				ist::IstackUnit typeToAdd = ist::IstackUnit();
				typeToAdd.m_modualTypeCode = 0 + m_varLibLocationForManipulationLib; //0 + ?: is byte type
				typeToAdd.m_data = new char;

				memcpy(typeToAdd.m_data, dumpFrame->UnitTop().m_data, sizeof(char) * 1);

				dumpFrame->UnitPush(typeToAdd);

				return true;
			}

			bool ValidateStack_DupeFourByte(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 1) { exec->ErrorSetCode(StackEmptyManipulation); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(DataIsNullManipulation); return false; }


				ist::IstackUnit typeToAdd = ist::IstackUnit();
				typeToAdd.m_modualTypeCode = 1 + m_varLibLocationForManipulationLib; //1 + ?: is four byte type
				typeToAdd.m_data = new char[4];

				memcpy(typeToAdd.m_data, dumpFrame->UnitTop().m_data, sizeof(char) * 4);

				dumpFrame->UnitPush(typeToAdd);

				return true;
			}

			bool ValidateStack_DupeString(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 1) { exec->ErrorSetCode(StackEmptyManipulation); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(DataIsNullManipulation); return false; }


				ist::IstackUnit typeToAdd = ist::IstackUnit();
				typeToAdd.m_modualTypeCode = 1 + m_varLibLocationForManipulationLib; //1 + ?: is four byte type
				typeToAdd.m_data = new std::string;

				for (size_t i = 0; i < (*(std::string*)(dumpFrame->UnitTop().m_data)).size(); i++)
				{
					(*(std::string*)(typeToAdd.m_data)) += (*(std::string*)(dumpFrame->UnitTop().m_data))[i];
				}

				dumpFrame->UnitPush(typeToAdd);

				return true;
			}

			bool ValidateStack_DupeRefrence(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 1) { exec->ErrorSetCode(StackEmptyManipulation); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(DataIsNullManipulation); return false; }


				(*data) = dumpFrame->UnitTop().m_data;

				return true;
			}


			bool ValidateStack_DupePop(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 1) { exec->ErrorSetCode(StackEmptyManipulation); return false; }

				dumpFrame->UnitPop();

				return true;
			}


			bool ValidateStack_DupeCount(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				(*data) = new int;
				(*((int*)(*data))) = dumpFrame->UnitLength();

				return true;
			}


			bool ValidateStack_DupeSwap(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 2) { exec->ErrorSetCode(StackSizeInvalidManipulation); return false; }

				IstackUnit A = dumpFrame->UnitTop();
				dumpFrame->UnitPop();

				IstackUnit B = dumpFrame->UnitTop();
				dumpFrame->UnitPop();


				dumpFrame->UnitPush(A);
				dumpFrame->UnitPush(B);

				return true;
			}

		}

		void LoadManipulationModules(IstackModuleExacuteor* module, IstackLexParser* parser, unsigned int varLibOffset)
		{
			raw::m_varLibLocationForManipulationLib = varLibOffset;

			ist::IstackModuleType Bcpy = ist::IstackModuleType();
			Bcpy.ValidateStack = raw::ValidateStack_DupeByte;
			Bcpy.ValidateSelf = raw::ValidateSelf_Fail;
			//ItF.FreeData = raw::FreeData_Single; //not needed conversion has no data
			//notMod.FreeData = raw::CopyData_Char; //not needed due to validate stack exacuting before any data can be read

			module->ModuleAddType(Bcpy);
			if (parser != nullptr) { parser->AddWord("&Byte<<"); }


			ist::IstackModuleType FBcpy = ist::IstackModuleType();
			FBcpy.ValidateStack = raw::ValidateStack_DupeFourByte;
			FBcpy.ValidateSelf = raw::ValidateSelf_Fail;
			//ItF.FreeData = raw::FreeData_Single; //not needed conversion has no data
			//notMod.FreeData = raw::CopyData_Char; //not needed due to validate stack exacuting before any data can be read

			module->ModuleAddType(FBcpy);
			if (parser != nullptr) { parser->AddWord("&FourByte<<"); }


			ist::IstackModuleType STRcpy = ist::IstackModuleType();
			STRcpy.ValidateStack = raw::ValidateStack_DupeString;
			STRcpy.ValidateSelf = raw::ValidateSelf_Fail;
			//ItF.FreeData = raw::FreeData_Single; //not needed conversion has no data
			//notMod.FreeData = raw::CopyData_Char; //not needed due to validate stack exacuting before any data can be read

			module->ModuleAddType(STRcpy);
			if (parser != nullptr) { parser->AddWord("&String<<"); }


			ist::IstackModuleType CPYcpy = ist::IstackModuleType();
			CPYcpy.ValidateStack = raw::ValidateStack_DupeUniversalCopy;
			CPYcpy.ValidateSelf = raw::ValidateSelf_Fail;
			//ItF.FreeData = raw::FreeData_Single; //not needed conversion has no data
			//notMod.FreeData = raw::CopyData_Char; //not needed due to validate stack exacuting before any data can be read

			module->ModuleAddType(CPYcpy);
			if (parser != nullptr) { parser->AddWord("&DataCpyOrMoveIfFail<<"); }


			ist::IstackModuleType Ref = ist::IstackModuleType();
			Ref.ValidateStack = raw::ValidateStack_DupeRefrence;
			Ref.ValidateSelf = raw::ValidateSelf_Success;
			Ref.FreeData = raw::FreeData_Fail;
			Ref.CopyData = raw::CopyData_CopyFail;

			module->ModuleAddType(Ref);
			if (parser != nullptr) { parser->AddWord("&Pointer<<"); }


			ist::IstackModuleType Count = ist::IstackModuleType();
			Count.ValidateStack = raw::ValidateStack_DupeSwap;
			Count.ValidateSelf = raw::ValidateSelf_Fail;
			Count.FreeData = raw::FreeData_Fail;

			module->ModuleAddType(Count);
			if (parser != nullptr) { parser->AddWord("&Count<<"); }


			ist::IstackModuleType Pop = ist::IstackModuleType();
			Pop.ValidateStack = raw::ValidateStack_DupeSwap;
			Pop.ValidateSelf = raw::ValidateSelf_Fail;

			module->ModuleAddType(Pop);
			if (parser != nullptr) { parser->AddWord("&Pop>>"); }


			ist::IstackModuleType Swap = ist::IstackModuleType();
			Swap.ValidateStack = raw::ValidateStack_DupeSwap;
			Swap.ValidateSelf = raw::ValidateSelf_Fail;

			module->ModuleAddType(Swap);
			if (parser != nullptr) { parser->AddWord("&Swap<<"); }
		}
	}
}