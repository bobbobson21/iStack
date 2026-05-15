#pragma once

#include <iostream>
#include <string>

#include "generics.h"

namespace ist
{
	namespace modules
	{
		enum modulePullErrorCodes : unsigned int
		{
			StackEmptyPullDataScope = 903,
			DataIsNullPullDataScope = 904,
			PullIsNullPullDataScope = 905,
			PullIsBeyondStackLengthScope = 906,
		};

		namespace raw
		{
			bool ValidateStack_PullData(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 1) { exec->ErrorSetCode(StackEmptyPullDataScope); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(DataIsNullPullDataScope); return false; }

				int popAmount = (*(int*)(dumpFrame->UnitTop().m_data)); //get amount
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();

				IstackStackFrame codeFrameBeta = IstackStackFrame();
				exec->CopyIstackFrameAndModuleDataFromAndTo((*dumpFrame->PipeGetCleared()), &codeFrameBeta); //access a copy of the scope

				for (int i = 0; i < popAmount; i++) //UnitPop untill amount is reached or untill failure
				{
					codeFrameBeta.UnitPop();
					if (codeFrameBeta.UnitLength() < 1) { exec->ErrorSetCode(PullIsBeyondStackLengthScope); return false; }
				}

				if (codeFrameBeta.UnitTop().m_data == nullptr) { exec->ErrorSetCode(PullIsNullPullDataScope); return false; } //is data valid

				IstackUnit newUnit = IstackUnit();
				exec->CopyUnitFromAndTo(codeFrameBeta.UnitTopPtr(), &newUnit);

				dumpFrame->UnitPush(newUnit); //copy data to dump
				exec->FreeFrame(&codeFrameBeta);


				return true;
			}

			bool ValidateStack_PullDataPop(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 1) { exec->ErrorSetCode(StackEmptyPullDataScope); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(DataIsNullPullDataScope); return false; }

				int popAmount = (*(int*)(dumpFrame->UnitTop().m_data)); //get amount
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();

				for (int i = 0; i < popAmount; i++) //UnitPop untill amount is reached or untill failure in live dump
				{
					(*dumpFrame->PipeGetCleared())->UnitPop();
					if ((*dumpFrame->PipeGetCleared())->UnitLength() < 1) { exec->ErrorSetCode(PullIsBeyondStackLengthScope); return false; }
				}

				if ((*dumpFrame->PipeGetCleared())->UnitTop().m_data == nullptr) { exec->ErrorSetCode(PullIsNullPullDataScope); return false; } //is data valid

				dumpFrame->UnitPush(dumpFrame->UnitTop()); //move data to dump
				(*dumpFrame->PipeGetCleared())->UnitPop();

				if ((*dumpFrame->PipeGetCleared())->UnitLength() > 0) //deletes the scope if theres no longer stuff inside
				{
					exec->FreeFrameRecursive((*dumpFrame->PipeGetCleared()));
					(*dumpFrame->PipeGetCleared()) = nullptr;
				}

				return true;
			}

		}

		void LoadPullDataModules(IstackModuleExacuteor* module, IstackLexParser* parser)
		{

			ist::IstackModuleType pullData = ist::IstackModuleType();
			pullData.ValidateStack = raw::ValidateStack_PullData;
			pullData.ValidateSelf = raw::ValidateSelf_Fail;

			module->ModuleAddType(pullData);
			if (parser != nullptr) { parser->WordsAdd("iPullDataFromScope"); }


			ist::IstackModuleType pullDataPop = ist::IstackModuleType();
			pullDataPop.ValidateStack = raw::ValidateStack_PullDataPop;
			pullDataPop.ValidateSelf = raw::ValidateSelf_Fail;

			module->ModuleAddType(pullDataPop);
			if (parser != nullptr) { parser->WordsAdd("iPullDataFromScopePop"); }

		}
	}
}
