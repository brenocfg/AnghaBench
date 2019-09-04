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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  scalar_t__ LPCWSTR ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int INT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/ * Alloc (int) ; 
 int /*<<< orphan*/  CP_ACP ; 
 scalar_t__ LPSTR_TEXTCALLBACKW ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TRACE (char*,char*) ; 
 char* debugstr_w (int /*<<< orphan*/ *) ; 
 scalar_t__ is_text (scalar_t__) ; 

__attribute__((used)) static inline LPWSTR textdupTtoW(LPCWSTR text, BOOL isW)
{
    LPWSTR wstr = (LPWSTR)text;

    if (!isW && is_text(text))
    {
	INT len = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)text, -1, NULL, 0);
	wstr = Alloc(len * sizeof(WCHAR));
	if (wstr) MultiByteToWideChar(CP_ACP, 0, (LPCSTR)text, -1, wstr, len);
    }
    TRACE("   wstr=%s\n", text == LPSTR_TEXTCALLBACKW ?  "(callback)" : debugstr_w(wstr));
    return wstr;
}