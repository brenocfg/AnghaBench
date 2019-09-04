#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int WORD ;
typedef  int WCHAR ;
struct TYPE_10__ {int X; int Y; } ;
struct TYPE_12__ {TYPE_1__ dwSize; } ;
struct TYPE_11__ {int X; int Y; } ;
typedef  void* SHORT ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int DWORD ;
typedef  TYPE_2__ COORD ;
typedef  TYPE_3__ CONSOLE_SCREEN_BUFFER_INFO ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int ATTR ; 
 int /*<<< orphan*/  FillConsoleOutputCharacterW (int /*<<< orphan*/ ,int,int,TYPE_2__,int*) ; 
 int GetConsoleOutputCP () ; 
 int /*<<< orphan*/  GetConsoleScreenBufferInfo (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  IsValidCodePage (int) ; 
 int /*<<< orphan*/  ReadConsoleOutputAttribute (int /*<<< orphan*/ ,int*,int,TYPE_2__,int*) ; 
 int /*<<< orphan*/  ReadConsoleOutputCharacterW (int /*<<< orphan*/ ,int*,int,TYPE_2__,int*) ; 
 int /*<<< orphan*/  SetConsoleCursorPosition (int /*<<< orphan*/ ,TYPE_2__) ; 
 int /*<<< orphan*/  SetConsoleOutputCP (int) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  WriteConsoleW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ *) ; 
 int ideograph_space ; 
 int lstrlenW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  okCURSOR (int /*<<< orphan*/ ,TYPE_2__) ; 
 int /*<<< orphan*/  skip (char*,...) ; 
 int /*<<< orphan*/  trace (char*,int,...) ; 
 int /*<<< orphan*/  u0414 ; 
 int /*<<< orphan*/  u9580 ; 

__attribute__((used)) static void test_cp932(HANDLE hConOut)
{
    BOOL ret;
    DWORD oldcp;
    int n;
    DWORD len;
    COORD c;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int count;
    WCHAR str[32];
    WORD attr;

    if (!IsValidCodePage(932))
    {
        skip("Codepage 932 not available\n");
        return;
    }

    /* Set code page */
    oldcp = GetConsoleOutputCP();
    SetLastError(0xdeadbeef);
    ret = SetConsoleOutputCP(932);
    if (!ret)
    {
        skip("SetConsoleOutputCP failed with last error %lu\n", GetLastError());
        return;
    }

    /* Get info */
    ret = GetConsoleScreenBufferInfo(hConOut, &csbi);
    ok(ret, "GetConsoleScreenBufferInfo failed\n");
    trace("csbi.dwSize.X:%d, csbi.dwSize.Y:%d\n", csbi.dwSize.X, csbi.dwSize.Y);
    count = csbi.dwSize.X * 3 / 2;
    trace("count: %d\n", count);

    /* "\u0414" */
    {
        /* Output u0414 "count" times at (0,0) */
        c.X = c.Y = 0;
        SetConsoleCursorPosition(hConOut, c);
        okCURSOR(hConOut, c);
        for (n = 0; n < count; ++n)
        {
            ret = WriteConsoleW(hConOut, u0414, lstrlenW(u0414), &len, NULL);
            ok(ret && len == lstrlenW(u0414), "WriteConsoleW failed\n");
        }

        /* Check cursor */
        GetConsoleScreenBufferInfo(hConOut, &csbi);
        len = count * 2;     /* u0414 is fullwidth in Japanese */
        c.X = (SHORT)(len % csbi.dwSize.X);
        c.Y = (SHORT)(len / csbi.dwSize.X);
        okCURSOR(hConOut, c);

        /* Read characters at (0,0) */
        c.X = c.Y = 0;
        ret = ReadConsoleOutputCharacterW(hConOut, str, 3 * sizeof(WCHAR), c, &len);
        ok(ret, "ReadConsoleOutputCharacterW failed\n");
        ok(len == 3, "len was: %ld\n", len);
        ok(str[0] == 0x414, "str[0] was: 0x%04X\n", str[0]);
        ok(str[1] == 0x414, "str[1] was: 0x%04X\n", str[1]);
        ok(str[2] == 0x414, "str[2] was: 0x%04X\n", str[2]);

        /* Check cursor */
        c.X = 1;
        c.Y = 0;
        ret = SetConsoleCursorPosition(hConOut, c);
        ok(ret, "SetConsoleCursorPosition failed\n");
        okCURSOR(hConOut, c);

        /* Fill by space */
        c.X = c.Y = 0;
        FillConsoleOutputCharacterW(hConOut, L' ', csbi.dwSize.X * csbi.dwSize.Y, c, &len);

        /* Output u0414 "count" times at (1,0) */
        c.X = 1;
        c.Y = 0;
        SetConsoleCursorPosition(hConOut, c);
        okCURSOR(hConOut, c);
        for (n = 0; n < count; ++n)
        {
            ret = WriteConsoleW(hConOut, u0414, lstrlenW(u0414), &len, NULL);
            ok(ret && len == lstrlenW(u0414), "WriteConsoleW failed\n");
        }

        /* Check cursor */
        len = csbi.dwSize.X + (count - (csbi.dwSize.X - 1) / 2) * 2;
        c.X = (SHORT)(len % csbi.dwSize.X);
        c.Y = (SHORT)(len / csbi.dwSize.X);
        okCURSOR(hConOut, c);

        /* Read characters at (0,0) */
        c.X = 0;
        c.Y = 0;
        ret = ReadConsoleOutputCharacterW(hConOut, str, 3 * sizeof(WCHAR), c, &len);
        ok(ret, "ReadConsoleOutputCharacterW failed\n");
        ok(len == 4, "len was: %ld\n", len);
        ok(str[0] == L' ', "str[0] was: 0x%04X\n", str[0]);
        ok(str[1] == 0x414, "str[1] was: 0x%04X\n", str[1]);
        ok(str[2] == 0x414, "str[2] was: 0x%04X\n", str[2]);
    }

    /* "\u9580" */
    {
        /* Output u9580 "count" times at (0,0) */
        c.X = c.Y = 0;
        SetConsoleCursorPosition(hConOut, c);
        okCURSOR(hConOut, c);
        for (n = 0; n < count; ++n)
        {
            ret = WriteConsoleW(hConOut, u9580, lstrlenW(u9580), &len, NULL);
            ok(ret && len == lstrlenW(u9580), "WriteConsoleW failed\n");
        }

        /* Check cursor */
        len = count * 2;     /* u9580 is fullwidth in Japanese */
        c.X = (SHORT)(len % csbi.dwSize.X);
        c.Y = (SHORT)(len / csbi.dwSize.X);
        okCURSOR(hConOut, c);

        /* Check cursor */
        c.X = 1;
        c.Y = 0;
        ret = SetConsoleCursorPosition(hConOut, c);
        ok(ret, "SetConsoleCursorPosition failed\n");
        okCURSOR(hConOut, c);

        /* Fill by space */
        c.X = c.Y = 0;
        ret = FillConsoleOutputCharacterW(hConOut, L' ', csbi.dwSize.X * csbi.dwSize.Y, c, &len);
        ok(ret, "FillConsoleOutputCharacterW failed\n");
        ok(len == csbi.dwSize.X * csbi.dwSize.Y, "len was: %ld\n", len);

        /* Output u9580 "count" times at (1,0) */
        c.X = 1;
        c.Y = 0;
        SetConsoleCursorPosition(hConOut, c);
        okCURSOR(hConOut, c);
        for (n = 0; n < count; ++n)
        {
            ret = WriteConsoleW(hConOut, u9580, lstrlenW(u9580), &len, NULL);
            ok(ret && len == lstrlenW(u9580), "WriteConsoleW failed\n");
        }

        /* Check cursor */
        len = csbi.dwSize.X + (count - (csbi.dwSize.X - 1) / 2) * 2;
        c.X = (SHORT)(len % csbi.dwSize.X);
        c.Y = (SHORT)(len / csbi.dwSize.X);
        okCURSOR(hConOut, c);

        /* Fill by ideograph space */
        c.X = c.Y = 0;
        ret = FillConsoleOutputCharacterW(hConOut, ideograph_space, csbi.dwSize.X * csbi.dwSize.Y, c, &len);
        ok(ret, "FillConsoleOutputCharacterW failed\n");
        ok(len == csbi.dwSize.X * csbi.dwSize.Y, "len was: %ld\n", len);

        /* Read characters at (0,0) */
        c.X = c.Y = 0;
        ret = ReadConsoleOutputCharacterW(hConOut, str, 3 * sizeof(WCHAR), c, &len);
        ok(ret, "ReadConsoleOutputCharacterW failed\n");
        ok(len == 3, "len was: %ld\n", len);
        ok(str[0] == ideograph_space, "str[0] was: 0x%04X\n", str[0]);
        ok(str[1] == ideograph_space, "str[1] was: 0x%04X\n", str[1]);
        ok(str[2] == ideograph_space, "str[2] was: 0x%04X\n", str[2]);

        /* Read attr */
        ret = ReadConsoleOutputAttribute(hConOut, &attr, 1, c, &len);
        ok(ret, "ReadConsoleOutputAttribute failed\n");
        ok(attr == ATTR, "attr was: %d\n", attr);
        ok(len == 1, "len was %ld\n", len);

        /* Output u9580 "count" once at (1,0) */
        c.X = 1;
        c.Y = 0;
        SetConsoleCursorPosition(hConOut, c);
        okCURSOR(hConOut, c);
        ret = WriteConsoleW(hConOut, u9580, lstrlenW(u9580), &len, NULL);
        ok(ret && len == lstrlenW(u9580), "WriteConsoleW failed\n");

        /* Read attr */
        ret = ReadConsoleOutputAttribute(hConOut, &attr, 1, c, &len);
        ok(ret, "ReadConsoleOutputAttribute failed\n");
        ok(attr == ATTR, "attr was: %d\n", attr);
        ok(len == 1, "len was %ld\n", len);

        /* Check cursor */
        c.X = 3;
        c.Y = 0;
        okCURSOR(hConOut, c);

        /* Read characters */
        c.X = c.Y = 0;
        ret = ReadConsoleOutputCharacterW(hConOut, str, 3 * sizeof(WCHAR), c, &len);
        ok(ret, "ReadConsoleOutputCharacterW failed\n");
        ok(len == 4, "len was: %ld\n", len);
        ok(str[0] == L' ', "str[0] was: 0x%04X\n", str[0]);
        ok(str[1] == 0x9580, "str[1] was: 0x%04X\n", str[1]);
        ok(str[2] == L' ', "str[2] was: 0x%04X\n", str[2]);
    }

    /* Restore code page */
    SetConsoleOutputCP(oldcp);
}