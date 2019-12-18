#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ofc ;
struct TYPE_10__ {int lStructSize; int nFilterIndex; int Flags; int nMaxFile; struct TYPE_10__* lpstrFile; int /*<<< orphan*/  lpstrDefExt; int /*<<< orphan*/  lpstrTitle; int /*<<< orphan*/  lpstrFilter; } ;
typedef  TYPE_1__ TCHAR ;
typedef  TYPE_1__ OPENFILENAME ;
typedef  int /*<<< orphan*/  FileName ;

/* Variables and functions */
 int /*<<< orphan*/  FILEOPEN_DEFEXT ; 
 int /*<<< orphan*/  FILEOPEN_FILTER ; 
 int /*<<< orphan*/  FILEOPEN_TITLE ; 
 int GetOpenFileName (TYPE_1__*) ; 
 int /*<<< orphan*/  INF_COMMAND ; 
 int /*<<< orphan*/  InstallHinfSection (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int MAX_PATH ; 
 int MB_ICONERROR ; 
 int MB_OK ; 
 int /*<<< orphan*/  MessageBox (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int OFN_FILEMUSTEXIST ; 
 int OFN_LONGNAMES ; 
 int OFN_PATHMUSTEXIST ; 
 int /*<<< orphan*/  TEXT (char*) ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_1__*,int) ; 
 int /*<<< orphan*/  _stprintf (TYPE_1__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int _tcslen (TYPE_1__*) ; 

int
_tmain(int argc, TCHAR *argv[])
{
	TCHAR infCommand[MAX_PATH + 32];

	if (argc <= 1)
	{
		TCHAR FileName[MAX_PATH + 1];
		OPENFILENAME ofc;
		int rv;

		ZeroMemory(&ofc, sizeof(ofc));
		ZeroMemory(FileName, MAX_PATH + 1);
		ofc.lStructSize = sizeof(ofc);
		ofc.lpstrFilter = FILEOPEN_FILTER;
		ofc.nFilterIndex = 1;
		ofc.lpstrTitle = FILEOPEN_TITLE;
		ofc.Flags = OFN_FILEMUSTEXIST | OFN_LONGNAMES | OFN_PATHMUSTEXIST;
		ofc.lpstrDefExt = FILEOPEN_DEFEXT;
		ofc.lpstrFile = FileName;
		ofc.nMaxFile = sizeof(FileName) / sizeof(TCHAR);

		rv = GetOpenFileName(&ofc);

		if (rv == 0)
			return 1;

		_stprintf(infCommand, INF_COMMAND, FileName);
	}
	else
	{
		if (_tcslen(argv[1]) > MAX_PATH)
		{
			MessageBox(NULL, TEXT("Command line too long to be a valid file name"), NULL, MB_OK | MB_ICONERROR);
			return 2; /* User error */
		}
		_stprintf(infCommand, INF_COMMAND, argv[1]);
	}

	InstallHinfSection(NULL, NULL, infCommand, 0);

	return 0;
}