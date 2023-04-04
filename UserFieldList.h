#pragma once

class CUserFieldList
{
	CKeywordField* m_pHead;
	CKeywordField* m_pTail;
	int m_nNumFields;
public:
	CUserFieldList();
	virtual ~CUserFieldList();
	BOOL Create();
	void AddField(CKeywordField* pField);
	CKeywordField* FindField(const char* pName);
	int GetNumberOfFields() { return m_nNumFields; }
	//---------------------------------------
	// Linked List
	//---------------------------------------
	CKeywordField* GetHead() { return m_pHead; }
	void SetHead(CKeywordField* pH) { m_pHead = pH; }
	CKeywordField* GetTail() { return m_pTail; }
	void SetTail(CKeywordField* pT) { m_pTail = pT; }
};

