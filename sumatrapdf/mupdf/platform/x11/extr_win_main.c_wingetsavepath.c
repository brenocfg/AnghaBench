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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  pdfapp_t ;
struct TYPE_4__ {int lStructSize; int nMaxFile; char* lpstrTitle; char* lpstrFilter; int /*<<< orphan*/  Flags; int /*<<< orphan*/ * lpstrInitialDir; int /*<<< orphan*/ * lpstrFile; int /*<<< orphan*/  hwndOwner; } ;
typedef  TYPE_1__ OPENFILENAME ;

/* Variables and functions */
 int /*<<< orphan*/  CP_UTF8 ; 
 scalar_t__ GetSaveFileName (TYPE_1__*) ; 
 int /*<<< orphan*/  MIN (int,int) ; 
 int /*<<< orphan*/  OFN_HIDEREADONLY ; 
 int PATH_MAX ; 
 int WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  filename ; 
 int /*<<< orphan*/  hwndframe ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pdfapp_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * wbuf ; 
 int /*<<< orphan*/  wcscpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int wingetsavepath(pdfapp_t *app, char *buf, int len)
{
	wchar_t twbuf[PATH_MAX];
	OPENFILENAME ofn;

	wcscpy(twbuf, wbuf);
	memset(&ofn, 0, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hwndframe;
	ofn.lpstrFile = twbuf;
	ofn.nMaxFile = PATH_MAX;
	ofn.lpstrInitialDir = NULL;
	ofn.lpstrTitle = L"MuPDF: Save PDF file";
	ofn.lpstrFilter = L"PDF Documents (*.pdf)\0*.pdf\0All Files\0*\0\0";
	ofn.Flags = OFN_HIDEREADONLY;
	if (GetSaveFileName(&ofn))
	{
		int code = WideCharToMultiByte(CP_UTF8, 0, twbuf, -1, buf, MIN(PATH_MAX, len), NULL, NULL);
		if (code == 0)
		{
			pdfapp_error(app, "cannot convert filename to utf-8");
			return 0;
		}

		wcscpy(wbuf, twbuf);
		strcpy(filename, buf);
		return 1;
	}
	else
	{
		return 0;
	}
}