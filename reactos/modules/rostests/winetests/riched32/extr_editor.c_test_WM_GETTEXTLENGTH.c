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
 int SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_GETTEXTLENGTH ; 
 int /*<<< orphan*/  WM_SETTEXT ; 
 int /*<<< orphan*/  is_lang_japanese ; 
 int lstrlenA (char const*) ; 
 int /*<<< orphan*/  new_richedit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void test_WM_GETTEXTLENGTH(void)
{
    HWND hwndRichEdit = new_richedit(NULL);
    static const char text1[] = "aaa\r\nbbb\r\nccc\r\nddd\r\neee";
    static const char text2[] = "aaa\r\nbbb\r\nccc\r\nddd\r\neee\r\n";
    static const char text3[] = "abcdef\x8e\xf0";
    int result;

    /* Test for WM_GETTEXTLENGTH */
    SendMessageA(hwndRichEdit, WM_SETTEXT, 0, (LPARAM)text1);
    result = SendMessageA(hwndRichEdit, WM_GETTEXTLENGTH, 0, 0);
    ok(result == lstrlenA(text1),
       "WM_GETTEXTLENGTH reports incorrect length %d, expected %d\n",
       result, lstrlenA(text1));

    SendMessageA(hwndRichEdit, WM_SETTEXT, 0, (LPARAM)text2);
    result = SendMessageA(hwndRichEdit, WM_GETTEXTLENGTH, 0, 0);
    ok(result == lstrlenA(text2),
       "WM_GETTEXTLENGTH reports incorrect length %d, expected %d\n",
       result, lstrlenA(text2));

    /* Test with multibyte character */
    if (!is_lang_japanese)
        skip("Skip multibyte character tests on non-Japanese platform\n");
    else
    {
        SendMessageA(hwndRichEdit, WM_SETTEXT, 0, (LPARAM)text3);
        result = SendMessageA(hwndRichEdit, WM_GETTEXTLENGTH, 0, 0);
        ok(result == 8, "WM_GETTEXTLENGTH returned %d, expected 8\n", result);
    }

    DestroyWindow(hwndRichEdit);
}