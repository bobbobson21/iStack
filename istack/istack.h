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

/**
* @brief the ist namespace contains the whole Istack code block system which allows you to put code blocks togeter in a way that leads to some sort of logic exacuting
*/
namespace ist
{
	class ISTACK_API IstackModuleExacuteor; //for modual type
	class ISTACK_API IstackStackFrame;

	/**
	* @brief the unit data and type
	*/
	struct ISTACK_API IstackUnit
	{
		unsigned int m_modualTypeCode = 0; ///Which modual this is from.
		void* m_data = nullptr; ///The data this has.
	};

	/**
	* @brief the type data for a unit
	*/
	struct ISTACK_API IstackModuleType
	{
		bool(*ValidateStack)(IstackStackFrame*, IstackModuleExacuteor*, void**) = nullptr; ///Is the stack valid if not bail on program exacution. Do data modifying here.
		bool(*ValidateSelf)(IstackStackFrame*, IstackModuleExacuteor*, void**) = nullptr; ///Is self valid if not bail on data being added to stack.
		bool(*ValidateSelfPiped)(IstackStackFrame*, IstackModuleExacuteor*, void**) = nullptr; ///can it be added to the sub stack frame and this will also be exacuted in piped stack frames
		void(*FreeData)(void**) = nullptr; ///frees the data
		void(*CopyData)(void**, void**) = nullptr; ///copys the data
	};

	/**
	* @brief frames are local scopes of code nothing inside them can access the outside and they can be fed into IstackModuleExacuteor along with a dump frame (an empty frame that holds data) to have there code exacuted 
	*/
	class ISTACK_API IstackStackFrame
	{
	private:
		IstackUnit* m_stackUnits = nullptr; ///the units/modules currently in the stack
		unsigned int m_stackIndex = 0; //the length of the stack
		unsigned int m_stackTotalLength = 0; ///the length of the stack + the length of the inaccessible region (the inaccessible region being eveything that was poped off from when the stack was its biggest)

		IstackStackFrame* m_pipeTo = nullptr; ///where stuff is currently being piped to
		IstackStackFrame* m_pipeCleared = nullptr; ///a means to access the last piped to location
		unsigned int m_pipeDepthContext = 0; ///used to ensure everything can work correctly involving pipeing

	public:
		IstackStackFrame(void);
		~IstackStackFrame(void);
		IstackStackFrame& operator=(const IstackStackFrame& t) = delete;
		IstackStackFrame(IstackStackFrame const&) = delete;
		IstackStackFrame(IstackStackFrame&& h) = default;

		/**
		* @brief creates a IstackStackFrame which will result in all new units pushed to this frame being insted pushed to that one. SHOULD ONLY BE FREE'D with PipeFree OR PipeClearedFree
		*/
		void PipeCreate(void);

		/**
		* @brief frees the pipe atteched to this from memory
		*/
		void PipeFree(void);

		/**
		* @brief frees the pipe attech to this in the cleared section
		*/
		void PipeClearedFree(void);

		/**
		* @brief connect a frame to this one which all new stuff will be piped to
		*
		* @param[in] otherFrame: the pipe you wish to attach
		*/
		void PipeSet(IstackStackFrame* otherFrame);

		/**
		* @brief gets the frame stuff is currently being piped to
		*
		* @return a pointer to the pointer which contains the frame
		*/
		IstackStackFrame** PipeGet(void);

		/**
		* @brief gets the frame stuff was being piped to
		*
		* @return a pointer to the pointer which contains the frame
		*/
		IstackStackFrame** PipeGetCleared(void);

		/**
		* @brief sets the cleared pipe to the current pipe and sets the current pipe to nullptr
		*/
		void PipeClear();


		/**
		* @brief this is used to make sure we dont premeturely close a pipe as the current pipe should not be close if this dosent equal 0 run it after PipeCreate
		*/
		void PipePushDepthContext();

		/**
		* @brief this is used to make sure we dont premeturely close a pipe as the current pipe should not be close if this dosent equal 0
		*/
		void PipePopDepthContext();

		/**
		* @brief if this equals 0 it is safe to end the current pipe
		*/
		unsigned int PipeTopDepthContext();


		/**
		* @brief adds a unit to the stack
		*
		* @param[in] unit: the uniit you wish to add and it can contain data (make in the applcation side) as well as the module id
		*/
		void UnitPush(IstackUnit unit);

		/**
		* @brief pops a unit for the top of the stack
		*/
		void UnitPop(void);

		/**
		* @brief flips the stack so the bottom becomes the top and the top becomes the bottom useful for scopes
		*/
		void UnitFlip(void);


		/**
		* @brief gets the unit at the top of the stack
		*
		* @return that unit at the top of the stack IstackUnit
		*/
		IstackUnit UnitTop(void);

		/**
		* @brief gets a pointer to the unit at the top of the stack
		*
		* @return the pointer which may be made invalid by new elements added to the stack
		*/
		IstackUnit* UnitTopPtr(void);

		/**
		* @brief gets the length of the stack
		*
		* @return that length
		*/
		unsigned int UnitLength(void);

		/**
		* @brief adds to the max length making further UnitPushes faster
		*
		* @param[in] addToTheAvalibleStackMemoryForNewPushes: adds to the max length of the stack
		*/
		void UnitAddToExtent(unsigned int addToTheAvalibleStackMemoryForNewPushes);


		/**
		* @brief delete the inaccessible region of the stack aka the part above the top of the stack which was allocated to make room for the total about of units
		*/
		void UnitFlush(void);

		/**
		* @brief emptes the stack in totality
		*/
		void UnitFree(void);


		/**
		* @brief copies the stack data to another stack
		*
		* @param[in] otherFrame: the frame the stack data is being coppied to
		*/
		void CopyIStackTo(IstackStackFrame* otherFrame);

		/**
		* @brief copies the pipe data to another stack
		*
		* @param[in] otherFrame: the frame the pipe data is being coppied to
		*/
		void CopyPipeDataTo(IstackStackFrame* otherFrame);
	};

	/**
	* @brief feed a stack frame with code and another frame with nothing into this in order for the code to be exacuted. This also handles a lot of stack frame minulation oparations due to int knowing the bast way to do thoese and it handles error codes from inpropper module useage and it also know what all the moduals mean and what they do.
	*/
	class ISTACK_API IstackModuleExacuteor
	{
	private:
		IstackModuleType* m_moduleTypesArray = nullptr; ///all the types of modules that exsist
		unsigned int m_moduleTypesArrayLength = 0; ///the length of this array
		
		unsigned int m_processDepthMax = 1024; /// the max depth of exacution
		unsigned int m_processDepthCurrent = 0;

		unsigned int m_errorCode = 0; //current error code if there is an error
		bool m_errorSymbolMemoryOverflowed = false; //will be true on error

	public:
		IstackModuleExacuteor(unsigned int processDepth);
		IstackModuleExacuteor(void);
		~IstackModuleExacuteor(void);
		IstackModuleExacuteor& operator=(const IstackModuleExacuteor& t) = delete;
		IstackModuleExacuteor(IstackModuleExacuteor const&) = delete;
		IstackModuleExacuteor(IstackModuleExacuteor&& h) = default;

		/**
		* @brief sets the error that occored
		* 
		* @param[in] code: the code of the error
		*/
		void ErrorSetCode(unsigned int code);

		/**
		* @brief gets the error occored
		*
		* @return the error code
		*/
		unsigned int ErrorGetCode();

		/**
		* @brief did the error occorer because there was to many processes exacuting
		*
		* @return true if this is the case false if otherwise
		*/
		bool ErrorProcessDepthOverflowed();

		/**
		* @brief did an error occour from to many moduls being added (if so HOW)
		*
		* @return true if this is the case but most of the time it will be false
		*/
		bool ErrorSymbolMemoryOverflowed();


		/**
		* @brief exacutes the code in a stack frame
		*
		* @param[in] frameIn: the frame contain the code to be exacuted
		* @param[in] frameOut: an empty frame for data to be dumped in
		*/
		bool ProcessExacuteFrame(IstackStackFrame* frameIn, IstackStackFrame* frameOut);

		/**
		* @brief if exacuted the ProcessDepth data will be errased meaning if you were close to reaching it this is a quick fix for that but it isnt recommened to be used
		*/
		void ProcessFlushDepthContext();


		/**
		* @brief frees the frame and all piped frames under it and all unit date (it is the best free frame option)
		*
		* @param[in] frame: the frameyou wish to have everything in freeded
		* @param[in] doDeleteOfPipeFramesAsWell: should the piped frames also be deleted
		*/
		void FreeFrameRecursive(IstackStackFrame* frame, bool doDeleteOfPipeFramesAsWell = true);

		/**
		* @brief free the frame and all unit date
		*
		* @param[in] frame: the frame you wish to free
		*/
		void FreeFrame(IstackStackFrame* frame);

		/**
		* @brief frees a unit and its data correctly
		*
		* @param[in] unit: the unit you wish to free
		*/
		void FreeUnit(IstackUnit* unit);


		/**
		* @brief copies the unit and its data correctly
		*
		* @param[in] copyFrom: the unit we are copying from
		* @param[in] copyTo: the unit we are copying to
		*/
		void CopyUnitFromAndTo(IstackUnit* copyFrom, IstackUnit* copyTo);

		/**
		* @brief copies the stack frame and its units data correctly
		*
		* @param[in] copyFrom: the frame we are copying from
		* @param[in] copyTo: the frame we are copying to
		*/
		void CopyIstackFrameAndModuleDataFromAndTo(IstackStackFrame* copyFrom, IstackStackFrame* copyTo);

		/**
		* @brief copies all the module type data into another IstackModuleExacuteor
		*
		* @param[in] copyTo: the frame we are copying to
		*/
		void CopyModuleTypeDataFromAndTo(IstackModuleExacuteor* otherExec);

		/**
		* @brief copies the depth data into another IstackModuleExacuteor
		*
		* @param[in] copyTo: the IstackModuleExacuteor we are copying to
		*/
		void CopyModuleProcessDepthDataFromAndTo(IstackModuleExacuteor* otherExec);


		/**
		* @brief adds a module type to the exacutor and in doing this  modules of that type can then be exacuted
		*
		* @param[in] module: the module type data
		*
		* @return the id of the module
		*/
		unsigned int ModuleAddType(IstackModuleType module);

		/**
		* @brief gets the type data of a module if you know its id
		*
		* @param[in] moduleIndex: the index of the module we are getting
		*
		* @return the module type data but changing it wont change the type data in the executor
		*/
		IstackModuleType ModuleGetType(unsigned int moduleIndex);

		/**
		* @brief gets the type data of a module if you know its id
		*
		* @param[in] moduleIndex: the index of the module we are getting
		*
		* @return the module type data but changing it will change the type data in the executor also adding a module after this will corupt the result
		*/
		IstackModuleType* ModuleGetTypePtr(unsigned int moduleIndex);

		/**
		* @brief the length of all the module types added to the array
		*
		* @return that length
		*/
		unsigned int ModuleGetTypeCount(void);

		/**
		* @brief frees all the module types
		*/
		void ModuleFreeTypes(void);
	};

	/**
	* @brief converts the human readable form of code to runtime code
	*/
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
		bool m_errorFrameInvalid = false; ///will be true on error

		bool(*m_f_ParseFuncData)(char*, unsigned int*, IstackUnit*) = nullptr; ///return true to confirm all is working and return false to confirm parsing failure
		bool(*m_f_ParseFuncComment)(char*, unsigned int*, char, IstackLexParser*) = nullptr; ///return true to add text to buffer and return false to block text being added to buffer 
		bool(*m_f_ParseFuncString)(char*, unsigned int*, char, IstackLexParser*) = nullptr; ///return true to say we are outside a sting and false to say we are inside a string and that ingored or controled charater (\t,\n,;) sholud be added to buffer
		bool(*m_f_ParseFuncModuleSeparator)(char*, unsigned int*, char, IstackLexParser*) = nullptr; ///return true to say we have the name of the module we are pasing

		/**
		* @brief adds a letter to the sting buffer and once a ; is added it will that try to find the right module for it
		*
		* @param[in] charter: the letter
		*/
		void PushChar(char charter);

		/**
		* @brief frees the input buffer NO LETTERS CAN BE ADDED AFTER THIS
		*/
		void FreeInputBuffer(void);

		/**
		* @brief creates an input buffer if there isnt one
		*
		* @param[in] inputBufferSize: the size of the buffer/ the defult one that will be created on inilization will be at size 1024
		*/
		void CreateInputBuffer(unsigned int inputBufferSize);

	public:
		IstackLexParser(unsigned int inputBufferSize);
		IstackLexParser(void);
		~IstackLexParser(void);
		IstackLexParser& operator=(const IstackLexParser& t) = delete;
		IstackLexParser(IstackLexParser const&) = delete;
		IstackLexParser(IstackLexParser&& h) = default;

		/**
		* @brief sets the function that pases the data ie 42/"hohoh"/true and has to be done manually there can be no DefParseFuncs for this
		*
		* @param[in] dataParseFunc: parses data function params: (char* textBuffer, unsigned int* textBufferLength, IstackUnit* IstackLexParser* us)
		*/
		void ParseSetDataFunc(bool(*dataParseFunc)(char*, unsigned int*, IstackUnit*));

		/**
		* @brief use ist::DefParseFuncs::CppCommentStyle
		*
		* @param[in] commentParse: the function which parses the comments params: (char* textBuffer, unsigned int textBufferLength, char newLetter, IstackLexParser* us)
		*/
		void ParseSetCommentFunc(bool(*commentParse)(char*, unsigned int*, char, IstackLexParser*));

		/**
		* @brief use ist::DefParseFuncs::LuaStringStyle
		*
		* @param[in] stringParse finds out if we are in a sting or not and sets if chars like \n\t should be ingored or not params: (char* textBuffer, unsigned int textBufferLength, char newLetter, IstackLexParser* us)
		*/
		void ParseSetStringFunc(bool(*stringParse)(char*, unsigned int*, char, IstackLexParser*));

		/**
		* @brief use ist::DefParseFuncs::LuaStringStyle
		*
		* @param[in] stringParse finds out if we are in a sting or not and sets if chars like \n\t should be ingored or not params: (char* textBuffer, unsigned int textBufferLength, char newLetter, IstackLexParser* us)
		*/
		void ParseSetSeparatorFunc(bool(*sepratorParse)(char*, unsigned int*, char, IstackLexParser*));


		/**
		* @brief sets the frame that will have the code added to
		*
		* @param[in] frame: sets the frame that will have the code added to
		*/
		void FrameSet(IstackStackFrame* frame);

		/**
		* @brief adds the text version of a module IT SHOULD BE ADDED DIRECTLY AFTER ADDING THE MODULE TO THE EXEC
		*/
		void WordsAdd(const char* keyword);

		/**
		* @brief frees all the words meaning this can no longer be used to add code to the frame
		*/
		void WordsFree(void);


		/**
		* @brief parses the string into code that will go into the frame that was set
		*
		* @param[in] the c style string
		*/
		void InputParseStringIntoFrame(const char* sting);

		/**
		* @brief parses the string into code that will go into the frame that was set
		*
		* @param[in] the c style string
		*/
		void operator<<(char* charters);

		/**
		* @brief parses the string into code that will go into the frame that was set
		*
		* @param[in] the c style string
		*/
		void operator<<(const char* charters);

		/**
		* @brief parses the char into code that will go into the frame that was set
		*
		* @param[in] the char
		*/
		void operator<<(char charter);

		/**
		* @brief fluses the input buffer and all bool based error data
		*/
		void InputFlushBuffer();


		/**
		* @return true if parsing failed false if otherwise
		*/
		bool ErrorIsParsingUnsucessful();

		/**
		* @return true if the frame code is ment to be sent to is not set
		*/
		bool ErrorFrameUnableToBeFound();

		/**
		* @return true if the input buffer overflow before reaching a ;
		*/
		bool ErrorInputBufferOverflowed();

		/**
		* @return true if there are to many symbols/words
		*/
		bool ErrorSymbolMemoryOverflowed();
	};

	namespace DefParseFuncs
	{
		bool ISTACK_API CppCommentStyle(char* inputBuffer, unsigned int* inputLength, char newChar, ist::IstackLexParser* parserToModify);
		bool ISTACK_API CppModuleSeparator(char* inputBuffer, unsigned int* inputLength, char newChar, ist::IstackLexParser* parserToModify);
		bool ISTACK_API LuaModuleSeparator(char* inputBuffer, unsigned int* inputLength, char newChar, ist::IstackLexParser* parserToModify);
		bool ISTACK_API LuaStringStyle(char* inputBuffer, unsigned int* inputLength, char newChar, ist::IstackLexParser* parserToModify);
	}

}
