#pragma once

#include <thread>
#include <string>
#include <mutex>
#include <map>

#include "generics.h"


namespace ist
{
	namespace modules
	{
		static std::mutex n_coreThreadMutex;
		static std::map<std::string, ist::IstackUnit> n_objectMap = std::map<std::string, ist::IstackUnit>();

		enum moduleThreadErrorCodes : unsigned int
		{
			PipeCantBeFoundThread = 801,
			StackEmptyIfThread = 802,
			DataIsNullIfThread = 803,

			StackLengthNotMetThread = 804,
			InvalidLocationThread = 805,
		};

		void Thread_ThreadOparator(IstackStackFrame* dumpFrame, IstackStackFrame* codeFrame, IstackModuleExacuteor* exec)
		{
			exec->ProcessExacuteFrame(dumpFrame, codeFrame);

			exec->FreeFrameRecursive(dumpFrame);
			exec->FreeFrameRecursive(codeFrame);
			exec->ModuleFreeTypes();

			delete exec;
			delete dumpFrame;
			delete codeFrame;
		}

		bool ValidateStack_Thread(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
		{
			if ((*dumpFrame->PipeGetCleared()) == nullptr) { exec->ErrorSetCode(PipeCantBeFoundThread); return false; }

			IstackModuleExacuteor* threadExecInstance = new IstackModuleExacuteor();
			exec->CopyModuleTypeDataFromAndTo(threadExecInstance);

			IstackStackFrame* threadDumpFrame = new IstackStackFrame();
			IstackStackFrame* threadCodeFrame = new IstackStackFrame();
			exec->CopyIstackFrameAndModuleDataFromAndTo((*dumpFrame->PipeGetCleared()), threadCodeFrame);


			std::thread* thread = new std::thread(Thread_ThreadOparator, threadDumpFrame, threadCodeFrame, threadExecInstance);
			(*data) = thread;


			return true;
		}

		void FreeData_Thread(void** data)
		{
			delete (std::thread*)(*data);
		}
		

		bool ValidateStack_Join(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
		{
			if (dumpFrame->UnitLength() < 1) { exec->ErrorSetCode(PipeCantBeFoundThread); return false; }
			if (dumpFrame->UnitLength() < 1) { exec->ErrorSetCode(StackEmptyIfThread); return false; }
			
			if (dumpFrame->UnitTop().m_data == nullptr) { exec->ErrorSetCode(DataIsNullIfThread); return false; }
			
			try
			{
				((std::thread*)(dumpFrame->UnitTop().m_data))->join();
			}
			catch (...)
			{
				exec->ErrorSetCode(DataIsNullIfThread);
				return false;
			}
		}

		bool ValidateStack_PushObject(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
		{
			if (dumpFrame->UnitLength() < 2) { exec->ErrorSetCode(StackLengthNotMetThread); return false; }

			std::string adress = "";

			try
			{
				adress = (*(std::string*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();
			}
			catch (...)
			{
				exec->ErrorSetCode(InvalidLocationThread); return false;
			}

			ist::IstackUnit unit = dumpFrame->UnitTop();
			dumpFrame->UnitPop();

			n_coreThreadMutex.lock();
			n_objectMap[adress] = unit;
			n_coreThreadMutex.unlock();
		}

		bool ValidateStack_PopObject(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
		{
			if (dumpFrame->UnitLength() < 1) { exec->ErrorSetCode(StackEmptyIfThread); return false; }

			std::string adress = "";

			try
			{
				adress = (*(std::string*)(dumpFrame->UnitTop().m_data));
				exec->FreeUnit(dumpFrame->UnitTopPtr());
				dumpFrame->UnitPop();
			}
			catch (...)
			{
				exec->ErrorSetCode(InvalidLocationThread); return false;
			}

			while (true)
			{
				n_coreThreadMutex.lock();

				if (n_objectMap.count(adress) > 0)
				{
					dumpFrame->UnitPush( n_objectMap[adress] );
					n_objectMap.erase(adress);
					return true;
				}

				n_coreThreadMutex.unlock();
			}

			return false;
		}

	}

	void LoadThreadModules(IstackModuleExacuteor* module, IstackLexParser* parser)
	{

	}
}