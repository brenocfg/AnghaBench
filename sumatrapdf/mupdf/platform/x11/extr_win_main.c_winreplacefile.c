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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  pdfapp_t ;

/* Variables and functions */
 int /*<<< orphan*/  CP_UTF8 ; 
 int /*<<< orphan*/  DeleteFile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MoveFile (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int) ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  REPLACEFILE_IGNORE_MERGE_ERRORS ; 
 int /*<<< orphan*/  ReplaceFile (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdfapp_error (int /*<<< orphan*/ *,char*) ; 

void winreplacefile(pdfapp_t *app, char *source, char *target)
{
	wchar_t wsource[PATH_MAX];
	wchar_t wtarget[PATH_MAX];

	int sz = MultiByteToWideChar(CP_UTF8, 0, source, -1, wsource, PATH_MAX);
	if (sz == 0)
	{
		pdfapp_error(app, "cannot convert filename to Unicode");
		return;
	}

	sz = MultiByteToWideChar(CP_UTF8, 0, target, -1, wtarget, PATH_MAX);
	if (sz == 0)
	{
		pdfapp_error(app, "cannot convert filename to Unicode");
		return;
	}

#if (_WIN32_WINNT >= 0x0500)
	ReplaceFile(wtarget, wsource, NULL, REPLACEFILE_IGNORE_MERGE_ERRORS, NULL, NULL);
#else
	DeleteFile(wtarget);
	MoveFile(wsource, wtarget);
#endif
}