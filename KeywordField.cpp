#include "Global.h"

CKeywordField::CKeywordField()
{
}

CKeywordField::~CKeywordField()
{
}

BOOL CKeywordField::Create()
{
	//--------------------------------------
	// Create
	// 
	//--------------------------------------
	BOOL rV = TRUE;

	return rV;
}

BOOL CKeywordField::Compare(const char* pName)
{
	BOOL match = FALSE;

	if (strcmp(m_pFieldName, pName) == 0)
		match = TRUE;
	return match;
}

void CKeywordField::SetFieldName(const char* pName)
{
	int l;
	l = strlen(pName) + 1;
	m_pFieldName = new char[l];
	strcpy_s(m_pFieldName, l, pName);
}

void CKeywordField::SetCppTypeString(const char* pTypeString)
{
	int l;
	l = strlen(pTypeString) + 1;
	m_pFieldCppTypeString = new char[l];
	strcpy_s(m_pFieldCppTypeString, l, pTypeString);
}

void CKeywordField::SetStringValue(const char* pValueString)
{
	int l;
	l = strlen(pValueString) + 1;
	m_pFieldStringValue = new char[l];
	strcpy_s(m_pFieldStringValue, l, pValueString);
}

CKeywordField* CKeywordField::Duplicate(CKeywordField* pNewField)
{
	pNewField->Create();
	pNewField->SetFieldName(m_pFieldName);
	pNewField->SetCppTypeString(m_pFieldCppTypeString);
	pNewField->SetFiledObjType(m_FieldValueType);
	return pNewField;
}

void CKeywordField::Print(FILE* pOut)
{
	const char* pValType;
	const char* pFormat;
	if (pOut)
	{
		switch (m_FieldValueType)
		{
		case ValType::NUMBER:
			pValType = "NUMBER";
			fprintf(pOut, "%s:(%s)Type=%s Value=%d",
				m_pFieldName,
				m_pFieldCppTypeString,
				pValType,
				(int)m_FieldNumberValue
			);
			break;
		case ValType::POINTER:
			pValType = "POINTER";
			fprintf(pOut, "%s:(%s)Type=%s Value=%P",
				m_pFieldName,
				m_pFieldCppTypeString,
				pValType,
				m_FieldNumberValue
			);
			break;
		case ValType::STRING:
			pValType = "STRING";
			fprintf(pOut, "%s:(%s)Type=%s Value=%s",
				m_pFieldName,
				m_pFieldCppTypeString,
				pValType,
				m_pFieldStringValue
			);
			break;
		}
	}
}
