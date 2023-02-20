#pragma once

class CStack
{
public:
	int m_StackPointer;
	char* m_pStack;
	int Push(void* pV);
};

