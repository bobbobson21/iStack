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

void ist::IstackStackFrame::PipeFree()
{
	delete m_pipeTo;
	m_pipeTo = nullptr;
}

void ist::IstackStackFrame::PipeClearedFree()
{
	delete m_pipeCleared;
	m_pipeCleared = nullptr;
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
	m_processDepthMax = processDepth;
}

ist::IstackModuleExacuteor::IstackModuleExacuteor(void)
{
}

ist::IstackModuleExacuteor::~IstackModuleExacuteor(void)
{
	ModuleFreeTypes();
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
	return (m_processDepthCurrent > m_processDepthMax);
}

bool ist::IstackModuleExacuteor::ErrorSymbolMemoryOverflowed()
{
	return m_errorSymbolMemoryOverflowed;
}


bool ist::IstackModuleExacuteor::ProcessExacuteFrame(IstackStackFrame* frameIn, IstackStackFrame* frameOut)
{
	if (m_processDepthCurrent > m_processDepthMax) //oh no you overflow how much exacution is allowed didnt you
	{
		return false;
	}

	m_processDepthCurrent = m_processDepthCurrent + 1; //increeses the depth

	while (frameIn->UnitLength() > 0) //proccess code untll theres non left to process
	{
		IstackUnit* unit = frameIn->UnitTopPtr();

		if ((*frameOut->PipeGet()) == nullptr)
		{
			if (unit->m_modualTypeCode >= m_moduleTypesArrayLength)
			{
				if (m_processDepthCurrent <= m_processDepthMax)  //decresse incase failure shouldnt cause crash
				{ 
					m_processDepthCurrent = m_processDepthCurrent - 1;  //we only decreese if we are bellow the depth so errors are reported correctly
				}

				return false;
			}

			if (m_moduleTypesArray[unit->m_modualTypeCode].ValidateStack != nullptr && m_moduleTypesArray[unit->m_modualTypeCode].ValidateStack(frameOut, this, &unit->m_data) == false)
			{
				if (m_processDepthCurrent <= m_processDepthMax) //decresse incase failure shouldnt cause crash
				{
					m_processDepthCurrent = m_processDepthCurrent - 1;
				}

				return false;
			}

			if (m_moduleTypesArray[unit->m_modualTypeCode].ValidateExecution != nullptr && m_moduleTypesArray[unit->m_modualTypeCode].ValidateExecution(frameOut, this, &unit->m_data) == false)
			{
				if (m_processDepthCurrent <= m_processDepthMax) //decresse incase exit shouldnt cause crash
				{
					m_processDepthCurrent = m_processDepthCurrent - 1;
				}

				return true;
			}

			if (m_moduleTypesArray[unit->m_modualTypeCode].ValidateSelf == nullptr || m_moduleTypesArray[unit->m_modualTypeCode].ValidateSelf(frameOut, this, &unit->m_data) == true)
			{
				frameOut->UnitPush(frameIn->UnitTop());
			}
			else
			{
				FreeUnit(frameIn->UnitTopPtr());
			}
		}
		else
		{
			if (m_moduleTypesArray[unit->m_modualTypeCode].ValidateSelfPiped == nullptr || m_moduleTypesArray[unit->m_modualTypeCode].ValidateSelfPiped(frameOut, this, &unit->m_data) == true)
			{
				frameOut->UnitPush(frameIn->UnitTop());
			}
		}

		frameIn->UnitPop();
	}

	if (m_processDepthCurrent <= m_processDepthMax) //decresse because we reached the end of the funtion
	{
		m_processDepthCurrent = m_processDepthCurrent - 1;
	}

	return true;
}


void ist::IstackModuleExacuteor::ProcessFlushDepthContext()
{
	m_processDepthCurrent = 0;
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
	if (m_moduleTypesArray[unit->m_modualTypeCode].FreeData != nullptr)
	{
		m_moduleTypesArray[unit->m_modualTypeCode].FreeData(&unit->m_data);
	}
}


void ist::IstackModuleExacuteor::CopyUnitFromAndTo(IstackUnit* copyFrom, IstackUnit* copyTo)
{
	if (m_moduleTypesArray[copyFrom->m_modualTypeCode].CopyData != nullptr)
	{
		m_moduleTypesArray[copyFrom->m_modualTypeCode].CopyData(&copyFrom->m_data, &copyTo->m_data);
	}
	else
	{
		copyTo->m_data = copyFrom->m_data;
	}

	copyTo->m_modualTypeCode = copyFrom->m_modualTypeCode;
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


unsigned int ist::IstackModuleExacuteor::ModuleAddType(IstackModuleType module)
{
	if (m_moduleTypesArrayLength + 1 < m_moduleTypesArrayLength)
	{
		m_errorSymbolMemoryOverflowed = true;
		return -1; //it will be highest positive value and that will indercate something wnt wrong
	}

	IstackModuleType* modulesBuffer = new IstackModuleType[m_moduleTypesArrayLength +1];

	if (m_moduleTypesArray != nullptr)
	{
		memcpy(modulesBuffer, m_moduleTypesArray, sizeof(IstackModuleType) * m_moduleTypesArrayLength);
		delete[] m_moduleTypesArray;
	}

	modulesBuffer[m_moduleTypesArrayLength] = module;
	m_moduleTypesArray = modulesBuffer;

	m_moduleTypesArrayLength = m_moduleTypesArrayLength + 1;
	return m_moduleTypesArrayLength -1;
}

ist::IstackModuleType ist::IstackModuleExacuteor::ModuleGetType(unsigned int moduleIndex)
{
	return m_moduleTypesArray[moduleIndex];
}

ist::IstackModuleType* ist::IstackModuleExacuteor::ModuleGetTypePtr(unsigned int moduleIndex)
{
	return &m_moduleTypesArray[moduleIndex];
}

unsigned int ist::IstackModuleExacuteor::ModuleGetTypeCount(void)
{
	return m_moduleTypesArrayLength;
}

void ist::IstackModuleExacuteor::ModuleFreeTypes(void)
{
	delete[] m_moduleTypesArray;

	m_moduleTypesArrayLength = 0;
	m_moduleTypesArray = nullptr;
}

void ist::IstackModuleExacuteor::CopyModuleTypeDataFromAndTo(IstackModuleExacuteor* otherExec)
{
	delete[] otherExec->m_moduleTypesArray;
	otherExec->m_moduleTypesArrayLength = m_moduleTypesArrayLength;

	otherExec->m_moduleTypesArray = new IstackModuleType[otherExec->m_moduleTypesArrayLength];

	for (unsigned int i = 0; i < otherExec->m_moduleTypesArrayLength; i++)
	{
		otherExec->m_moduleTypesArray[i] = m_moduleTypesArray[i];
	}
}

void ist::IstackModuleExacuteor::CopyModuleProcessDepthDataFromAndTo(IstackModuleExacuteor* otherExec)
{
	otherExec->m_processDepthCurrent = m_processDepthCurrent;
	otherExec->m_processDepthMax = m_processDepthMax;
}



void ist::IstackLexParser::PushChar(char charter)
{
	if (m_f_ParseFuncComment(m_inputStringBuffer, m_inputStringBufferIndex, charter, this) == false) //comment handling
	{
		return;
	}

	if (m_inputStringBufferIndex >= m_inputStringMaxBufferLength) //safty
	{
		return;
	}

	bool isOutsideOfString = m_f_ParseFuncString(m_inputStringBuffer, m_inputStringBufferIndex, charter);

	if (isOutsideOfString == true)
	{
		if (charter == '\n') { return; } //outside a string these charters are ingored but inside one this is not the case
		if (charter == '\r') { return; }
		if (charter == '\t') { return; }
		if (charter == '\0') { return; }

		if (charter == ' ') { return; }

		if (charter == ';') //every symbol has this is the end and this is also allowed in strings
		{
			unsigned int lagestSymbolMatchSize = 0;
			IstackUnit unitToPush = IstackUnit();

			for (unsigned int i = 0; i < m_keywordsArrayLength; i++) //loop thougth words
			{
				bool sucessfulMatch = true;
				unsigned int symbolLength = (unsigned int)strnlen(m_keywordsArray[i], m_inputStringMaxBufferLength);

				for (size_t o = 0; o < symbolLength; o++)
				{
					if (m_inputStringBuffer[o] != m_keywordsArray[i][o]) //word dosent match input buffers contents
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

				if (m_f_ParseFuncData != nullptr)
				{
					isSucessfulAtParsingData = m_f_ParseFuncData(m_inputStringBuffer, m_inputStringBufferIndex, &unitToPush);
				}

				if (isSucessfulAtParsingData == true) //can parse data
				{
					m_outputFrame->UnitPush(unitToPush);
				}
				else //no so fail
				{
					m_errorIsParsingUnsucessful = true;
				}
			}
			else //no matches so fail
			{
				m_errorIsParsingUnsucessful = true;
			}

			m_inputStringBufferIndex = 0;
			return;
		}
	}

	m_inputStringBuffer[m_inputStringBufferIndex] = charter;
	m_inputStringBufferIndex = m_inputStringBufferIndex + 1;
}


void ist::IstackLexParser::FreeInputBuffer(void)
{
	delete[] m_inputStringBuffer;

	m_inputStringBuffer = nullptr;
	m_inputStringMaxBufferLength = 0;
	m_inputStringBufferIndex = 0;
}

void ist::IstackLexParser::CreateInputBuffer(unsigned int inputBufferSize)
{
	m_inputStringMaxBufferLength = inputBufferSize;
	m_inputStringBuffer = new char[m_inputStringMaxBufferLength];
}


ist::IstackLexParser::IstackLexParser(unsigned int maxBufferSize)
{
	CreateInputBuffer(maxBufferSize);
}

ist::IstackLexParser::IstackLexParser(void)
{
	CreateInputBuffer(1024);
}

ist::IstackLexParser::~IstackLexParser(void)
{
	FreeInputBuffer();
	WordsFree();
}


void ist::IstackLexParser::ParseSetDataFunc(bool(*dataParseFunc)(char*, unsigned int, IstackUnit*))
{
	m_f_ParseFuncData = dataParseFunc;
}

void ist::IstackLexParser::ParseSetCommentFunc(bool(*commentParse)(char*, unsigned int, char, IstackLexParser*))
{
	m_f_ParseFuncComment = commentParse;
}

void ist::IstackLexParser::ParseSetStringFunc(bool(*stringParse)(char*, unsigned int, char))
{
	m_f_ParseFuncString = stringParse;
}


void ist::IstackLexParser::FrameSet(IstackStackFrame* frame)
{
	m_outputFrame = frame;
}

void ist::IstackLexParser::WordsAdd(const char* keyword)
{
	if (m_keywordsArrayLength + 1 < m_keywordsArrayLength)
	{
		m_errorSymbolMemoryOverflowed = true;
		return;
	}

	char** modulesBuffer = new char*[m_keywordsArrayLength +1];

	if (m_keywordsArray != nullptr)
	{
		memcpy(modulesBuffer, m_keywordsArray, sizeof(char*) * m_keywordsArrayLength);
		delete[] m_keywordsArray;
	}

	modulesBuffer[m_keywordsArrayLength] = new char[strnlen(keyword, m_inputStringMaxBufferLength) +1];
	memcpy(modulesBuffer[m_keywordsArrayLength], keyword, strnlen(keyword, m_inputStringMaxBufferLength));
	modulesBuffer[m_keywordsArrayLength][strnlen(keyword, m_inputStringMaxBufferLength)] = '\0';

	m_keywordsArray = modulesBuffer;
	m_keywordsArrayLength = m_keywordsArrayLength + 1;
}

void ist::IstackLexParser::WordsFree(void)
{
	for (unsigned int i = 0; i < m_keywordsArrayLength; i++)
	{
		delete[] m_keywordsArray[i];
	}

	delete[] m_keywordsArray;

	m_keywordsArray = nullptr;
	m_keywordsArrayLength = 0;
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
	return m_errorIsParsingUnsucessful;
}

bool ist::IstackLexParser::ErrorInputBufferOverflowed()
{
	return (m_inputStringBufferIndex >= m_inputStringMaxBufferLength);
}

bool ist::IstackLexParser::ErrorSymbolMemoryOverflowed()
{
	return m_errorSymbolMemoryOverflowed;
}

void ist::IstackLexParser::InputFlushBuffer()
{
	m_errorIsParsingUnsucessful = false;
	m_inputStringBufferIndex = 0;
}



bool ist::DefParseFuncs::CppCommentStyle(char* inputBuffer, unsigned int inputLength, char newChar, ist::IstackLexParser* parserToModify)
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

bool ist::DefParseFuncs::LuaStringStyle(char* inputBuffer, unsigned int inputLength, char newChar)
{
	static char currentStringState = '\0';

	if (inputLength > 0)
	{
		char lastCharAdded = inputBuffer[inputLength - 1];

		if (lastCharAdded == '"' && currentStringState == '"') { currentStringState = '\0'; }
		else if (lastCharAdded == '"' && currentStringState == '\0') { currentStringState = '"'; }

		if (lastCharAdded == '\'' && currentStringState == '\'') { currentStringState = '\0'; }
		else if (lastCharAdded == '\'' && currentStringState == '\0') { currentStringState = '\''; }
	}

	return (currentStringState == '\0');
}

