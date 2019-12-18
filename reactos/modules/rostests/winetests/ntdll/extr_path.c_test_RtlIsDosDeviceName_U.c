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
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ ULONG ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  HIWORD (scalar_t__) ; 
 int /*<<< orphan*/  LOWORD (scalar_t__) ; 
 scalar_t__ MAKELONG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  TRUE 128 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ pRtlIsDosDeviceName_U (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pRtlMultiByteToUnicodeN (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,char const*,scalar_t__) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_RtlIsDosDeviceName_U(void)
{
    struct test
    {
        const char *path;
        WORD pos;
        WORD len;
        BOOL fails;
    };

    static const struct test tests[] =
    {
        { "\\\\.\\CON",    8, 6, TRUE },  /* fails on win8 */
        { "\\\\.\\con",    8, 6, TRUE },  /* fails on win8 */
        { "\\\\.\\CON2",   0, 0 },
        { "",              0, 0 },
        { "\\\\foo\\nul",  0, 0 },
        { "c:\\nul:",      6, 6 },
        { "c:\\nul\\",     0, 0 },
        { "c:\\nul\\foo",  0, 0 },
        { "c:\\nul::",     6, 6, TRUE },  /* fails on nt4 */
        { "c:\\nul::::::", 6, 6, TRUE },  /* fails on nt4 */
        { "c:prn     ",    4, 6 },
        { "c:prn.......",  4, 6 },
        { "c:prn... ...",  4, 6 },
        { "c:NUL  ....  ", 4, 6, TRUE },  /* fails on nt4 */
        { "c: . . .",      0, 0 },
        { "c:",            0, 0 },
        { " . . . :",      0, 0 },
        { ":",             0, 0 },
        { "c:nul. . . :",  4, 6 },
        { "c:nul . . :",   4, 6, TRUE },  /* fails on nt4 */
        { "c:nul0",        0, 0 },
        { "c:prn:aaa",     4, 6, TRUE },  /* fails on win9x */
        { "c:PRN:.txt",    4, 6 },
        { "c:aux:.txt...", 4, 6 },
        { "c:prn:.txt:",   4, 6 },
        { "c:nul:aaa",     4, 6, TRUE },  /* fails on win9x */
        { "con:",          0, 6 },
        { "lpt1:",         0, 8 },
        { "c:com5:",       4, 8 },
        { "CoM4:",         0, 8 },
        { "lpt9:",         0, 8 },
        { "c:\\lpt0.txt",  0, 0 },
        { "c:aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
          "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
          "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
          "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
          "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
          "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
          "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\\nul.txt", 1000, 6 },
        // ReactOS r54114
        { "c:\\nul",       6, 6 },
        { NULL, 0 }
    };

    const struct test *test;
    WCHAR buffer[2000];
    ULONG ret;

    if (!pRtlIsDosDeviceName_U)
    {
        win_skip("RtlIsDosDeviceName_U is not available\n");
        return;
    }

    for (test = tests; test->path; test++)
    {
        pRtlMultiByteToUnicodeN( buffer, sizeof(buffer), NULL, test->path, strlen(test->path)+1 );
        ret = pRtlIsDosDeviceName_U( buffer );
        ok( ret == MAKELONG( test->len, test->pos ) ||
            (test->fails && broken( ret == 0 )),
            "Wrong result (%d,%d)/(%d,%d) for %s\n",
            HIWORD(ret), LOWORD(ret), test->pos, test->len, test->path );
    }
}