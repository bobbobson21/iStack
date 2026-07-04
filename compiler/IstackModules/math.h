#pragma once

#include <string>

#include "generics.h"

namespace ist
{
	namespace modules
	{
		enum moduleMathErrorCodes : unsigned int
		{
			StackElementSizeNotMetMath = 601,
			StackElementFirstInvalidMath = 602,
			StackElementSecondInvalidMath = 603,
		};

		namespace raw
		{
			bool ValidateStack_IntAdd(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 2) { exec->ErrorSetCode(StackElementSizeNotMetMath); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StackElementFirstInvalidMath); return false; }

				int A = (*(int*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();

				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StackElementSecondInvalidMath); return false; }

				int B = (*(int*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();


				delete (*data);

				(*data) = new int;
				(*(int*)(*data)) = (A + B);

				return true;
			}

			bool ValidateStack_IntTake(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 2) { exec->ErrorSetCode(StackElementSizeNotMetMath); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StackElementFirstInvalidMath); return false; }

				int A = (*(int*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();

				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StackElementSecondInvalidMath); return false; }

				int B = (*(int*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();


				delete (*data);

				(*data) = new int;
				(*(int*)(*data)) = (A - B);

				return true;
			}

			bool ValidateStack_IntTimes(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 2) { exec->ErrorSetCode(StackElementSizeNotMetMath); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StackElementFirstInvalidMath); return false; }

				int A = (*(int*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();

				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StackElementSecondInvalidMath); return false; }

				int B = (*(int*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();


				delete (*data);

				(*data) = new int;
				(*(int*)(*data)) = (A * B);

				return true;
			}

			bool ValidateStack_IntDivide(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 2) { exec->ErrorSetCode(StackElementSizeNotMetMath); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StackElementFirstInvalidMath); return false; }

				int A = (*(int*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();

				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StackElementSecondInvalidMath); return false; }

				int B = (*(int*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();


				delete (*data);

				(*data) = new int;
				(*(int*)(*data)) = (A / B);

				return true;
			}

			bool ValidateStack_IntMod(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 2) { exec->ErrorSetCode(StackElementSizeNotMetMath); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StackElementFirstInvalidMath); return false; }

				int A = (*(int*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();

				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StackElementSecondInvalidMath); return false; }

				int B = (*(int*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();


				delete (*data);

				(*data) = new int;
				(*(int*)(*data)) = (A % B);

				return true;
			}

			bool ValidateStack_IntPow(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 2) { exec->ErrorSetCode(StackElementSizeNotMetMath); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StackElementFirstInvalidMath); return false; }

				int A = (*(int*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();

				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StackElementSecondInvalidMath); return false; }

				int B = (*(int*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();


				delete (*data);
				(*data) = new int;
				(*(int*)(*data)) = (int)std::pow((int)(A), (int)(B));

				return true;
			}


			bool ValidateStack_FloatAdd(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 2) { exec->ErrorSetCode(StackElementSizeNotMetMath); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StackElementFirstInvalidLogic); return false; }

				float A = (*(float*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();

				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StackElementSecondInvalidMath); return false; }

				float B = (*(float*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();


				delete (*data);
				(*data) = new float;
				(*(float*)(*data)) = (A + B);

				return true;
			}

			bool ValidateStack_FloatTake(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 2) { exec->ErrorSetCode(StackElementSizeNotMetMath); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StackElementFirstInvalidMath); return false; }

				float A = (*(float*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();

				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StackElementSecondInvalidMath); return false; }

				float B = (*(float*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();


				delete (*data);
				(*data) = new float;
				(*(float*)(*data)) = (A - B);

				return true;
			}

			bool ValidateStack_FloatTimes(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 2) { exec->ErrorSetCode(StackElementSizeNotMetMath); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StackElementFirstInvalidMath); return false; }

				float A = (*(float*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();

				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StackElementSecondInvalidMath); return false; }

				float B = (*(float*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();


				delete (*data);
				(*data) = new float;
				(*(float*)(*data)) = (A * B);

				return true;
			}

			bool ValidateStack_FloatDivide(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 2) { exec->ErrorSetCode(StackElementSizeNotMetMath); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StackElementFirstInvalidMath); return false; }

				float A = (*(float*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();

				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StackElementSecondInvalidMath); return false; }

				float B = (*(float*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();


				delete (*data);
				(*data) = new float;
				(*(float*)(*data)) = (A / B);

				return true;
			}


			bool ValidateStack_FloatSin(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 1) { exec->ErrorSetCode(StackElementSizeNotMetMath); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StackElementFirstInvalidMath); return false; }

				float A = (*(float*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();

				delete (*data);
				(*data) = new float;
				(*(float*)(*data)) = std::sinf(A);

				return true;
			}

			bool ValidateStack_FloatCos(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 1) { exec->ErrorSetCode(StackElementSizeNotMetMath); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StackElementFirstInvalidMath); return false; }

				float A = (*(float*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();

				delete (*data);
				(*data) = new float;
				(*(float*)(*data)) = std::cosf(A);

				return true;
			}

			bool ValidateStack_FloatAbs(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 1) { exec->ErrorSetCode(StackElementSizeNotMetMath); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StackElementFirstInvalidMath); return false; }

				float A = (*(float*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();

				delete (*data);
				(*data) = new float;
				(*(float*)(*data)) = std::abs(A);

				return true;
			}

			bool ValidateStack_FloatFloor(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 1) { exec->ErrorSetCode(StackElementSizeNotMetMath); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StackElementFirstInvalidMath); return false; }

				float A = (*(float*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();

				delete (*data);
				(*data) = new float;
				(*(float*)(*data)) = std::floorf(A);

				return true;
			}

			bool ValidateStack_FloatCeil(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 1) { exec->ErrorSetCode(StackElementSizeNotMetMath); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StackElementFirstInvalidMath); return false; }

				float A = (*(float*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();

				delete (*data);
				(*data) = new float;
				(*(float*)(*data)) = std::ceilf(A);

				return true;
			}

			bool ValidateStack_FloatRandomRange(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 1) { exec->ErrorSetCode(StackElementSizeNotMetMath); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StackElementFirstInvalidMath); return false; }

				float A = (*(float*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();


				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StackElementSecondInvalidMath); return false; }

				float B = (*(float*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();

				float randomNumber = A;
				
				if (A < B)
				{
					int decimalDetail = RAND_MAX;
					randomNumber = randomNumber + (rand() % (int)(std::floorf(B - A)));
					randomNumber = randomNumber + (((float)(rand() % decimalDetail)) / ((float)(decimalDetail)));
				}

				delete (*data);
				(*data) = new float;
				(*(float*)(*data)) = randomNumber;

				return true;
			}

			bool ValidateStack_IntSetSeed(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				if (dumpFrame->UnitLength() < 1) { exec->ErrorSetCode(StackElementSizeNotMetMath); return false; }
				if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(StackElementFirstInvalidMath); return false; }

				int A = (*(int*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();

				srand(A);

				return true;
			}
		}

		void LoadMathModules(IstackModuleExacuteor* module, IstackLexParser* parser)
		{
			ist::IstackModuleType AddF = ist::IstackModuleType();
			AddF.ValidateStack = raw::ValidateStack_FloatAdd;
			AddF.ValidateSelf = raw::Validate_Success;
			AddF.FreeData = raw::FreeData_Single;
			AddF.CopyData = raw::CopyData_FourChar;

			module->ModuleAddType(AddF);
			if (parser != nullptr) { parser->WordsAdd("f+"); }


			ist::IstackModuleType TakeF = ist::IstackModuleType();
			TakeF.ValidateStack = raw::ValidateStack_FloatTake;
			TakeF.ValidateSelf = raw::Validate_Success;
			TakeF.FreeData = raw::FreeData_Single;
			TakeF.CopyData = raw::CopyData_FourChar;

			module->ModuleAddType(TakeF);
			if (parser != nullptr) { parser->WordsAdd("f-"); }


			ist::IstackModuleType TimesF = ist::IstackModuleType();
			TimesF.ValidateStack = raw::ValidateStack_FloatTimes;
			TimesF.ValidateSelf = raw::Validate_Success;
			TimesF.FreeData = raw::FreeData_Single;
			TimesF.CopyData = raw::CopyData_FourChar;

			module->ModuleAddType(TimesF);
			if (parser != nullptr) { parser->WordsAdd("f*"); }


			ist::IstackModuleType DivideF = ist::IstackModuleType();
			DivideF.ValidateStack = raw::ValidateStack_FloatDivide;
			DivideF.ValidateSelf = raw::Validate_Success;
			DivideF.FreeData = raw::FreeData_Single;
			DivideF.CopyData = raw::CopyData_FourChar;

			module->ModuleAddType(DivideF);
			if (parser != nullptr) { parser->WordsAdd("f/"); }


			ist::IstackModuleType AddI = ist::IstackModuleType();
			AddI.ValidateStack = raw::ValidateStack_IntAdd;
			AddI.ValidateSelf = raw::Validate_Success;
			AddI.FreeData = raw::FreeData_Single;
			AddI.CopyData = raw::CopyData_FourChar;

			module->ModuleAddType(AddI);
			if (parser != nullptr) { parser->WordsAdd("i+"); }


			ist::IstackModuleType TakeI = ist::IstackModuleType();
			TakeI.ValidateStack = raw::ValidateStack_IntTake;
			TakeI.ValidateSelf = raw::Validate_Success;
			TakeI.FreeData = raw::FreeData_Single;
			TakeI.CopyData = raw::CopyData_FourChar;

			module->ModuleAddType(TakeI);
			if (parser != nullptr) { parser->WordsAdd("i-"); }


			ist::IstackModuleType TimesI = ist::IstackModuleType();
			TimesI.ValidateStack = raw::ValidateStack_IntTimes;
			TimesI.ValidateSelf = raw::Validate_Success;
			TimesI.FreeData = raw::FreeData_Single;
			TimesI.CopyData = raw::CopyData_FourChar;

			module->ModuleAddType(TimesI);
			if (parser != nullptr) { parser->WordsAdd("i*"); }


			ist::IstackModuleType DivideI = ist::IstackModuleType();
			DivideI.ValidateStack = raw::ValidateStack_IntDivide;
			DivideI.ValidateSelf = raw::Validate_Success;
			DivideI.FreeData = raw::FreeData_Single;
			DivideI.CopyData = raw::CopyData_FourChar;

			module->ModuleAddType(DivideI);
			if (parser != nullptr) { parser->WordsAdd("i/"); }


			ist::IstackModuleType ModI = ist::IstackModuleType();
			ModI.ValidateStack = raw::ValidateStack_IntMod;
			ModI.ValidateSelf = raw::Validate_Success;
			ModI.FreeData = raw::FreeData_Single;
			ModI.CopyData = raw::CopyData_FourChar;

			module->ModuleAddType(ModI);
			if (parser != nullptr) { parser->WordsAdd("i%"); }


			ist::IstackModuleType PowI = ist::IstackModuleType();
			PowI.ValidateStack = raw::ValidateStack_IntPow;
			PowI.ValidateSelf = raw::Validate_Success;
			PowI.FreeData = raw::FreeData_Single;
			PowI.CopyData = raw::CopyData_FourChar;

			module->ModuleAddType(PowI);
			if (parser != nullptr) { parser->WordsAdd("i^"); }


			ist::IstackModuleType sinF = ist::IstackModuleType();
			sinF.ValidateStack = raw::ValidateStack_FloatSin;
			sinF.ValidateSelf = raw::Validate_Success;
			sinF.FreeData = raw::FreeData_Single;
			sinF.CopyData = raw::CopyData_FourChar;

			module->ModuleAddType(sinF);
			if (parser != nullptr) { parser->WordsAdd("fSinf"); }


			ist::IstackModuleType cosF = ist::IstackModuleType();
			cosF.ValidateStack = raw::ValidateStack_FloatCos;
			cosF.ValidateSelf = raw::Validate_Success;
			cosF.FreeData = raw::FreeData_Single;
			cosF.CopyData = raw::CopyData_FourChar;

			module->ModuleAddType(cosF);
			if (parser != nullptr) { parser->WordsAdd("fCosf"); }


			ist::IstackModuleType absF = ist::IstackModuleType();
			absF.ValidateStack = raw::ValidateStack_FloatAbs;
			absF.ValidateSelf = raw::Validate_Success;
			absF.FreeData = raw::FreeData_Single;
			absF.CopyData = raw::CopyData_FourChar;

			module->ModuleAddType(absF);
			if (parser != nullptr) { parser->WordsAdd("fAbsf"); }


			ist::IstackModuleType floorF = ist::IstackModuleType();
			floorF.ValidateStack = raw::ValidateStack_FloatFloor;
			floorF.ValidateSelf = raw::Validate_Success;
			floorF.FreeData = raw::FreeData_Single;
			floorF.CopyData = raw::CopyData_FourChar;

			module->ModuleAddType(floorF);
			if (parser != nullptr) { parser->WordsAdd("fFloorf"); }


			ist::IstackModuleType ceilF = ist::IstackModuleType();
			ceilF.ValidateStack = raw::ValidateStack_FloatCeil;
			ceilF.ValidateSelf = raw::Validate_Success;
			ceilF.FreeData = raw::FreeData_Single;
			ceilF.CopyData = raw::CopyData_FourChar;

			module->ModuleAddType(ceilF);
			if (parser != nullptr) { parser->WordsAdd("fCeilf"); }


			ist::IstackModuleType RandomRangeF = ist::IstackModuleType();
			RandomRangeF.ValidateStack = raw::ValidateStack_FloatRandomRange;
			RandomRangeF.ValidateSelf = raw::Validate_Success;
			RandomRangeF.FreeData = raw::FreeData_Single;
			RandomRangeF.CopyData = raw::CopyData_FourChar;

			module->ModuleAddType(RandomRangeF);
			if (parser != nullptr) { parser->WordsAdd("ffRandomRangef"); }


			ist::IstackModuleType ISetRandomSeed = ist::IstackModuleType();
			ISetRandomSeed.ValidateStack = raw::ValidateStack_IntSetSeed;
			ISetRandomSeed.ValidateSelf = raw::Validate_Success;
			ISetRandomSeed.FreeData = raw::FreeData_Single;
			ISetRandomSeed.CopyData = raw::CopyData_FourChar;

			module->ModuleAddType(ISetRandomSeed);
			if (parser != nullptr) { parser->WordsAdd("iSetRandomSeed"); }
		}
	}
}