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
			StackEmptyPullData = 903,
			DataIsNullPullData = 904,
			PullIsNullPullData = 905,
			PullIsBeyondStackLengthPullData = 906,

			StackFrameNotFound = 907,
		};

		namespace raw
		{
			bool ValidateStack_PullData(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 1) { exec->ErrorSetCode(StackEmptyPullData); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(DataIsNullPullData); return false; }

				int popAmount = (*(int*)(dumpFrame->UnitTop().m_data)); //get amount
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();

				IstackStackFrame codeFrameBeta = IstackStackFrame();
				exec->CopyIstackFrameAndModuleDataFromAndTo((*dumpFrame->PipeGetCleared()), &codeFrameBeta); //access a copy of the scope

				for (int i = 0; i < popAmount; i++) //UnitPop untill amount is reached or untill failure
				{
					codeFrameBeta.UnitPop();
					if (codeFrameBeta.UnitLength() < 1) { exec->ErrorSetCode(PullIsBeyondStackLengthPullData); return false; }
				}

				if (codeFrameBeta.UnitTop().m_data == nullptr) { exec->ErrorSetCode(PullIsNullPullData); return false; } //is data valid

				IstackUnit newUnit = IstackUnit();
				exec->CopyUnitFromAndTo(codeFrameBeta.UnitTopPtr(), &newUnit);

				dumpFrame->UnitPush(newUnit); //copy data to dump
				exec->FreeFrame(&codeFrameBeta);


				return true;
			}

			bool ValidateStack_PullDataPop(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 1) { exec->ErrorSetCode(StackEmptyPullData); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(DataIsNullPullData); return false; }

				int popAmount = (*(int*)(dumpFrame->UnitTop().m_data)); //get amount
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();

				for (int i = 0; i < popAmount; i++) //UnitPop untill amount is reached or untill failure in live dump
				{
					(*dumpFrame->PipeGetCleared())->UnitPop();
					if ((*dumpFrame->PipeGetCleared())->UnitLength() < 1) { exec->ErrorSetCode(PullIsBeyondStackLengthPullData); return false; }
				}

				if ((*dumpFrame->PipeGetCleared())->UnitTop().m_data == nullptr) { exec->ErrorSetCode(PullIsNullPullData); return false; } //is data valid

				dumpFrame->UnitPush(dumpFrame->UnitTop()); //move data to dump
				(*dumpFrame->PipeGetCleared())->UnitPop();

				if ((*dumpFrame->PipeGetCleared())->UnitLength() > 0) //deletes the scope if theres no longer stuff inside
				{
					exec->FreeFrameRecursive((*dumpFrame->PipeGetCleared()));
					(*dumpFrame->PipeGetCleared()) = nullptr;
				}

				return true;
			}

			bool ValidateStack_PushData(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 1) { exec->ErrorSetCode(StackEmptyPullData); return false; }
				if ((*dumpFrame->PipeGetCleared()) == nullptr) { exec->ErrorSetCode(StackFrameNotFound); return false; }

				ist::IstackUnit toTransfer = dumpFrame->UnitTop();
				dumpFrame->UnitPop();

				(*dumpFrame->PipeGetCleared())->UnitPush(toTransfer);

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


			ist::IstackModuleType pushData = ist::IstackModuleType();
			pushData.ValidateStack = raw::ValidateStack_PushData;
			pushData.ValidateSelf = raw::ValidateSelf_Fail;

			module->ModuleAddType(pushData);
			if (parser != nullptr) { parser->WordsAdd("PushDataIntoScope"); }

		}
	}
}
