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
 int /*<<< orphan*/  Edit_GetLineCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Edit_ReplaceSel (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Edit_Scroll (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Edit_SetSel (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  MAX_LOG_SIZE ; 
 int /*<<< orphan*/  OutputDebugStringW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hLog ; 
 int /*<<< orphan*/ * utf8_to_wchar (char const*) ; 

void _uprintfs(const char* str)
{
	wchar_t* wstr;
	wstr = utf8_to_wchar(str);
	OutputDebugStringW(wstr);
	if ((hLog != NULL) && (hLog != INVALID_HANDLE_VALUE)) {
		Edit_SetSel(hLog, MAX_LOG_SIZE, MAX_LOG_SIZE);
		Edit_ReplaceSel(hLog, wstr);
		Edit_Scroll(hLog, Edit_GetLineCount(hLog), 0);
	}
	free(wstr);
}