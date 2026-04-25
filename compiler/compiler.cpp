// Compiler.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <cctype>
#include <fstream>

#include "IstackModules/io.h"
#include "IstackModules/scope.h"
#include "IstackModules/var.h"
#include "IstackModules/logic.h"
#include "IstackModules/math.h"
#include "IstackModules/conversion.h"
#include "IstackModules/loops.h"
#include "IstackModules/manipulation.h"
#include "IstackModules/system.h"

#include "compileConfig.h"
#include "compileParsering.h"

#include "istack/istack.h"


int main(int argc, char* argv[])
{
	std::string filePath = "";

	for (int i = 1; i < argc; i++)
	{
		for (unsigned int o = 0; argv[i][o] != '\0'; o++)
		{
			filePath = filePath + argv[i][o];
		}
	}

	//set up contents
	ist::IstackStackFrame codeScope = ist::IstackStackFrame();
	ist::IstackStackFrame dump = ist::IstackStackFrame();

	ist::IstackLexParser parser = ist::IstackLexParser();
	parser.SetFrame(&codeScope);
	parser.SetDataParse(compiler::DataParse); //a function for this cant be included in the dll as it requires data minulation that should only be done on the programs end
	parser.SetCommentParse(ist::includedCommentStyles::CppCommentStyle); //but this can be done tho

	ist::IstackModuleExacuteor exec = ist::IstackModuleExacuteor();
	
	//load modules
	ist::modules::LoadVarModules(&exec, &parser);
	ist::modules::LoadManipulationModules(&exec, &parser, 0); //last
	ist::modules::LoadConversionModules(&exec, &parser, 0);
	ist::modules::LoadLoopsModules(&exec, &parser, 0);
	ist::modules::LoadSystemModules(&exec, &parser);
	ist::modules::LoadScopeModules(&exec, &parser);
	ist::modules::LoadLogicModules(&exec, &parser);
	ist::modules::LoadMathModules(&exec, &parser);
	ist::modules::LoadIoModules(&exec, &parser);


	//read in contents of istack file
	bool canExacuteCodeFrame = compiler::CompileFunc(filePath, &codeScope, &dump, &parser, &exec);

	if (canExacuteCodeFrame == true)
	{
		//exacute istack code
		bool success = exec.ProcessExacuteFrame(&codeScope, &dump);

		//error repoarting
		if (success == false)
		{
			if (exec.ErrorProcessDepthOverflowed() == true)
			{
				std::cout << "error: exec: recursive proccess depth overflowed (to many scopes exacuting)" << std::endl;
			}
			else
			{
				std::cout << "error: exec: stack exacition failed with error code: " << exec.ErrorGetCode() << std::endl;
			}
		}
	}

	//free data
	exec.FreeFrame(&codeScope);
	exec.FreeFrameRecursive(&dump); //both are true so that all memory is freed without the process being stoped by errors

	return 0;
}

