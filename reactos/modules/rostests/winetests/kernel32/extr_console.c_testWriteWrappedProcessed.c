#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ WORD ;
struct TYPE_7__ {int X; int Y; } ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int const DWORD ;
typedef  TYPE_1__ COORD ;

/* Variables and functions */
 scalar_t__ DEFAULT_ATTRIB ; 
 int const ENABLE_PROCESSED_OUTPUT ; 
 int const ENABLE_WRAP_AT_EOL_OUTPUT ; 
 scalar_t__ GetConsoleMode (int /*<<< orphan*/ ,int const*) ; 
 int /*<<< orphan*/  ReadConsoleOutputAttribute (int /*<<< orphan*/ ,scalar_t__*,int,TYPE_1__,int const*) ; 
 scalar_t__ SetConsoleCursorPosition (int /*<<< orphan*/ ,TYPE_1__) ; 
 scalar_t__ SetConsoleMode (int /*<<< orphan*/ ,int const) ; 
 scalar_t__ TEST_ATTRIB ; 
 scalar_t__ WriteConsoleA (int /*<<< orphan*/ ,char const*,int const,int const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 int /*<<< orphan*/  okCHAR (int /*<<< orphan*/ ,TYPE_1__,char const,scalar_t__) ; 
 int /*<<< orphan*/  okCURSOR (int /*<<< orphan*/ ,TYPE_1__) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void testWriteWrappedProcessed(HANDLE hCon, COORD sbSize)
{
    COORD		c;
    DWORD		len, mode;
    const char*		mytest = "abcd\nf\tg";
    const int	mylen = strlen(mytest);
    int			p;
    WORD                attr;

    ok(GetConsoleMode(hCon, &mode) && SetConsoleMode(hCon, mode | (ENABLE_WRAP_AT_EOL_OUTPUT|ENABLE_PROCESSED_OUTPUT)),
       "setting wrap at EOL & processed output\n");

    /* write line, wrapping enabled, buffer doesn't exceed sb width */
    c.X = sbSize.X - 9; c.Y = 0;
    ok(SetConsoleCursorPosition(hCon, c) != 0, "Cursor in upper-left-9\n");

    ok(WriteConsoleA(hCon, mytest, mylen, &len, NULL) != 0 && len == mylen, "WriteConsole\n");
    for (p = 0; p < 4; p++)
    {
        c.X = sbSize.X - 9 + p;
        okCHAR(hCon, c, mytest[p], TEST_ATTRIB);
    }
    c.X = sbSize.X - 9 + p;
    ReadConsoleOutputAttribute(hCon, &attr, 1, c, &len);
    if (attr == TEST_ATTRIB)
        win_skip("Win9x/WinMe changes attribs for '\\n' up to 'f'\n");
    else
        okCHAR(hCon, c, ' ', DEFAULT_ATTRIB);
    c.X = 0; c.Y++;
    okCHAR(hCon, c, mytest[5], TEST_ATTRIB);
    for (c.X = 1; c.X < 8; c.X++)
        okCHAR(hCon, c, ' ', TEST_ATTRIB);
    okCHAR(hCon, c, mytest[7], TEST_ATTRIB);
    c.X++;
    okCHAR(hCon, c, ' ', DEFAULT_ATTRIB);
    okCURSOR(hCon, c);

    /* write line, wrapping enabled, buffer does exceed sb width */
    c.X = sbSize.X - 3; c.Y = 2;
    ok(SetConsoleCursorPosition(hCon, c) != 0, "Cursor in upper-left-3\n");

    ok(WriteConsoleA(hCon, mytest, mylen, &len, NULL) != 0 && len == mylen, "WriteConsole\n");
    for (p = 0; p < 3; p++)
    {
        c.X = sbSize.X - 3 + p;
        okCHAR(hCon, c, mytest[p], TEST_ATTRIB);
    }
    c.X = 0; c.Y++;
    okCHAR(hCon, c, mytest[3], TEST_ATTRIB);
    c.X++;
    ReadConsoleOutputAttribute(hCon, &attr, 1, c, &len);
    if (attr == TEST_ATTRIB)
        win_skip("Win9x/WinMe changes attribs for '\\n' up to 'f'\n");
    else
        okCHAR(hCon, c, ' ', DEFAULT_ATTRIB);

    c.X = 0; c.Y++;
    okCHAR(hCon, c, mytest[5], TEST_ATTRIB);
    for (c.X = 1; c.X < 8; c.X++)
        okCHAR(hCon, c, ' ', TEST_ATTRIB);
    okCHAR(hCon, c, mytest[7], TEST_ATTRIB);
    c.X++;
    okCHAR(hCon, c, ' ', DEFAULT_ATTRIB);
    okCURSOR(hCon, c);
}