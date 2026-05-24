// Compiler.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//created a transfer data module

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
#include "IstackModules/exec.h"
#include "IstackModules/pulldata.h"
#include "IstackModules/function.h"

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
	parser.FrameSet(&codeScope);
	parser.ParseSetDataFunc(compiler::DataParse); //a function for this cant be included in the dll as it requires data minulation that should only be done on the programs end
	parser.ParseSetCommentFunc(ist::DefParseFuncs::CppCommentStyle); //but this can be done tho
	parser.ParseSetStringFunc(ist::DefParseFuncs::LuaStringStyle);

	ist::IstackModuleExacuteor exec = ist::IstackModuleExacuteor();

	//load modules
	ist::modules::LoadVarModules(&exec, &parser); //0 -> 7
	ist::modules::LoadManipulationModules(&exec, &parser, 0); //7 -> 15
	ist::modules::LoadConversionModules(&exec, &parser, 0); //15 -> 25
	ist::modules::LoadLoopsModules(&exec, &parser, 0); //25 -> 30
	ist::modules::LoadPullDataModules(&exec, &parser); //30 -> 33 //last
	ist::modules::LoadSystemModules(&exec, &parser); //33 -> 35
	ist::modules::LoadScopeModules(&exec, &parser); //35 -> 37
	ist::modules::LoadLogicModules(&exec, &parser); //37 -> 48
	ist::modules::LoadMathModules(&exec, &parser); //48 -> 58
	ist::modules::LoadExecModules(&exec, &parser); //58 -> 61
	ist::modules::LoadIoModules(&exec, &parser); //61 -> 67
	ist::modules::LoadFunctionModules(&exec, &parser); //67 -> 71

	if (exec.ErrorSymbolMemoryOverflowed() == true || parser.ErrorSymbolMemoryOverflowed() == true) //you would need 4,294,967,295 modules all of which would need at lest 4,294,967,295 unique functions but they could have two or four unique functions so this would be very difficult to pull of and maybe even impossible
	{
		std::cout << "error: exec || parser: to many module types loaded into istack and im honestly inpresed you managed to pull that off" << std::endl;
	}

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
	ist::modules::KillFunctionModule(&exec);

	exec.FreeFrameRecursive(&codeScope);
	exec.FreeFrameRecursive(&dump);

	return 0;
}

