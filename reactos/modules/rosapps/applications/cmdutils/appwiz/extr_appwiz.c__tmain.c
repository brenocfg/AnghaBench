#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  _TCHAR ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  int INT ;

/* Variables and functions */
 int /*<<< orphan*/  APP_ONLY ; 
 int /*<<< orphan*/  PrintHelp () ; 
 int /*<<< orphan*/  RunGUIAppWiz () ; 
 int /*<<< orphan*/  SHOW_ALL ; 
 int /*<<< orphan*/  SetConsoleTitle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ShowAppList (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UPD_ONLY ; 
 int /*<<< orphan*/  _T (char*) ; 
 scalar_t__ _tcsncmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int atoi (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scanf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int _tmain(int argc, _TCHAR* argv[])
{
    INT iNumber;
    TCHAR Char[4 + 1];

    SetConsoleTitle(_T("Application Wizard"));

    if (argc < 2)
    {
        RunGUIAppWiz();
        return 0;
    }

	if (_tcsncmp(argv[1], _T("/?"), 2) == 0)
	{
		PrintHelp();
		return 0;
	}

    if (_tcsncmp(argv[1], _T("/l"), 2) == 0)
    {
        if (argc < 3) goto ShowAll;
        if (_tcsncmp(argv[2], _T("/all"), 4) == 0)
        {
ShowAll:
            if (ShowAppList(SHOW_ALL, -1) == 0) return 0;
            scanf(_T("%s"), Char);

            iNumber = atoi(Char);

            if (iNumber == 0) return 0;
            ShowAppList(SHOW_ALL, iNumber);
        }
        else if (_tcsncmp(argv[2], _T("/app"), 4) == 0)
        {
            if (ShowAppList(APP_ONLY, -1) == 0) return 0;

            scanf(_T("%s"), Char);

            iNumber = atoi(Char);

            if (iNumber == 0) return 0;
            ShowAppList(APP_ONLY, iNumber);
        }
        else if (_tcsncmp(argv[2], _T("/upd"), 4) == 0)
        {
            if (ShowAppList(UPD_ONLY, -1) == 0) return 0;

            scanf(_T("%s"), Char);

            iNumber = atoi(Char);

            if (iNumber == 0) return 0;
            ShowAppList(UPD_ONLY, iNumber);
        }

        return 0;
    }

	return 0;
}