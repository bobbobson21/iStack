#pragma once

#include <iostream>
#include <string>

#include "generics.h"

namespace ist
{
	namespace modules
	{
		namespace raw
		{
			bool ValidateSelf_ScopeStart(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if ((*dumpFrame->PipeGetCleared()) != nullptr)
				{
					exec->FreeFrameRecursive((*dumpFrame->PipeGetCleared()));
					(*dumpFrame->PipeGetCleared()) = nullptr;
				}

				dumpFrame->PipeCreate();
				dumpFrame->PipePushDepthContext();
				return false;
			}

			bool ValidateSelfPiped_ScopeStart(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				dumpFrame->PipePushDepthContext();
				return true;
			}


			bool ValidateSelfPiped_ScopeEndFliped(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				dumpFrame->PipePopDepthContext();

				if (dumpFrame->PipeTopDepthContext() == 0)
				{
					dumpFrame->PipeClear();
					(*dumpFrame->PipeGetCleared())->UnitFlip();
					return false;
				}

				return true;
			}
		}

		void LoadScopeModules(IstackModuleExacuteor* module, IstackLexParser* parser)
		{
			ist::IstackModuleType scopeStart = ist::IstackModuleType();
			scopeStart.ValidateSelf = raw::ValidateSelf_ScopeStart;
			scopeStart.ValidateSelfPiped = raw::ValidateSelfPiped_ScopeStart;

			module->ModuleAddType(scopeStart);
			if (parser != nullptr) { parser->WordsAdd("}"); }


			ist::IstackModuleType scopeEndFliped = ist::IstackModuleType();
			scopeEndFliped.ValidateSelf = raw::ValidateSelf_Fail;
			scopeEndFliped.ValidateSelfPiped = raw::ValidateSelfPiped_ScopeEndFliped;

			module->ModuleAddType(scopeEndFliped);
			if (parser != nullptr) { parser->WordsAdd("{"); }
		}
	}
}
