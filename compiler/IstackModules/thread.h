#pragma once

#include <thread>
#include <string>
#include <mutex>
#include <map>
#include <vector>

#include "generics.h"


namespace ist
{
	namespace modules
	{
		enum moduleThreadErrorCodes : unsigned int
		{
			PipeCantBeFoundThread = 801,
			StackEmptyIfThread = 802,
			DataIsNullIfThread = 803,

			StackLengthNotMetThread = 804,
			InvalidLocationThread = 805,
			ThreadsCouldNotBeFoundThread = 806,
		};
		
		namespace raw
		{
			struct StackThreadObject
			{
				std::thread* threadCore = nullptr;
				bool* isFinished = nullptr;
			};


			static std::mutex n_coreThreadMutex;
			static std::map<std::string, ist::IstackUnit> n_objectMap = std::map<std::string, ist::IstackUnit>();
			static std::vector<StackThreadObject> n_threads = std::vector<StackThreadObject>();


			void Thread_ThreadOparator(IstackStackFrame* dumpFrame, IstackStackFrame* codeFrame, IstackModuleExacuteor* exec, bool* isDone)
			{
				exec->ProcessExacuteFrame(dumpFrame, codeFrame);

				exec->FreeFrameRecursive(dumpFrame);
				exec->FreeFrameRecursive(codeFrame);
				exec->ModuleFreeTypes();

				(*isDone) = true;

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


				bool* isFinished = new bool{false};

				std::thread* thread = new std::thread(Thread_ThreadOparator, threadDumpFrame, threadCodeFrame, threadExecInstance, isFinished);
				(*data) = thread;

				StackThreadObject threadObj = StackThreadObject();
				threadObj.threadCore = thread;
				threadObj.isFinished = isFinished;

				n_threads.push_back(threadObj);

				return true;
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
						dumpFrame->UnitPush(n_objectMap[adress]);
						n_objectMap.erase(adress);
						
						n_coreThreadMutex.unlock();

						return true;
					}

					n_coreThreadMutex.unlock();
				}

				return false;
			}

			bool ValidateStack_WaitForThreadCompleteion(IstackStackFrame* dumpFrame, IstackModuleExacuteor* exec, void** data)
			{
				bool dontExit = true;

				if (n_threads.size() <= 0)
				{
					exec->ErrorSetCode(ThreadsCouldNotBeFoundThread);
					return false;
				}

				while (dontExit)
				{
					dontExit = false;

					for (size_t i = 0; i < n_threads.size(); i++)
					{
						if ((*n_threads[i].isFinished) == false)
						{
							dontExit = true;
							break;
						}
					}
				}

				return true;
			}
		}


		void LoadThreadModules(IstackModuleExacuteor* module, IstackLexParser* parser)
		{
			ist::IstackModuleType threadExec = ist::IstackModuleType();
			threadExec.ValidateStack = raw::ValidateStack_Thread;
			threadExec.ValidateSelf = raw::ValidateSelf_Success;

			module->ModuleAddType(threadExec);
			if (parser != nullptr) { parser->WordsAdd("ThreadExec"); }


			ist::IstackModuleType threadJoin = ist::IstackModuleType();
			threadJoin.ValidateStack = raw::ValidateStack_Join;
			threadJoin.ValidateSelf = raw::ValidateSelf_Success;

			module->ModuleAddType(threadJoin);
			if (parser != nullptr) { parser->WordsAdd("ThreadJoin"); }


			ist::IstackModuleType threadPush = ist::IstackModuleType();
			threadPush.ValidateStack = raw::ValidateStack_PushObject;
			threadPush.ValidateSelf = raw::ValidateSelf_Success;

			module->ModuleAddType(threadPush);
			if (parser != nullptr) { parser->WordsAdd("ThreadPush"); }

			ist::IstackModuleType threadPop = ist::IstackModuleType();
			threadPop.ValidateStack = raw::ValidateStack_PopObject;
			threadPop.ValidateSelf = raw::ValidateSelf_Success;

			module->ModuleAddType(threadPop);
			if (parser != nullptr) { parser->WordsAdd("ThreadPop"); }
		}

		void FreeAllThreads()
		{
			for (size_t i = 0; i < raw::n_threads.size(); i++)
			{
				delete raw::n_threads[i].isFinished;
				delete raw::n_threads[i].threadCore;
			}

			raw::n_threads.clear();
		}
	}
}