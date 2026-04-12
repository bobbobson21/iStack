// Compiler.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>

#include "IstackModules/io.h"
#include "IstackModules/scope.h"
#include "IstackModules/var.h"
#include "IstackModules/logic.h"

#include "istack/istack.h"

void DataParse(char* string, unsigned int stringLength, ist::IstackUnit* unit)
{
	std::string stringProper = "";
	bool inParseMode = false;

	for (size_t i = 0; i < stringLength; i++)
	{
		if (string[i] == ')') { inParseMode = false; }

		if (inParseMode == true)
		{
			stringProper = stringProper + string[i];
		}

		if (string[i] == '(') { inParseMode = true; }
	}

	if (stringProper == "")
	{
		return;
	}

	if (stringProper == "true") 
	{
		unit->m_data = new bool; 
		(*((bool*)unit->m_data)) = true;
		return; 
	}

	if (stringProper == "false") 
	{
		unit->m_data = new bool;
		(*((bool*) unit->m_data)) = false;
		return;
	}

	try
	{
		float data = std::stof(stringProper);

		unit->m_data = new float();
		(*((float*)unit->m_data)) = data;
	}
	catch (...)
	{
		try
		{
			int data = std::stof(stringProper);

			unit->m_data = new int();
			(*((int*)unit->m_data)) = data;
		}
		catch (...)
		{
			unit->m_data = new std::string();
			(*((std::string*)unit->m_data)) = stringProper;
		}
	}
}

int main(int argc, char* argv[])
{
	std::string filePath = "TestCode.ist";

	for (int i = 1; i < argc; i++)
	{
		for (unsigned int o = 0; argv[i][o] != '\0'; o++)
		{
			filePath = filePath + argv[i][o];
		}
	}

	//std::cout << "filePath: " << argc << ": " << filePath << std::endl;

	ist::IstackStackFrame codeScope = ist::IstackStackFrame();
	ist::IstackStackFrame dump = ist::IstackStackFrame();

	ist::IstackLexParser parser = ist::IstackLexParser();
	parser.SetFrame(&codeScope);
	parser.SetDataParse(DataParse);

	ist::IstackModuleExacuteor exec = ist::IstackModuleExacuteor();
	
	ist::modules::LoadVarModules(&exec, &parser);
	ist::modules::LoadScopeModules(&exec, &parser);
	ist::modules::LoadIoModules(&exec, &parser);
	ist::modules::LoadLogicModules(&exec, &parser);


	//istack exacutes from bottom to top so the instruction lowest down will be doe first the the one highest up will be done last and parser is what compiles the code so exec can run it
	// istack code here ///////////////////////////////////////////////////////////////////

	parser << "Exec();";
	parser << "{;";
	parser << "   SelfPrint(c);";

	//parser << "   Exec();";
	//parser << "   Exec();";

	parser << "   If;";
	parser << "   i==;";
	parser << "   FourByte(2);";
	parser << "   FourByte(2);";
	parser << "   {;";
	parser << "      PopPrint();";
	parser << "      String(wowo);";
	parser << "   };";

	parser << "   SelfPrint(a);";
	parser << "};";
	parser << "SelfPrint(===============================);";
	parser << "SelfPrint(a);";
	parser << "SelfPrint(b);";
	parser << "SelfPrint(c);";

	//////////////////////////////////////////////////////////////////////////////////////

	exec.ExacuteFrame(&codeScope, &dump);
	
	exec.FreeFrameRecursive(&codeScope);
	exec.FreeFrame(&dump);

	return 0;
}

