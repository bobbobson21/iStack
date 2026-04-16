#pragma once

#ifdef ISTACK_EXPORTS
#define ISTACK_API __declspec(dllexport)
#else
#define ISTACK_API __declspec(dllimport)
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

		void CreatePipe();
		void SetPipe(IstackStackFrame* OtherFrame);
		IstackStackFrame** GetPipe(void);
		IstackStackFrame** GetClearedPipe(void);
		void ClearPipe();

		void PushPipeDepthContext();
		void PopPipeDepthContext();
		unsigned int TopPipeDepthContext();

		void Push(IstackUnit unit);
		void Pop(void);
		void Flip(void);

		IstackUnit Top(void);
		IstackUnit* TopPtr(void);
		unsigned int Length(void);

		void CopyIStackTo(IstackStackFrame* otherFrame);
		void CopyPipeDataTo(IstackStackFrame* otherFrame);

		void Flush(void);
		void Free(void);
	};

	/// <summary>
	/// feed the code int this and it will run it
	/// </summary>
	class ISTACK_API IstackModuleExacuteor
	{
	private:
		IstackModuleType* m_arrayModules = nullptr;
		unsigned int m_arrayModulesLength = 0;
		unsigned int m_pointOfFailure = 0;

	public:
		IstackModuleExacuteor& operator=(const IstackModuleExacuteor& t) = delete;

		IstackModuleExacuteor(void);
		~IstackModuleExacuteor(void);

		bool ExacuteFrame(IstackStackFrame* frameIn, IstackStackFrame* frameOut);
		unsigned int GetPointOfFailure();

		void FreeFrameRecursive(IstackStackFrame* frame, bool doDeleteOfPipeFramesAsWell = true);
		void FreeFrame(IstackStackFrame* frame);
		void FreeUnit(IstackUnit* unit);

		void CopyIstackFrameAndModuleDataFromAndTo(IstackStackFrame* copyFrom, IstackStackFrame* copyTo);
		void CopyUnitFromAndTo(IstackUnit* copyFrom, IstackUnit* copyTo);

		unsigned int AddModule(IstackModuleType module);
		IstackModuleType GetModule(unsigned int moduleIndex);
		IstackModuleType* GetModulePtr(unsigned int moduleIndex);
		unsigned int GetModuleCount(void);
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

		void pushChar(char charter);

		bool(*m_f_DataParseFunc)(char*, unsigned int, IstackUnit*) = nullptr;

	public:
		IstackLexParser& operator=(const IstackLexParser& t) = delete;

		IstackLexParser(unsigned int inputBufferSize);
		IstackLexParser(void);
		~IstackLexParser(void);
		
		void SetDataParse(bool(*DataParseFunc)(char*, unsigned int, IstackUnit*));

		void SetFrame(IstackStackFrame* frame);
		void AddWords(const char* keyword);

		void ParseStringIntoFrame(const char* sting);
		void operator<<(char* charters);
		void operator<<(const char* charters);
		void operator<<(char charter);


		bool IsParsingSucessful();
		bool InputBufferOverflowed();
		void FlushInputBuffer();
	};
}
