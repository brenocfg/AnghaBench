#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buff ;
struct TYPE_4__ {char* cFileName; } ;
typedef  TYPE_1__ WIN32_FIND_DATA ;
typedef  int INT ;
typedef  scalar_t__ HANDLE ;
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int BUFF_SIZE ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  ConErrPrintf (char*,char*) ; 
 int /*<<< orphan*/  ConOutPuts (int /*<<< orphan*/ ) ; 
 scalar_t__ CreateFile (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int /*<<< orphan*/  FILE_SHARE_READ ; 
 int /*<<< orphan*/  FindClose (scalar_t__) ; 
 scalar_t__ FindFirstFile (char*,TYPE_1__*) ; 
 scalar_t__ FindNextFile (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 scalar_t__ GetStdHandle (int /*<<< orphan*/ ) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 scalar_t__ ReadFile (scalar_t__,char*,int,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STD_INPUT_HANDLE ; 
 int /*<<< orphan*/  STD_OUTPUT_HANDLE ; 
 int /*<<< orphan*/  Sleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteFile (scalar_t__,char*,scalar_t__,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _T (char*) ; 
 scalar_t__ _tcsncmp (char*,int /*<<< orphan*/ ,int) ; 

int main (int argc, char **argv)
{
	INT i;
	HANDLE hFind;
	HANDLE hConsoleIn, hConsoleOut, hFile;
	char buff[BUFF_SIZE];
	DWORD dwRead,dwWritten;
	BOOL bRet;
	WIN32_FIND_DATA FindData;

	hConsoleIn = GetStdHandle(STD_INPUT_HANDLE);
	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);

	if (argc == 2 && _tcsncmp (argv[1], _T("/?"), 2) == 0)
	{
		ConOutPuts(_T("copy stdin to stdout and then files to stdout\n"
		              "\n"
		              "Y [files]\n"
		              "\n"
		              "files         files to copy to stdout"));
		return 0;
	}

	/*stdin to stdout*/
	do
	{
		bRet = ReadFile(hConsoleIn,buff,sizeof(buff),&dwRead,NULL);

		if (dwRead>0 && bRet)
			WriteFile(hConsoleOut,buff,dwRead,&dwWritten,NULL);

	} while(dwRead>0 && bRet);


	/*files to stdout*/
	Sleep(0);

	for (i = 1; i < argc; i++)
	{
		hFind=FindFirstFile(argv[i],&FindData);

		if (hFind==INVALID_HANDLE_VALUE)
		{
			ConErrPrintf("File not found - %s\n",argv[i]);
			continue;
		}

		do
		{
			hFile = CreateFile(FindData.cFileName,
				GENERIC_READ,
				FILE_SHARE_READ,NULL,
				OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL,NULL);

			if(hFile == INVALID_HANDLE_VALUE)
			{
				ConErrPrintf("File not found - %s\n",FindData.cFileName);
				continue;
			}

			do
			{
				bRet = ReadFile(hFile,buff,sizeof(buff),&dwRead,NULL);

				if (dwRead>0 && bRet)
					WriteFile(hConsoleOut,buff,dwRead,&dwWritten,NULL);

			} while(dwRead>0 && bRet);

			CloseHandle(hFile);

		}
		while(FindNextFile(hFind,&FindData));

		FindClose(hFind);
	}

	return 0;
}