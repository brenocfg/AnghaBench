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

/* Variables and functions */
 int /*<<< orphan*/  CP_UTF8 ; 
 scalar_t__ GetPrivateProfileString (char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int MAX_PATH ; 
 int WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  gl_ini_file ; 
 char* http_post (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  wprintf (char*,...) ; 

__attribute__((used)) static void do_send_report(wchar_t *report)
{
	wchar_t up_url[MAX_PATH];
	int     utf_sz;
	char   *utf;
    char   *p = NULL;

	if (GetPrivateProfileString(L"URL", L"report", NULL, up_url, MAX_PATH, gl_ini_file) == 0) {
		wprintf(L"Report URL not found in rosddt.ini\n"); return;
	}

	utf_sz = WideCharToMultiByte(CP_UTF8, 0, report, -1, NULL, 0, NULL, NULL);
	utf    = malloc(utf_sz);
	utf_sz = WideCharToMultiByte(CP_UTF8, 0, report, -1, utf, utf_sz, NULL, NULL);

	wprintf(L"Sending report...\n");

	if (p == http_post(up_url, utf, utf_sz-1, NULL)) {
		wprintf(L"%S\n", p); free(p);
	} else {
		wprintf(L"Report can not be sended, connection error\n");
	}
}