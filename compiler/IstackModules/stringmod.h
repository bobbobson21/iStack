#pragma once

#include <string>

#include "generics.h"


namespace ist
{
	namespace modules
	{
		enum moduleStringModErrorCodes : unsigned int
		{
			StringInvalidStringMod = 2001,

			StackEmptyStringMod = 2002,
			StackElementSizeNotMetStringMod = 2003,
			StringIsNullStringMod = 2004,

			ExceededStringBounds = 2005,
		};

		namespace raw
		{
			bool ValidateStack_StringCombine(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 2) { exec->ErrorSetCode(StackElementSizeNotMetStringMod); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StringIsNullStringMod); return false; }

				try
				{
					std::string A = (*(std::string*)(dumpFrame->UnitTop().m_data));
					exec->FreeUnit(dumpFrame->UnitTopPtr());
					dumpFrame->UnitPop();

					if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StringIsNullStringMod); return false; }

					std::string B = (*(std::string*)(dumpFrame->UnitTop().m_data));
					exec->FreeUnit(dumpFrame->UnitTopPtr());
					dumpFrame->UnitPop();

					if ((*data) != nullptr)
					{
						delete (std::string*)data;
					}

					(*data) = new std::string;
					(*(std::string*)(*data)) = (A + B);
				}
				catch (...)
				{
					exec->ErrorSetCode(StringInvalidStringMod);
					return false;
				}

				return true;
			}

			bool ValidateStack_StringLength(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 2) { exec->ErrorSetCode(StackElementSizeNotMetStringMod); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StringIsNullStringMod); return false; }

				try
				{
					std::string A = (*(std::string*)(dumpFrame->UnitTop().m_data));
					exec->FreeUnit(dumpFrame->UnitTopPtr());
					dumpFrame->UnitPop();

					if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StringIsNullStringMod); return false; }

					delete (*data);
					(*data) = new int;
					(*(int*)(*data)) = (A.length());
				}
				catch (...)
				{
					exec->ErrorSetCode(StringInvalidStringMod);
					return false;
				}

				return true;
			}

			bool ValidateStack_StringUpper(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 1) { exec->ErrorSetCode(StackEmptyStringMod); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StringIsNullStringMod); return false; }

				try
				{
					std::string A = (*(std::string*)(dumpFrame->UnitTop().m_data));
					exec->FreeUnit(dumpFrame->UnitTopPtr());
					dumpFrame->UnitPop();

					for (size_t i = 0; i < A.length(); i++)
					{
						A[i] = toupper(A[i]);
					}

					if ((*data) != nullptr)
					{
						delete (std::string*)data;
					}

					(*data) = new std::string;
					(*(std::string*)(*data)) = A;
				}
				catch (...)
				{
					exec->ErrorSetCode(StringInvalidStringMod);
					return false;
				}

				return true;
			}

			bool ValidateStack_StringLower(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 1) { exec->ErrorSetCode(StackEmptyStringMod); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StringIsNullStringMod); return false; }

				try
				{
					std::string A = (*(std::string*)(dumpFrame->UnitTop().m_data));
					exec->FreeUnit(dumpFrame->UnitTopPtr());
					dumpFrame->UnitPop();

					for (size_t i = 0; i < A.length(); i++)
					{
						A[i] = tolower(A[i]);
					}

					if ((*data) != nullptr)
					{
						delete (std::string*)data;
					}

					(*data) = new std::string;
					(*(std::string*)(*data)) = A;
				}
				catch (...)
				{
					exec->ErrorSetCode(StringInvalidStringMod);
					return false;
				}

				return true;
			}

			bool ValidateStack_StringContains(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 2) { exec->ErrorSetCode(StackEmptyStringMod); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StringIsNullStringMod); return false; }

				try
				{
					std::string A = (*(std::string*)(dumpFrame->UnitTop().m_data));
					exec->FreeUnit(dumpFrame->UnitTopPtr());
					dumpFrame->UnitPop();

					if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StringIsNullStringMod); return false; }

					std::string B = (*(std::string*)(dumpFrame->UnitTop().m_data));
					exec->FreeUnit(dumpFrame->UnitTopPtr());
					dumpFrame->UnitPop();

					delete data;
					(*data) = new bool;
					(*(bool*)(*data)) = (A.find_first_of(B) != std::string::npos);
				}
				catch (...)
				{
					exec->ErrorSetCode(StringInvalidStringMod);
					return false;
				}

				return true;
			}

			bool ValidateStack_StringFind(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 2) { exec->ErrorSetCode(StackEmptyStringMod); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StringIsNullStringMod); return false; }

				try
				{
					std::string A = (*(std::string*)(dumpFrame->UnitTop().m_data));
					exec->FreeUnit(dumpFrame->UnitTopPtr());
					dumpFrame->UnitPop();

					if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StringIsNullStringMod); return false; }

					std::string B = (*(std::string*)(dumpFrame->UnitTop().m_data));
					exec->FreeUnit(dumpFrame->UnitTopPtr());
					dumpFrame->UnitPop();

					delete data;
					(*data) = new int;
					(*(int*)(*data)) = (A.find_first_of(B));
				}
				catch (...)
				{
					exec->ErrorSetCode(StringInvalidStringMod);
					return false;
				}

				return true;
			}

			bool ValidateStack_StringSub(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 3) { exec->ErrorSetCode(StackEmptyStringMod); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StringIsNullStringMod); return false; }

				try
				{
					std::string A = (*(std::string*)(dumpFrame->UnitTop().m_data));
					exec->FreeUnit(dumpFrame->UnitTopPtr());
					dumpFrame->UnitPop();


					if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StringIsNullStringMod); return false; }
					int B = (*(int*)(dumpFrame->UnitTop().m_data));
					exec->FreeUnit(dumpFrame->UnitTopPtr());
					dumpFrame->UnitPop();


					if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StringIsNullStringMod); return false; }
					int C = (*(int*)(dumpFrame->UnitTop().m_data));
					exec->FreeUnit(dumpFrame->UnitTopPtr());
					dumpFrame->UnitPop();

					if (B < 0 || C < 0 || B >= A.length() || C >= A.length())
					{
						exec->ErrorSetCode(ExceededStringBounds);
						return false;
					}

					if ((*data) != nullptr)
					{
						delete (std::string*)data;
					}

					(*data) = new std::string;
					(*(std::string*)(*data)) = A.substr(B, C);
				}
				catch (...)
				{
					exec->ErrorSetCode(StringInvalidStringMod);
					return false;
				}

				return true;
			}

			bool ValidateStack_StringReplace(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 3) { exec->ErrorSetCode(StackEmptyStringMod); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StringIsNullStringMod); return false; }

				try
				{
					std::string A = (*(std::string*)(dumpFrame->UnitTop().m_data)); //the string body/main string
					exec->FreeUnit(dumpFrame->UnitTopPtr());
					dumpFrame->UnitPop();


					if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StringIsNullStringMod); return false; } //the text tat needs replacing in main
					std::string B = (*(std::string*)(dumpFrame->UnitTop().m_data));
					exec->FreeUnit(dumpFrame->UnitTopPtr());
					dumpFrame->UnitPop();


					if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StringIsNullStringMod); return false; } //the text to replace it with
					std::string C = (*(std::string*)(dumpFrame->UnitTop().m_data));
					exec->FreeUnit(dumpFrame->UnitTopPtr());
					dumpFrame->UnitPop();

					std::string resultString = "";

					for (size_t i = 0; i <= A.length() - B.length(); i++) //dose replacement oparation
					{
						if (A.substr(i, B.length()) == B) //found text to replace
						{
							std::string leftSide = A.substr(0, i); //all the text left to it
							std::string rightSide = A.substr(i + B.length(), A.length() - (i + B.length())); //all the text right to it
							A = leftSide + C + rightSide; //replace
						}
					}

					if ((*data) != nullptr)
					{
						delete (std::string*)data;
					}

					(*data) = new std::string;
					(*(std::string*)(*data)) = resultString;
				}
				catch (...)
				{
					exec->ErrorSetCode(StringInvalidStringMod);
					return false;
				}

				return true;
			}
		}

		void LoadFileModules(IstackModuleExacuteor* module, IstackLexParser* parser)
		{
			ist::IstackModuleType strAdd = ist::IstackModuleType();
			strAdd.ValidateStack = raw::ValidateStack_StringCombine;
			strAdd.ValidateSelf = raw::Validate_Fail;
			strAdd.CopyData = raw::CopyData_String;
			strAdd.FreeData = raw::FreeData_String;

			module->ModuleAddType(strAdd);
			if (parser != nullptr) { parser->WordsAdd("str+"); }


			ist::IstackModuleType strLen = ist::IstackModuleType();
			strLen.ValidateStack = raw::ValidateStack_StringLength;
			strLen.ValidateSelf = raw::Validate_Fail;
			strLen.CopyData = raw::CopyData_FourChar;
			strLen.FreeData = raw::FreeData_Single;

			module->ModuleAddType(strLen);
			if (parser != nullptr) { parser->WordsAdd("strGetLengthi"); }


			ist::IstackModuleType strUpper = ist::IstackModuleType();
			strUpper.ValidateStack = raw::ValidateStack_StringUpper;
			strUpper.ValidateSelf = raw::Validate_Fail;
			strUpper.CopyData = raw::CopyData_String;
			strUpper.FreeData = raw::FreeData_String;

			module->ModuleAddType(strUpper);
			if (parser != nullptr) { parser->WordsAdd("strToUpper"); }


			ist::IstackModuleType strLower = ist::IstackModuleType();
			strLower.ValidateStack = raw::ValidateStack_StringLower;
			strLower.ValidateSelf = raw::Validate_Fail;
			strLower.CopyData = raw::CopyData_String;
			strLower.FreeData = raw::FreeData_String;

			module->ModuleAddType(strLower);
			if (parser != nullptr) { parser->WordsAdd("strToLower"); }


			ist::IstackModuleType strCon = ist::IstackModuleType();
			strCon.ValidateStack = raw::ValidateStack_StringLower;
			strCon.ValidateSelf = raw::Validate_Fail;
			strCon.CopyData = raw::CopyData_String;
			strCon.FreeData = raw::FreeData_String;

			module->ModuleAddType(strCon);
			if (parser != nullptr) { parser->WordsAdd("strContains"); }


			ist::IstackModuleType strCon = ist::IstackModuleType();
			strCon.ValidateStack = raw::ValidateStack_StringLower;
			strCon.ValidateSelf = raw::Validate_Fail;
			strCon.CopyData = raw::CopyData_Char;
			strCon.FreeData = raw::FreeData_Single;

			module->ModuleAddType(strCon);
			if (parser != nullptr) { parser->WordsAdd("strContains"); }


			ist::IstackModuleType strFind = ist::IstackModuleType();
			strFind.ValidateStack = raw::ValidateStack_StringFind;
			strFind.ValidateSelf = raw::Validate_Fail;
			strFind.CopyData = raw::CopyData_FourChar;
			strFind.FreeData = raw::FreeData_Single;

			module->ModuleAddType(strFind);
			if (parser != nullptr) { parser->WordsAdd("strFind"); }


			ist::IstackModuleType strSub = ist::IstackModuleType();
			strSub.ValidateStack = raw::ValidateStack_StringSub;
			strSub.ValidateSelf = raw::Validate_Fail;
			strSub.CopyData = raw::CopyData_String;
			strSub.FreeData = raw::FreeData_String;

			module->ModuleAddType(strSub);
			if (parser != nullptr) { parser->WordsAdd("strSub"); }


			ist::IstackModuleType strRep = ist::IstackModuleType();
			strRep.ValidateStack = raw::ValidateStack_StringReplace;
			strRep.ValidateSelf = raw::Validate_Fail;
			strRep.CopyData = raw::CopyData_String;
			strRep.FreeData = raw::FreeData_String;

			module->ModuleAddType(strRep);
			if (parser != nullptr) { parser->WordsAdd("strReplace"); }

		}
	}
}
