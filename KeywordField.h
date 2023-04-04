#pragma once

class CKeywordField
{
	enum class ValType{
		NUMBER,
		STRING,
		POINTER
	};
	char* m_pFieldName;			//Name of the Field
	char* m_pFieldCppTypeString;	//C++ variable type name
	ValType m_FieldValueType;		//Number or String Value
	void* m_FieldNumberValue;		// Number Value, if any
	char* m_pFieldStringValue;	//String Value, if any
	CKeywordField* m_pNext;
	CKeywordField* m_pPrev;
public:
	CKeywordField();
	virtual ~CKeywordField();
	BOOL Create();
	BOOL Compare(const char* pName);
	void SetFieldName(const char* pName);
	void SetCppTypeString(const char* pTypeString);
	void SetFiledObjType(ValType Type) { m_FieldValueType = Type; }
	void SetFieldNumberValue(void* pVal) { m_FieldNumberValue = pVal; }
	void SetStringValue(const char* pValString);
	CKeywordField* Duplicate(CKeywordField* newField);
	//---------------------------------------------
	// Linked List Management
	//---------------------------------------------
	CKeywordField* GetNext() { return m_pNext; }
	void SetNext(CKeywordField* pN) { m_pNext = pN; }
	CKeywordField* GetPrev() { return m_pPrev; }
	void SetPrev(CKeywordField* pP) { m_pPrev = pP; }
	//-------------------------------------------
	// Debug Methods
	//-------------------------------------------
	void Print(FILE* pOut);
};

