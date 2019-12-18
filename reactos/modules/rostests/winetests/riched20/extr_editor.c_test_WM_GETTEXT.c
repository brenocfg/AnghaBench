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
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ ) ; 
 int SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_GETTEXT ; 
 int /*<<< orphan*/  WM_GETTEXTLENGTH ; 
 int /*<<< orphan*/  WM_SETTEXT ; 
 int lstrlenA (char const*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  new_richedit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 int strcmp (char*,char const*) ; 
 int strlen (char const*) ; 
 int strncmp (char*,char const*,int) ; 

__attribute__((used)) static void test_WM_GETTEXT(void)
{
    HWND hwndRichEdit = new_richedit(NULL);
    static const char text[] = "Hello. My name is RichEdit!";
    static const char text2[] = "Hello. My name is RichEdit!\r";
    static const char text2_after[] = "Hello. My name is RichEdit!\r\n";
    char buffer[1024] = {0};
    int result;

    /* Baseline test with normal-sized buffer */
    SendMessageA(hwndRichEdit, WM_SETTEXT, 0, (LPARAM)text);
    result = SendMessageA(hwndRichEdit, WM_GETTEXT, 1024, (LPARAM)buffer);
    ok(result == lstrlenA(buffer),
        "WM_GETTEXT returned %d, expected %d\n", result, lstrlenA(buffer));
    SendMessageA(hwndRichEdit, WM_GETTEXT, 1024, (LPARAM)buffer);
    result = strcmp(buffer,text);
    ok(result == 0, 
        "WM_GETTEXT: settext and gettext differ. strcmp: %d\n", result);

    /* Test for returned value of WM_GETTEXTLENGTH */
    result = SendMessageA(hwndRichEdit, WM_GETTEXTLENGTH, 0, 0);
    ok(result == lstrlenA(text),
        "WM_GETTEXTLENGTH reports incorrect length %d, expected %d\n",
        result, lstrlenA(text));

    /* Test for behavior in overflow case */
    memset(buffer, 0, 1024);
    result = SendMessageA(hwndRichEdit, WM_GETTEXT, strlen(text), (LPARAM)buffer);
    ok(result == 0 ||
       result == lstrlenA(text) - 1, /* XP, win2k3 */
        "WM_GETTEXT returned %d, expected 0 or %d\n", result, lstrlenA(text) - 1);
    result = strcmp(buffer,text);
    if (result)
        result = strncmp(buffer, text, lstrlenA(text) - 1); /* XP, win2k3 */
    ok(result == 0,
        "WM_GETTEXT: settext and gettext differ. strcmp: %d\n", result);

    /* Baseline test with normal-sized buffer and carriage return */
    SendMessageA(hwndRichEdit, WM_SETTEXT, 0, (LPARAM)text2);
    result = SendMessageA(hwndRichEdit, WM_GETTEXT, 1024, (LPARAM)buffer);
    ok(result == lstrlenA(buffer),
        "WM_GETTEXT returned %d, expected %d\n", result, lstrlenA(buffer));
    result = strcmp(buffer,text2_after);
    ok(result == 0,
        "WM_GETTEXT: settext and gettext differ. strcmp: %d\n", result);

    /* Test for returned value of WM_GETTEXTLENGTH */
    result = SendMessageA(hwndRichEdit, WM_GETTEXTLENGTH, 0, 0);
    ok(result == lstrlenA(text2_after),
        "WM_GETTEXTLENGTH reports incorrect length %d, expected %d\n",
        result, lstrlenA(text2_after));

    /* Test for behavior of CRLF conversion in case of overflow */
    memset(buffer, 0, 1024);
    result = SendMessageA(hwndRichEdit, WM_GETTEXT, strlen(text2), (LPARAM)buffer);
    ok(result == 0 ||
       result == lstrlenA(text2) - 1, /* XP, win2k3 */
        "WM_GETTEXT returned %d, expected 0 or %d\n", result, lstrlenA(text2) - 1);
    result = strcmp(buffer,text2);
    if (result)
        result = strncmp(buffer, text2, lstrlenA(text2) - 1); /* XP, win2k3 */
    ok(result == 0,
        "WM_GETTEXT: settext and gettext differ. strcmp: %d\n", result);

    DestroyWindow(hwndRichEdit);
}