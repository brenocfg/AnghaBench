#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int X; int Y; } ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int const DWORD ;
typedef  TYPE_1__ COORD ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_ATTRIB ; 
 int const ENABLE_PROCESSED_OUTPUT ; 
 int const ENABLE_WRAP_AT_EOL_OUTPUT ; 
 scalar_t__ GetConsoleMode (int /*<<< orphan*/ ,int const*) ; 
 scalar_t__ SetConsoleCursorPosition (int /*<<< orphan*/ ,TYPE_1__) ; 
 scalar_t__ SetConsoleMode (int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  TEST_ATTRIB ; 
 scalar_t__ WriteConsoleA (int /*<<< orphan*/ ,char const*,int const,int const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 int /*<<< orphan*/  okCHAR (int /*<<< orphan*/ ,TYPE_1__,char const,int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void testWriteWrappedNotProcessed(HANDLE hCon, COORD sbSize)
{
    COORD		c;
    DWORD		len, mode;
    const char*		mytest = "abcd\nf\tg";
    const int	mylen = strlen(mytest);
    int			p;

    ok(GetConsoleMode(hCon, &mode) && SetConsoleMode(hCon,(mode | ENABLE_WRAP_AT_EOL_OUTPUT) & ~(ENABLE_PROCESSED_OUTPUT)),
       "setting wrap at EOL & clearing processed output\n");

    /* write line, wrapping enabled, buffer doesn't exceed sb width */
    c.X = sbSize.X - 9; c.Y = 0;
    ok(SetConsoleCursorPosition(hCon, c) != 0, "Cursor in upper-left-9\n");

    ok(WriteConsoleA(hCon, mytest, mylen, &len, NULL) != 0 && len == mylen, "WriteConsole\n");
    c.Y = 0;
    for (p = 0; p < mylen; p++)
    {
        c.X = sbSize.X - 9 + p;
        okCHAR(hCon, c, mytest[p], TEST_ATTRIB);
    }
    c.X = sbSize.X - 9 + mylen;
    okCHAR(hCon, c, ' ', DEFAULT_ATTRIB);
    c.X = 0; c.Y = 1;
    okCHAR(hCon, c, ' ', DEFAULT_ATTRIB);

    /* write line, wrapping enabled, buffer does exceed sb width */
    c.X = sbSize.X - 3; c.Y = 0;
    ok(SetConsoleCursorPosition(hCon, c) != 0, "Cursor in upper-left-3\n");

    c.Y = 1;
    c.X = mylen - 3;
    okCHAR(hCon, c, ' ', DEFAULT_ATTRIB);
}