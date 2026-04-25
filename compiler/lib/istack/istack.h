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
/// the ist namespace contains thw whole Istack code block system which allows you to put code blocks togeter in a way that leads to some sort of logic exacuting
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
		bool(*ValidateSelf)(IstackStackFrame*, IstackModuleExacuteor*, void**) = nullptr; ///Is self valid if not bail on data being added to stack.
		bool(*ValidateSelfPiped)(IstackStackFrame*, IstackModuleExacuteor*, void**) = nullptr; ///can it be added to the sub stack frame and this will also be exacuted in piped stack frames
		void(*FreeData)(void**) = nullptr; ///frees the data
		void(*CopyData)(void**, void**) = nullptr; ///copys the data
	};

	/// <summary>
	/// frames are local scopes nohing inside them can access the outside and vise versa
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
	/// feed the code int this and it will run it
	/// </summary>
	class ISTACK_API IstackModuleExacuteor
	{
	private:
		IstackModuleType* m_arrayModules = nullptr;
		unsigned int m_arrayModulesLength = 0;
		
		unsigned int m_errorCode = 0;
		unsigned int m_maxProcessDepth = 1024;
		unsigned int m_currentProcessDepth = 0;

	public:
		IstackModuleExacuteor& operator=(const IstackModuleExacuteor& t) = delete;

		IstackModuleExacuteor(unsigned int processDepth);
		IstackModuleExacuteor(void);
		~IstackModuleExacuteor(void);

		void ErrorSetCode(unsigned int code);
		unsigned int ErrorGetCode();
		bool ErrorProcessDepthOverflowed();

		bool ProcessExacuteFrame(IstackStackFrame* frameIn, IstackStackFrame* frameOut);
		bool ProcessExacuteFrameAsIfPiped(IstackStackFrame* frameIn, IstackStackFrame* frameOut);
		void ProcessFlushDepthContext();

		void FreeFrameRecursive(IstackStackFrame* frame, bool doDeleteOfPipeFramesAsWell = true);
		void FreeFrame(IstackStackFrame* frame);
		void FreeUnit(IstackUnit* unit);

		void CopyIstackFrameAndModuleDataFromAndTo(IstackStackFrame* copyFrom, IstackStackFrame* copyTo);
		void CopyUnitFromAndTo(IstackUnit* copyFrom, IstackUnit* copyTo);

		unsigned int ModuleAdd(IstackModuleType module);
		IstackModuleType ModuleGet(unsigned int moduleIndex);
		IstackModuleType* ModuleGetPtr(unsigned int moduleIndex);
		unsigned int ModuleGetCount(void);
	};

	/// <summary>
	/// converts the human readable form of code to runtime code
	/// </summary>
	class ISTACK_API IstackLexParser
	{
	private:
		char** m_arrayKeywords = nullptr;	
		unsigned int m_arrayKeywordsLength = 0;
				
		IstackStackFrame* m_outputFrame = nullptr;
		
		unsigned int m_maxInputStringBufferLength = 1024;
		unsigned int m_inputStringBufferIndex = 0;
		char* m_inputStringBuffer = nullptr;
		unsigned int m_scopeInputDepth = 0;

		bool m_isParsingSucessful = true;

		void PushChar(char charter);

		bool(*m_f_DataParseFunc)(char*, unsigned int, IstackUnit*) = nullptr;
		bool(*m_f_CommentParse)(char*, unsigned int, char, IstackLexParser*) = nullptr;

	public:
		IstackLexParser& operator=(const IstackLexParser& t) = delete;

		IstackLexParser(unsigned int inputBufferSize);
		IstackLexParser(void);
		~IstackLexParser(void);
		
		void SetDataParse(bool(*DataParseFunc)(char*, unsigned int, IstackUnit*));
		void SetCommentParse(bool(*CommentParse)(char*, unsigned int, char, IstackLexParser*));

		void SetFrame(IstackStackFrame* frame);
		void AddWord(const char* keyword);

		void InputParseStringIntoFrame(const char* sting);
		void operator<<(char* charters);
		void operator<<(const char* charters);
		void operator<<(char charter);
		void InputFlushBuffer();

		bool ErrorIsParsingUnsucessful();
		bool ErrorInputBufferOverflowed();
	};

	namespace includedStyles
	{
		bool ISTACK_API CppCommentStyle(char* inputBuffer, unsigned int inputLength, char newChar, ist::IstackLexParser* parserToModify);
	}

}
