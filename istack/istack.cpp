// istack.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "istack.h"

ist::IstackStackFrame::IstackStackFrame(void)
{
}

ist::IstackStackFrame::~IstackStackFrame(void)
{
	delete[] m_stackUnits;
}

void ist::IstackStackFrame::PipeCreate()
{
	m_pipeTo = new IstackStackFrame();
}

void ist::IstackStackFrame::PipeSet(IstackStackFrame* otherFrame)
{
	if (m_pipeTo != nullptr) { m_pipeCleared = m_pipeTo; }
	m_pipeTo = otherFrame;
}

ist::IstackStackFrame** ist::IstackStackFrame::PipeGet(void)
{
	return &m_pipeTo;
}

ist::IstackStackFrame** ist::IstackStackFrame::PipeGetCleared(void)
{
	return &m_pipeCleared;
}

void ist::IstackStackFrame::PipeClear(void)
{
	m_pipeCleared = m_pipeTo;
	m_pipeTo = nullptr;
}


void ist::IstackStackFrame::PipePushDepthContext()
{
	m_pipeDepthContext = m_pipeDepthContext + 1;
}

void ist::IstackStackFrame::PipePopDepthContext()
{
	m_pipeDepthContext = m_pipeDepthContext - 1;
}

unsigned int ist::IstackStackFrame::PipeTopDepthContext()
{
	return m_pipeDepthContext;
}


void ist::IstackStackFrame::UnitPush(IstackUnit unit)
{
	if (m_pipeTo != nullptr)
	{
		m_pipeTo->UnitPush(unit);
		return;
	}

	if (m_stackIndex >= m_stackTotalLength)
	{
		IstackUnit* stackBuffer = new IstackUnit[m_stackTotalLength +1];

		if (m_stackUnits != nullptr)
		{
			memcpy(stackBuffer, m_stackUnits, sizeof(IstackUnit) * m_stackTotalLength);
			delete[] m_stackUnits;
		}

		m_stackUnits = stackBuffer;
		m_stackTotalLength = m_stackTotalLength + 1;
	}

	m_stackUnits[m_stackIndex] = unit;
	m_stackIndex = m_stackIndex + 1;
}

void ist::IstackStackFrame::UnitPop(void)
{
	if (m_pipeTo != nullptr)
	{
		m_pipeTo->UnitPop();
	}

	m_stackIndex = m_stackIndex - 1;
}

void ist::IstackStackFrame::UnitFlip(void)
{
	if (m_stackUnits == nullptr)
	{
		return;
	}

	IstackUnit* stackBuffer = new IstackUnit[m_stackIndex];
	
	for (unsigned int i = 0; i < m_stackIndex; i++)
	{
		stackBuffer[(m_stackIndex -1) -i] = m_stackUnits[i];
	}

	delete[] m_stackUnits;
	m_stackUnits = stackBuffer;
	m_stackTotalLength = m_stackIndex;
}


ist::IstackUnit ist::IstackStackFrame::UnitTop(void)
{
	if (m_pipeTo != nullptr)
	{
		return m_pipeTo->UnitTop();
	}

	return m_stackUnits[m_stackIndex - 1];
}

ist::IstackUnit* ist::IstackStackFrame::UnitTopPtr(void)
{
	if (m_pipeTo != nullptr)
	{
		return m_pipeTo->UnitTopPtr();
	}

	return &m_stackUnits[m_stackIndex - 1];
}

unsigned int ist::IstackStackFrame::UnitLength(void)
{
	if (m_pipeTo != nullptr)
	{
		return m_pipeTo->UnitLength();
	}

	return m_stackIndex;
}

void ist::IstackStackFrame::UnitAddToExtent(unsigned int addToTheAvalibleStackMemoryForNewPushes)
{
	IstackUnit* stackBuffer = new IstackUnit[m_stackTotalLength + addToTheAvalibleStackMemoryForNewPushes];

	if (m_stackUnits != nullptr)
	{
		memcpy(stackBuffer, m_stackUnits, sizeof(IstackUnit) * m_stackTotalLength);
		delete[] m_stackUnits;
	}

	m_stackUnits = stackBuffer;
	m_stackTotalLength = m_stackTotalLength +addToTheAvalibleStackMemoryForNewPushes;
}


void ist::IstackStackFrame::CopyIStackTo(IstackStackFrame* otherFrame)
{
	delete[] otherFrame->m_stackUnits;
	otherFrame->m_stackUnits = nullptr;

	otherFrame->m_stackIndex = m_stackIndex;
	otherFrame->m_stackTotalLength = m_stackIndex;

	if (m_stackUnits != nullptr)
	{
		otherFrame->m_stackUnits = new IstackUnit[m_stackIndex];

		memcpy(otherFrame->m_stackUnits, m_stackUnits, sizeof(IstackUnit) * m_stackIndex);
	}
}

void ist::IstackStackFrame::CopyPipeDataTo(IstackStackFrame* otherFrame)
{
	otherFrame->m_pipeTo = m_pipeTo;
	otherFrame->m_pipeCleared = m_pipeCleared;
	otherFrame->m_pipeDepthContext = m_pipeDepthContext;
}


void ist::IstackStackFrame::UnitFlush(void)
{
	if (m_stackUnits == nullptr)
	{
		return;
	}

	IstackUnit* stackBuffer = new IstackUnit[m_stackIndex];

	memcpy(stackBuffer, m_stackUnits, sizeof(IstackUnit) * m_stackIndex);
	delete[] m_stackUnits;

	m_stackUnits = stackBuffer;
	m_stackTotalLength = m_stackIndex;
}

void ist::IstackStackFrame::UnitFree(void)
{
	delete[] m_stackUnits;
	m_stackUnits = nullptr;

	m_stackIndex = 0;
	m_stackTotalLength = 0;
}




ist::IstackModuleExacuteor::IstackModuleExacuteor(unsigned int processDepth)
{
	m_maxProcessDepth = processDepth;
}

ist::IstackModuleExacuteor::IstackModuleExacuteor(void)
{
}

ist::IstackModuleExacuteor::~IstackModuleExacuteor(void)
{
	delete[] m_arrayModules;
}


void ist::IstackModuleExacuteor::ErrorSetCode(unsigned int code)
{
	m_errorCode = code;
}

unsigned int ist::IstackModuleExacuteor::ErrorGetCode()
{
	return m_errorCode;
}

bool ist::IstackModuleExacuteor::ErrorProcessDepthOverflowed()
{
	return (m_currentProcessDepth > m_maxProcessDepth);
}


bool ist::IstackModuleExacuteor::ProcessExacuteFrame(IstackStackFrame* frameIn, IstackStackFrame* frameOut)
{
	if (m_currentProcessDepth > m_maxProcessDepth) //oh no you overflow how much exacution is allowed didnt you
	{
		return false;
	}

	m_currentProcessDepth = m_currentProcessDepth + 1; //increeses the depth

	while (frameIn->UnitLength() > 0) //proccess code untll theres non left to process
	{
		IstackUnit* unit = frameIn->UnitTopPtr();

		if ((*frameOut->PipeGet()) == nullptr)
		{
			if (unit->m_modualTypeCode >= m_arrayModulesLength)
			{
				if (m_currentProcessDepth <= m_maxProcessDepth)  //decresse incase failure shouldnt cause crash
				{ 
					m_currentProcessDepth = m_currentProcessDepth - 1;  //we only decreese if we are bellow the depth so errors are reported correctly
				}

				return false;
			}

			if (m_arrayModules[unit->m_modualTypeCode].ValidateStack != nullptr && m_arrayModules[unit->m_modualTypeCode].ValidateStack(frameOut, this, &unit->m_data) == false)
			{
				if (m_currentProcessDepth <= m_maxProcessDepth) //decresse incase failure shouldnt cause crash
				{
					m_currentProcessDepth = m_currentProcessDepth - 1;
				}

				return false;
			}

			if (m_arrayModules[unit->m_modualTypeCode].ValidateSelf == nullptr || m_arrayModules[unit->m_modualTypeCode].ValidateSelf(frameOut, this, &unit->m_data) == true)
			{
				frameOut->UnitPush(frameIn->UnitTop());
			}
		}
		else
		{
			if (m_arrayModules[unit->m_modualTypeCode].ValidateSelfPiped == nullptr || m_arrayModules[unit->m_modualTypeCode].ValidateSelfPiped(frameOut, this, &unit->m_data) == true)
			{
				frameOut->UnitPush(frameIn->UnitTop());
			}
		}

		frameIn->UnitPop();
	}

	if (m_currentProcessDepth <= m_maxProcessDepth) //decresse because we reached the end of the funtion
	{
		m_currentProcessDepth = m_currentProcessDepth - 1;
	}

	return true;
}

bool ist::IstackModuleExacuteor::ProcessExacuteFrameAsIfPiped(IstackStackFrame* frameIn, IstackStackFrame* frameOut)
{
	if (m_currentProcessDepth > m_maxProcessDepth) //oh no you overflow how much exacution is allowed didnt you
	{
		return false;
	}

	m_currentProcessDepth = m_currentProcessDepth + 1;

	while (frameIn->UnitLength() > 0) //proccess code untll theres non left to process
	{
		IstackUnit* unit = frameIn->UnitTopPtr();

		if (m_arrayModules[unit->m_modualTypeCode].ValidateSelfPiped == nullptr || m_arrayModules[unit->m_modualTypeCode].ValidateSelfPiped(frameOut, this, &unit->m_data) == true)
		{
			frameOut->UnitPush(frameIn->UnitTop());
		}
	}

	m_currentProcessDepth = m_currentProcessDepth - 1;

	return true;
}

void ist::IstackModuleExacuteor::ProcessFlushDepthContext()
{
	m_currentProcessDepth = 0;
}


void ist::IstackModuleExacuteor::FreeFrameRecursive(IstackStackFrame* frame, bool doDeleteOfPipeFramesAsWell)
{
	if ((*frame->PipeGet()) != nullptr)
	{
		FreeFrameRecursive((*frame->PipeGet()), doDeleteOfPipeFramesAsWell);
		
		if (doDeleteOfPipeFramesAsWell == true)
		{
			delete (IstackStackFrame*)(*frame->PipeGet());
			(*frame->PipeGet()) = nullptr;
		}
	}

	if ((*frame->PipeGetCleared()) != nullptr)
	{
		FreeFrameRecursive((*frame->PipeGetCleared()), doDeleteOfPipeFramesAsWell);

		if (doDeleteOfPipeFramesAsWell == true)
		{
			delete (IstackStackFrame*)(*frame->PipeGetCleared());
			(*frame->PipeGetCleared()) = nullptr;
		}
	}

	FreeFrame(frame);
}

void ist::IstackModuleExacuteor::FreeFrame(IstackStackFrame* frame)
{
	while (frame->UnitLength() > 0)
	{
		FreeUnit(frame->UnitTopPtr());
		frame->UnitPop();
	}

	frame->UnitFree();
}

void ist::IstackModuleExacuteor::FreeUnit(IstackUnit* unit)
{
	if (m_arrayModules[unit->m_modualTypeCode].FreeData != nullptr)
	{
		m_arrayModules[unit->m_modualTypeCode].FreeData(&unit->m_data);
	}
}


void ist::IstackModuleExacuteor::CopyIstackFrameAndModuleDataFromAndTo(IstackStackFrame* copyFrom, IstackStackFrame* copyTo)
{
	FreeFrame(copyTo);

	IstackUnit* transferBuffer = new IstackUnit[copyFrom->UnitLength()];
	IstackStackFrame transferFrame = IstackStackFrame();
	unsigned int transferIndex = copyFrom->UnitLength() -1;
	
	copyFrom->CopyIStackTo(&transferFrame);

	while (transferFrame.UnitLength() > 0 && transferIndex >= 0)
	{
		transferBuffer[transferIndex] = transferFrame.UnitTop();
		transferIndex--;

		transferFrame.UnitPop();
	}

	for (unsigned int i = 0; i < copyFrom->UnitLength(); i++)
	{
		IstackUnit newUnit = IstackUnit();
		CopyUnitFromAndTo(&transferBuffer[i], &newUnit);

		copyTo->UnitPush(newUnit);
	}

	transferFrame.UnitFree();
	delete[] transferBuffer;
}

void ist::IstackModuleExacuteor::CopyUnitFromAndTo(IstackUnit* copyFrom, IstackUnit* copyTo)
{
	if (m_arrayModules[copyFrom->m_modualTypeCode].CopyData != nullptr)
	{
		m_arrayModules[copyFrom->m_modualTypeCode].CopyData(&copyFrom->m_data, &copyTo->m_data);
	}
	else
	{
		copyTo->m_data = copyFrom->m_data;
	}

	copyTo->m_modualTypeCode = copyFrom->m_modualTypeCode;
}


unsigned int ist::IstackModuleExacuteor::ModuleAdd(IstackModuleType module)
{

	IstackModuleType* modulesBuffer = new IstackModuleType[m_arrayModulesLength +1];

	if (m_arrayModules != nullptr)
	{
		memcpy(modulesBuffer, m_arrayModules, sizeof(IstackModuleType) * m_arrayModulesLength);
		delete[] m_arrayModules;
	}

	modulesBuffer[m_arrayModulesLength] = module;
	m_arrayModules = modulesBuffer;

	m_arrayModulesLength = m_arrayModulesLength + 1;
	return m_arrayModulesLength -1;
}

ist::IstackModuleType ist::IstackModuleExacuteor::ModuleGet(unsigned int moduleIndex)
{
	return m_arrayModules[moduleIndex];
}

ist::IstackModuleType* ist::IstackModuleExacuteor::ModuleGetPtr(unsigned int moduleIndex)
{
	return &m_arrayModules[moduleIndex];
}

unsigned int ist::IstackModuleExacuteor::ModuleGetCount(void)
{
	return m_arrayModulesLength;
}



void ist::IstackLexParser::PushChar(char charter)
{
	if (m_f_CommentParse(m_inputStringBuffer, m_inputStringBufferIndex, charter, this) == false)
	{
		return;
	}

	if (charter == '\n') { return; }
	if (charter == '\r') { return; }
	if (charter == '\t') { return; }
	if (charter == '\0') { return; }

	if (m_scopeInputDepth == 0)
	{
		if (charter == ' ') { return; }
	}
	
	if (charter == '(') { m_scopeInputDepth = m_scopeInputDepth + 1; }
	if (charter == '{') { m_scopeInputDepth = m_scopeInputDepth + 1; }
	if (charter == '[') { m_scopeInputDepth = m_scopeInputDepth + 1; }

	if (charter == ')' && m_scopeInputDepth -1 < m_scopeInputDepth) { m_scopeInputDepth = m_scopeInputDepth - 1; }
	if (charter == '}' && m_scopeInputDepth - 1 < m_scopeInputDepth) { m_scopeInputDepth = m_scopeInputDepth - 1; }
	if (charter == ']' && m_scopeInputDepth - 1 < m_scopeInputDepth) { m_scopeInputDepth = m_scopeInputDepth - 1; }

	if (m_inputStringBufferIndex >= m_maxInputStringBufferLength) { return; }

	if (charter == ';') //every symbol has this is the end
	{
		unsigned int lagestSymbolMatchSize = 0;
		IstackUnit unitToPush = IstackUnit();

		for (unsigned int i = 0; i < m_arrayKeywordsLength; i++) //loop thougth words
		{
			bool sucessfulMatch = true;
			unsigned int symbolLength = strnlen(m_arrayKeywords[i], m_maxInputStringBufferLength);

			for (size_t o = 0; o < symbolLength; o++)
			{
				if (m_inputStringBuffer[o] != m_arrayKeywords[i][o]) //word dosent match input buffers contents
				{
					sucessfulMatch = false; //failure
					break;
				}
			}

			if (sucessfulMatch == true && symbolLength > lagestSymbolMatchSize) //word dose match but is it the best match
			{
				lagestSymbolMatchSize = symbolLength; //it is the bestest match so far but save resuts for later matches
				unitToPush.m_modualTypeCode = i;				
			}
		}

		if (lagestSymbolMatchSize > 0) //was there any matches
		{
			bool isSucessfulAtParsingData = true;

			if (m_f_DataParseFunc != nullptr)
			{
				isSucessfulAtParsingData = m_f_DataParseFunc(m_inputStringBuffer, m_inputStringBufferIndex, &unitToPush);
			}

			if (isSucessfulAtParsingData == true) //can parse data
			{
				m_outputFrame->UnitPush(unitToPush);
			}
			else //no so fail
			{
				m_isParsingSucessful = false;
			}
		}
		else //no matches so fail
		{
			m_isParsingSucessful = false;
		}

		m_scopeInputDepth = 0;
		m_inputStringBufferIndex = 0;
		return;
	}

	m_inputStringBuffer[m_inputStringBufferIndex] = charter;
	m_inputStringBufferIndex = m_inputStringBufferIndex + 1;
}


ist::IstackLexParser::IstackLexParser(unsigned int maxBufferSize)
{
	m_maxInputStringBufferLength = maxBufferSize;
	m_inputStringBuffer = new char[m_maxInputStringBufferLength];
}

ist::IstackLexParser::IstackLexParser(void)
{
	m_inputStringBuffer = new char[m_maxInputStringBufferLength];
}

ist::IstackLexParser::~IstackLexParser(void)
{
	delete[] m_inputStringBuffer;

	for (unsigned int i = 0; i < m_arrayKeywordsLength; i++)
	{
		delete[] m_arrayKeywords[i];
	}

	delete[] m_arrayKeywords;
}


void ist::IstackLexParser::SetDataParse(bool(*DataParseFunc)(char*, unsigned int, IstackUnit*))
{
	m_f_DataParseFunc = DataParseFunc;
}

void ist::IstackLexParser::SetCommentParse(bool(*CommentParse)(char*, unsigned int, char, IstackLexParser*))
{
	m_f_CommentParse = CommentParse;
}

void ist::IstackLexParser::SetFrame(IstackStackFrame* frame)
{
	m_outputFrame = frame;
}

void ist::IstackLexParser::AddWord(const char* keyword)
{
	char** modulesBuffer = new char*[m_arrayKeywordsLength +1];

	if (m_arrayKeywords != nullptr)
	{
		memcpy(modulesBuffer, m_arrayKeywords, sizeof(char*) * m_arrayKeywordsLength);
		delete[] m_arrayKeywords;
	}

	modulesBuffer[m_arrayKeywordsLength] = new char[strnlen(keyword, m_maxInputStringBufferLength) +1];
	memcpy(modulesBuffer[m_arrayKeywordsLength], keyword, strnlen(keyword, m_maxInputStringBufferLength));
	modulesBuffer[m_arrayKeywordsLength][strnlen(keyword, m_maxInputStringBufferLength)] = '\0';

	m_arrayKeywords = modulesBuffer;
	m_arrayKeywordsLength = m_arrayKeywordsLength + 1;
}

void ist::IstackLexParser::InputParseStringIntoFrame(const char* string)
{
	for (size_t i = 0; i < strlen(string); i++)
	{
		PushChar(string[i]);
	}
}

void ist::IstackLexParser::operator<<(char* charters)
{
	for (size_t i = 0; i < strlen(charters); i++)
	{
		PushChar(charters[i]);
	}
}

void ist::IstackLexParser::operator<<(const char* charters)
{
	for (size_t i = 0; i < strlen(charters); i++)
	{
		PushChar(charters[i]);
	}
}

void ist::IstackLexParser::operator<<(char charter)
{
	PushChar(charter);
}

bool ist::IstackLexParser::ErrorIsParsingUnsucessful()
{
	return !m_isParsingSucessful;
}

bool ist::IstackLexParser::ErrorInputBufferOverflowed()
{
	return (m_inputStringBufferIndex >= m_maxInputStringBufferLength);
}

void ist::IstackLexParser::InputFlushBuffer()
{
	m_isParsingSucessful = true;
	m_inputStringBufferIndex = 0;
}



bool ist::includedStyles::CppCommentStyle(char* inputBuffer, unsigned int inputLength, char newChar, ist::IstackLexParser* parserToModify)
{
	if (inputLength >= 2 && inputBuffer[0] == '/' && inputBuffer[1] == '/')
	{
		if (newChar == '\n' || newChar == '\r')
		{
			parserToModify->InputFlushBuffer();
		}

		return false;
	}

	if (inputLength >= 2 && inputBuffer[0] == '/' && inputBuffer[1] == '*')
	{
		if (inputBuffer[inputLength - 2] == '*' && inputBuffer[inputLength - 1] == '/')
		{
			parserToModify->InputFlushBuffer();
			return true;
		}

		if (newChar != '*' && newChar != '/')
		{
			return false;
		}
	}

	return true;
}

bool ist::includedStyles::LuaCommentStyle(char* inputBuffer, unsigned int inputLength, char newChar, ist::IstackLexParser* parserToModify)
{
	if (inputLength >= 2 && inputBuffer[0] == '-' && inputBuffer[1] == '-')
	{
		if (inputLength < 4 || inputBuffer[2] != '[' || inputBuffer[3] != '[')
		{
			if (newChar == '\n' || newChar == '\r')
			{
				parserToModify->InputFlushBuffer();
			}
		}

		if (inputBuffer[inputLength - 2] == ']' && inputBuffer[inputLength - 1] == ']')
		{
			parserToModify->InputFlushBuffer();
			return true;
		}

		if (newChar != '[' && newChar != ']')
		{
			return false;
		}
	}

	return true;
}
