#pragma once

#include <fstream>
#include <iostream>
#include <string>

#include "generics.h"


namespace ist
{
	namespace modules
	{
		enum moduleFileErrorCodes : unsigned int
		{
			CantAccessFileFile = 1001,
			FileDoseNotExsitFile = 1002,

			FileNameInvalidFile = 1003,
			UnableToWriteContentsToFileFile = 1004,
		};

		namespace raw
		{
			bool ValidateStack_FileRead(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				std::string fileContents = "";
				std::string filePath = "";

				//obtain file path
				if ((*data) != nullptr)
				{
					try
					{
						filePath = (*(std::string*)(*data));
					}
					catch (...)
					{
						exec->ErrorSetCode(FileNameInvalidFile);
						return false;
					}
				}
				else
				{
					try
					{
						filePath = (*(std::string*)(dumpFrame->UnitTop().m_data));
						exec->FreeUnit(dumpFrame->UnitTopPtr());
						dumpFrame->UnitPop();
					}
					catch (...)
					{
						exec->ErrorSetCode(FileNameInvalidFile);
						return false;
					}
				}

				//obtain file contents
				std::ifstream fileReader = std::ifstream();
				fileReader.open(filePath, std::ios::binary);

				if (fileReader.good() == false) { exec->ErrorSetCode(FileDoseNotExsitFile); return false; }
				if (fileReader.is_open() == false) { exec->ErrorSetCode(CantAccessFileFile); return false; }

				while (fileReader.good() == true && fileReader.good() == true && fileReader.eof() == false)
				{
					char letter = '\0';
					fileReader >> letter;

					fileContents = fileContents + letter;
				}

				fileReader.close();

				delete (*data);

				(*data) = new std::string;
				(*(std::string*)(*data)) = fileContents;

				return true;
			}

			bool ValidateStack_FileWrite(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				std::string fileContents = "";
				std::string filePath = "";

				//obtain file path
				if ((*data) != nullptr)
				{
					try
					{
						filePath = (*(std::string*)(*data));
					}
					catch (...)
					{
						exec->ErrorSetCode(FileNameInvalidFile);
						return false;
					}
				}
				else
				{
					try
					{
						filePath = (*(std::string*)(dumpFrame->UnitTop().m_data));
						exec->FreeUnit(dumpFrame->UnitTopPtr());
						dumpFrame->UnitPop();
					}
					catch (...)
					{
						exec->ErrorSetCode(FileNameInvalidFile);
						return false;
					}
				}

				delete data;

				//provide file contents
				try
				{
					fileContents = (*(std::string*)(dumpFrame->UnitTop().m_data));
					exec->FreeUnit(dumpFrame->UnitTopPtr());
					dumpFrame->UnitPop();
				}
				catch (...)
				{
					exec->ErrorSetCode(UnableToWriteContentsToFileFile);
					return false;
				}

				std::fstream fileWriter = std::fstream();
				fileWriter.open(filePath, std::ios::out | std::ios::in | std::ios::trunc);

				if (fileWriter.good() == false) { exec->ErrorSetCode(FileDoseNotExsitFile); return false; }
				if (fileWriter.is_open() == false) { exec->ErrorSetCode(CantAccessFileFile); return false; }

				for (size_t i = 0; i < fileContents.length(); i++)
				{
					fileWriter << fileContents[i];
				}

				fileWriter.close();

				return true;
			}
		
			bool ValidateStack_FileAppend(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				std::string fileContents = "";
				std::string filePath = "";

				//obtain file path
				if ((*data) != nullptr)
				{
					try
					{
						filePath = (*(std::string*)(*data));
					}
					catch (...)
					{
						exec->ErrorSetCode(FileNameInvalidFile);
						return false;
					}
				}
				else
				{
					try
					{
						filePath = (*(std::string*)(dumpFrame->UnitTop().m_data));
						exec->FreeUnit(dumpFrame->UnitTopPtr());
						dumpFrame->UnitPop();
					}
					catch (...)
					{
						exec->ErrorSetCode(FileNameInvalidFile);
						return false;
					}
				}

				delete data;

				//provide file contents
				try
				{
					fileContents = (*(std::string*)(dumpFrame->UnitTop().m_data));
					exec->FreeUnit(dumpFrame->UnitTopPtr());
					dumpFrame->UnitPop();
				}
				catch (...)
				{
					exec->ErrorSetCode(UnableToWriteContentsToFileFile);
					return false;
				}

				std::fstream fileWriter = std::fstream();
				fileWriter.open(filePath, std::ios::out | std::ios::in | std::ios::app);

				if (fileWriter.good() == false) { exec->ErrorSetCode(FileDoseNotExsitFile); return false; }
				if (fileWriter.is_open() == false) { exec->ErrorSetCode(CantAccessFileFile); return false; }

				for (size_t i = 0; i < fileContents.length(); i++)
				{
					fileWriter << fileContents[i];
				}

				fileWriter.close();

				return true;
			}
		}

		void LoadFileModules(IstackModuleExacuteor* module, IstackLexParser* parser)
		{
			ist::IstackModuleType fileRead = ist::IstackModuleType();
			fileRead.ValidateStack = raw::ValidateStack_FileRead;
			fileRead.ValidateSelf = raw::ValidateSelf_Fail;
			fileRead.CopyData = raw::CopyData_String;
			fileRead.FreeData = raw::FreeData_String;

			module->ModuleAddType(fileRead);
			if (parser != nullptr) { parser->WordsAdd("FileRead"); }


			ist::IstackModuleType fileWrite = ist::IstackModuleType();
			fileWrite.ValidateStack = raw::ValidateStack_FileWrite;
			fileWrite.ValidateSelf = raw::ValidateSelf_Fail;
			fileWrite.CopyData = raw::CopyData_String;
			fileWrite.FreeData = raw::FreeData_String;

			module->ModuleAddType(fileWrite);
			if (parser != nullptr) { parser->WordsAdd("FileWrite"); }


			ist::IstackModuleType fileAppend = ist::IstackModuleType();
			fileAppend.ValidateStack = raw::ValidateStack_FileAppend;
			fileAppend.ValidateSelf = raw::ValidateSelf_Fail;
			fileAppend.CopyData = raw::CopyData_String;
			fileAppend.FreeData = raw::FreeData_String;

			module->ModuleAddType(fileAppend);
			if (parser != nullptr) { parser->WordsAdd("FileAppend"); }
		}
	}
}
