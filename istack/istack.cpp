// istack.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "istack.h"

#include <memory>

ist::IstackStackFrame::IstackStackFrame(void)
{
}

ist::IstackStackFrame::~IstackStackFrame(void)
{
	delete[] m_stackUnits;
}

void ist::IstackStackFrame::SetPipe(IstackStackFrame* OtherFrame)
{
	if (m_pipeTo != nullptr) { m_pipeCleared = m_pipeTo; }
	m_pipeTo = OtherFrame;
}

ist::IstackStackFrame** ist::IstackStackFrame::GetPipe(void)
{
	return &m_pipeTo;
}

ist::IstackStackFrame** ist::IstackStackFrame::GetClearedPipe(void)
{
	return &m_pipeCleared;
}

void ist::IstackStackFrame::ClearPipe(void)
{
	m_pipeCleared = m_pipeTo;
	m_pipeTo = nullptr;
}


void ist::IstackStackFrame::PushPipeDepthContext()
{
	m_pipeDepthContext = m_pipeDepthContext + 1;
}

void ist::IstackStackFrame::PopPipeDepthContext()
{
	m_pipeDepthContext = m_pipeDepthContext - 1;
}

unsigned int ist::IstackStackFrame::TopPipeDepthContext()
{
	return m_pipeDepthContext;
}


void ist::IstackStackFrame::Push(IstackUnit unit)
{
	if (m_pipeTo != nullptr)
	{
		m_pipeTo->Push(unit);
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

void ist::IstackStackFrame::Pop(void)
{
	if (m_pipeTo != nullptr)
	{
		m_pipeTo->Pop();
	}

	m_stackIndex = m_stackIndex - 1;
}

void ist::IstackStackFrame::Flip(void)
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


ist::IstackUnit ist::IstackStackFrame::Top(void)
{
	if (m_pipeTo != nullptr)
	{
		return m_pipeTo->Top();
	}

	return m_stackUnits[m_stackIndex - 1];
}

ist::IstackUnit* ist::IstackStackFrame::TopPtr(void)
{
	if (m_pipeTo != nullptr)
	{
		return m_pipeTo->TopPtr();
	}

	return &m_stackUnits[m_stackIndex - 1];
}

unsigned int ist::IstackStackFrame::Length(void)
{
	if (m_pipeTo != nullptr)
	{
		return m_pipeTo->Length();
	}

	return m_stackIndex;
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


void ist::IstackStackFrame::Flush(void)
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

void ist::IstackStackFrame::Free(void)
{
	if (m_pipeTo != nullptr)
	{
		m_pipeTo->Free();
		return;
	}

	delete[] m_stackUnits;
	m_stackUnits = nullptr;

	m_stackIndex = 0;
	m_stackTotalLength = 0;
}




ist::IstackModuleExacuteor::IstackModuleExacuteor(void)
{
}

ist::IstackModuleExacuteor::~IstackModuleExacuteor(void)
{
	delete[] m_arrayModules;
}

bool ist::IstackModuleExacuteor::ExacuteFrame(IstackStackFrame* frameIn, IstackStackFrame* frameOut)
{
	m_pointOfFailure = 0;

	while (frameIn->Length() > 0)
	{
		IstackUnit* unit = frameIn->TopPtr();

		if ((*frameOut->GetPipe()) == nullptr)
		{
			if (unit->m_modualTypeCode >= m_arrayModulesLength)
			{
				m_pointOfFailure = frameIn->Length() -1;
				return false;
			}

			if (m_arrayModules[unit->m_modualTypeCode].ValidateStack != nullptr && m_arrayModules[unit->m_modualTypeCode].ValidateStack(frameOut, this, &unit->m_data) == false)
			{
				m_pointOfFailure = frameIn->Length() -1;
				return false;
			}

			if (m_arrayModules[unit->m_modualTypeCode].ValidateSelf == nullptr || m_arrayModules[unit->m_modualTypeCode].ValidateSelf(frameOut, this, &unit->m_data) == true)
			{
				frameOut->Push(frameIn->Top());
			}
		}
		else
		{
			if (m_arrayModules[unit->m_modualTypeCode].ValidateSelfPiped == nullptr || m_arrayModules[unit->m_modualTypeCode].ValidateSelfPiped(frameOut, this, &unit->m_data) == true)
			{
				frameOut->Push(frameIn->Top());
			}
		}

		frameIn->Pop();
	}

	return true;
}

unsigned int ist::IstackModuleExacuteor::GetPointOfFailure()
{
	return m_pointOfFailure;
}


void ist::IstackModuleExacuteor::FreeFrameRecursive(IstackStackFrame* frame, bool doDeleteOfPipeFramesAsWell)
{
	if ((*frame->GetPipe()) != nullptr)
	{
		FreeFrameRecursive((*frame->GetPipe()), doDeleteOfPipeFramesAsWell);
		
		if (doDeleteOfPipeFramesAsWell == true)
		{
			delete (*frame->GetPipe());
			(*frame->GetPipe()) = nullptr;
		}
	}

	if ((*frame->GetClearedPipe()) != nullptr)
	{
		FreeFrameRecursive((*frame->GetClearedPipe()), doDeleteOfPipeFramesAsWell);

		if (doDeleteOfPipeFramesAsWell == true)
		{
			delete (*frame->GetClearedPipe());
			(*frame->GetClearedPipe()) = nullptr;
		}
	}

	FreeFrame(frame);
}

void ist::IstackModuleExacuteor::FreeFrame(IstackStackFrame* frame)
{
	while (frame->Length() > 0)
	{
		FreeUnit(frame->TopPtr());
		frame->Pop();
	}

	frame->Free();
}

void ist::IstackModuleExacuteor::FreeUnit(IstackUnit* unit)
{
	if (m_arrayModules[unit->m_modualTypeCode].FreeData != nullptr)
	{
		m_arrayModules[unit->m_modualTypeCode].FreeData(&unit->m_data);
	}
}


void ist::IstackModuleExacuteor::CopyIstackAndModuleDataFromAndTo(IstackStackFrame* copyFrom, IstackStackFrame* copyTo)
{
	FreeFrame(copyTo);

	IstackUnit* transferBuffer = new IstackUnit[copyFrom->Length()];
	IstackStackFrame transferFrame = IstackStackFrame();
	unsigned int transferIndex = copyFrom->Length() -1;
	
	copyFrom->CopyIStackTo(&transferFrame);

	while (transferFrame.Length() > 0 && transferIndex >= 0)
	{
		transferBuffer[transferIndex] = transferFrame.Top();
		transferIndex--;

		transferFrame.Pop();
	}

	for (unsigned int i = 0; i < copyFrom->Length(); i++)
	{
		IstackUnit newUnit = IstackUnit();
		
		newUnit.m_modualTypeCode = transferBuffer[i].m_modualTypeCode;
		CopyUnitFromAndTo(&transferBuffer[i], &newUnit);

		copyTo->Push(newUnit);
	}
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
}


unsigned int ist::IstackModuleExacuteor::AddModule(IstackModuleType module)
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

ist::IstackModuleType ist::IstackModuleExacuteor::GetModule(unsigned int moduleIndex)
{
	return m_arrayModules[moduleIndex];
}

ist::IstackModuleType* ist::IstackModuleExacuteor::GetModulePtr(unsigned int moduleIndex)
{
	return &m_arrayModules[moduleIndex];
}

unsigned int ist::IstackModuleExacuteor::GetModuleCount(void)
{
	return m_arrayModulesLength;
}



void ist::IstackLexParser::pushChar(char charter)
{
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

	if (charter == ';')
	{
		for (unsigned int i = 0; i < m_arrayKeywordsLength; i++)
		{
			bool success = true;

			for (size_t o = 0; o < strnlen(m_arrayKeywords[i], m_maxInputStringBufferLength); o++)
			{
				if (m_inputStringBuffer[o] != m_arrayKeywords[i][o])
				{
					success = false;
					break;
				}
			}

			if (success == true)
			{
				IstackUnit newUnit = IstackUnit();
				newUnit.m_modualTypeCode = i;

				if (m_f_DataParseFunc != nullptr)
				{
					m_f_DataParseFunc(m_inputStringBuffer, m_inputStringBufferIndex, &newUnit);
				}

				m_outputFrame->Push(newUnit);
			}
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
		//delete[] m_arrayKeywords[i];
	}

	//delete[] m_arrayKeywords;
}


void ist::IstackLexParser::SetDataParse(void(*DataParseFunc)(char*, unsigned int, IstackUnit*))
{
	m_f_DataParseFunc = DataParseFunc;
}

void ist::IstackLexParser::SetFrame(IstackStackFrame* frame)
{
	m_outputFrame = frame;
}

void ist::IstackLexParser::AddWords(const char* keyword)
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

void ist::IstackLexParser::ParseStringIntoFrame(const char* string)
{
	for (size_t i = 0; i < strlen(string); i++)
	{
		pushChar(string[i]);
	}
}

void ist::IstackLexParser::operator<<(char* charters)
{
	for (size_t i = 0; i < strlen(charters); i++)
	{
		pushChar(charters[i]);
	}
}

void ist::IstackLexParser::operator<<(const char* charters)
{
	for (size_t i = 0; i < strlen(charters); i++)
	{
		pushChar(charters[i]);
	}
}

void ist::IstackLexParser::operator<<(char charter)
{
	pushChar(charter);
}

bool ist::IstackLexParser::InputBufferOverflowed()
{
	return (m_inputStringBufferIndex >= m_maxInputStringBufferLength);
}

void ist::IstackLexParser::FlushInputBuffer()
{
	m_inputStringBufferIndex = 0;
}
