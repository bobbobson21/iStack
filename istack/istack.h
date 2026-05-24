#pragma once

#ifdef _WIN32
	#ifdef ISTACK_EXPORTS
		#define ISTACK_API __declspec(dllexport)
	#else
		#define ISTACK_API __declspec(dllimport)
	#endif
#else
#define ISTACK_API
#endif

/// <summary>
/// the ist namespace contains the whole Istack code block system which allows you to put code blocks togeter in a way that leads to some sort of logic exacuting
/// </summary>
namespace ist
{
	class ISTACK_API IstackModuleExacuteor; //for modual type
	class ISTACK_API IstackStackFrame;

	/// <summary>
	/// the unit data and type
	/// </summary>
	struct ISTACK_API IstackUnit
	{
		unsigned int m_modualTypeCode = 0; ///Which modual this is from.
		void* m_data = nullptr; ///The data this has.
	};

	/// <summary>
	/// the type data for a unit
	/// </summary>
	struct ISTACK_API IstackModuleType
	{
		bool(*ValidateStack)(IstackStackFrame*, IstackModuleExacuteor*, void**) = nullptr; ///Is the stack valid if not bail on program exacution. Do data modifying here.
		bool(*ValidateExecution)(IstackStackFrame*, IstackModuleExacuteor*, void**) = nullptr; ///if returns false execution of the current code frame will end
		bool(*ValidateSelf)(IstackStackFrame*, IstackModuleExacuteor*, void**) = nullptr; ///Is self valid if not bail on data being added to stack.
		bool(*ValidateSelfPiped)(IstackStackFrame*, IstackModuleExacuteor*, void**) = nullptr; ///can it be added to the sub stack frame and this will also be exacuted in piped stack frames
		void(*FreeData)(void**) = nullptr; ///frees the data
		void(*CopyData)(void**, void**) = nullptr; ///copys the data
	};

	/// <summary>
	/// frames are local scopes of code nohing inside them can access the outside and they can be fed into IstackModuleExacuteor along with a dump frame (an empty frame that holds data) to have there code exacuted 
	/// </summary>
	class ISTACK_API IstackStackFrame
	{
	private:
		IstackUnit* m_stackUnits = nullptr;
		unsigned int m_stackIndex = 0;
		unsigned int m_stackTotalLength = 0;

		IstackStackFrame* m_pipeTo = nullptr;
		IstackStackFrame* m_pipeCleared = nullptr;
		unsigned int m_pipeDepthContext = 0;

	public:

		IstackModuleType& operator=(const IstackModuleType& t) = delete;

		IstackStackFrame(void);
		~IstackStackFrame(void);

		void PipeCreate();
		void PipeFree();
		void PipeClearedFree();
		void PipeSet(IstackStackFrame* otherFrame);
		IstackStackFrame** PipeGet(void);
		IstackStackFrame** PipeGetCleared(void);
		void PipeClear();

		void PipePushDepthContext();
		void PipePopDepthContext();
		unsigned int PipeTopDepthContext();

		void UnitPush(IstackUnit unit);
		void UnitPop(void);
		void UnitFlip(void);

		IstackUnit UnitTop(void);
		IstackUnit* UnitTopPtr(void);
		unsigned int UnitLength(void);
		void UnitAddToExtent(unsigned int addToTheAvalibleStackMemoryForNewPushes);

		void UnitFlush(void);
		void UnitFree(void);

		void CopyIStackTo(IstackStackFrame* otherFrame);
		void CopyPipeDataTo(IstackStackFrame* otherFrame);
	};

	/// <summary>
	/// feed a stack frame with code and another frame with nothing into this in order for the code to be exacuted. This also handles a lot of stack frame minulation oparations due to int knowing the bast way to do thoese and it handles error codes from inpropper module useage and it also know what all the moduals mean and what they do.
	/// </summary>
	class ISTACK_API IstackModuleExacuteor
	{
	private:
		IstackModuleType* m_moduleTypesArray = nullptr;
		unsigned int m_moduleTypesArrayLength = 0;
		
		unsigned int m_processDepthMax = 1024;
		unsigned int m_processDepthCurrent = 0;

		unsigned int m_errorCode = 0;
		bool m_errorSymbolMemoryOverflowed = false; //will be true on error

	public:

		IstackModuleExacuteor& operator=(const IstackModuleExacuteor& t) = delete;

		IstackModuleExacuteor(unsigned int processDepth);
		IstackModuleExacuteor(void);
		~IstackModuleExacuteor(void);

		void ErrorSetCode(unsigned int code);
		unsigned int ErrorGetCode();
		bool ErrorProcessDepthOverflowed();
		bool ErrorSymbolMemoryOverflowed();

		bool ProcessExacuteFrame(IstackStackFrame* frameIn, IstackStackFrame* frameOut);
		void ProcessFlushDepthContext();

		void FreeFrameRecursive(IstackStackFrame* frame, bool doDeleteOfPipeFramesAsWell = true);
		void FreeFrame(IstackStackFrame* frame);
		void FreeUnit(IstackUnit* unit);

		void CopyUnitFromAndTo(IstackUnit* copyFrom, IstackUnit* copyTo);
		void CopyIstackFrameAndModuleDataFromAndTo(IstackStackFrame* copyFrom, IstackStackFrame* copyTo);
		void CopyModuleTypeDataFromAndTo(IstackModuleExacuteor* otherExec);
		void CopyModuleProcessDepthDataFromAndTo(IstackModuleExacuteor* otherExec);

		unsigned int ModuleAddType(IstackModuleType module);
		IstackModuleType ModuleGetType(unsigned int moduleIndex);
		IstackModuleType* ModuleGetTypePtr(unsigned int moduleIndex);
		unsigned int ModuleGetTypeCount(void);
		void ModuleFreeTypes(void);
	};

	/// <summary>
	/// converts the human readable form of code to runtime code
	/// </summary>
	class ISTACK_API IstackLexParser
	{
	private:
		char** m_keywordsArray = nullptr; ///all the words added to the parser
		unsigned int m_keywordsArrayLength = 0;
				
		IstackStackFrame* m_outputFrame = nullptr;
		
		unsigned int m_inputStringMaxBufferLength = 1024; ///how big the text of a word can be
		unsigned int m_inputStringBufferIndex = 0; ///our place in the buffer
		char* m_inputStringBuffer = nullptr; ///the buffer

		bool m_errorIsParsingUnsucessful = false; ///will be true on error
		bool m_errorSymbolMemoryOverflowed = false; ///will be true on error

		bool(*m_f_ParseFuncData)(char*, unsigned int, IstackUnit*) = nullptr; ///return true to confirm all is working and return false to confirm parsing failure
		bool(*m_f_ParseFuncComment)(char*, unsigned int, char, IstackLexParser*) = nullptr; ///return true to add text to buffer and return false to block text being added to buffer 
		bool(*m_f_ParseFuncString)(char*, unsigned int, char) = nullptr; ///return true to say we are outside a sting and false to say we are inside a string and that ingored or controled charater (\t,\n,;) sholud be added to buffer

		void PushChar(char charter);
		void FreeInputBuffer(void);
		void CreateInputBuffer(unsigned int inputBufferSize);

	public:
		IstackLexParser& operator=(const IstackLexParser& t) = delete;

		IstackLexParser(unsigned int inputBufferSize);
		IstackLexParser(void);
		~IstackLexParser(void);
		
		void ParseSetDataFunc(bool(*dataParseFunc)(char*, unsigned int, IstackUnit*)); ///has to be done manually there can be no DefParseFuncs for this
		void ParseSetCommentFunc(bool(*commentParse)(char*, unsigned int, char, IstackLexParser*)); ///use ist::DefParseFuncs::CppCommentStyle
		void ParseSetStringFunc(bool(*stringParse)(char*, unsigned int, char)); ///use ist::DefParseFuncs::LuaStringStyle

		void FrameSet(IstackStackFrame* frame);
		void WordsAdd(const char* keyword);
		void WordsFree(void);

		void InputParseStringIntoFrame(const char* sting);
		void operator<<(char* charters);
		void operator<<(const char* charters);
		void operator<<(char charter);
		void InputFlushBuffer();

		bool ErrorIsParsingUnsucessful();
		bool ErrorInputBufferOverflowed();
		bool ErrorSymbolMemoryOverflowed();
	};

	namespace DefParseFuncs
	{
		bool ISTACK_API CppCommentStyle(char* inputBuffer, unsigned int inputLength, char newChar, ist::IstackLexParser* parserToModify);
		bool ISTACK_API LuaStringStyle(char* inputBuffer, unsigned int inputLength, char newChar);
	}

}
