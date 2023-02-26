#include <stdio.h>
#include <stdlib.h>

#include "Global.h"

CRecDecParGen Parser;	//BARF a global

FILE* LogFile()
{
	return Parser.GetLogFile();
}

char* IndentString(char *s, int nSpaces)
{
	int i = 0;
	while (nSpaces--)
		s[i++] = ' ';
	s[i] = 0;
	return s;
}

const char* TrueFalse(BOOL b)
{
	const char* s;
	if (b)
		s = "TRUE";
	else
		s = "FALSE";
	return s;
}
int main(int arcg, char *argv[])
{
	FILE* pIN;
	FILE* pOUT;
	FILE* pLog;
	char aOutFile[256];

	fopen_s(&pIN,argv[1], "r");
	if (pIN == NULL)
	{
		printf("Cannot Open Input File\n");
		exit(1);
	}
	sprintf_s(aOutFile, 256, "%s.cpp", argv[1]);
	fopen_s(&pOUT, aOutFile, "w");
	if (pOUT == NULL)
	{
		printf("Cannot Open Output File %s\n", aOutFile);
		fclose(pIN);
		exit(1);
	}
	fopen_s(&pLog, "Log.txt", "w");
	if (pLog == NULL)
	{
		fprintf(stderr, "Could not open the Log File\n");
		fclose(pIN);
		fclose(pOUT);
		exit(1);
	}
	fprintf(stderr, "RDgen Ver 0.0.2\n");
	fprintf(stderr, "InFile:%s  OutFile:%s\n",
		argv[1],
		aOutFile
	);

	Parser.Create(pIN, pOUT, pLog);
	Parser.Run();
	printf("Done\n");
	fclose(pIN);
	fclose(pOUT);
	fclose(pLog);
	return 0;
}
