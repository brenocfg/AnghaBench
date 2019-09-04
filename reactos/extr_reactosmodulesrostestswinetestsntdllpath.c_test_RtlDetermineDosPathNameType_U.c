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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ UINT ;

/* Variables and functions */
 int MAX_PATH ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,scalar_t__,char const*) ; 
 scalar_t__ pRtlDetermineDosPathNameType_U (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pRtlMultiByteToUnicodeN (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,char const*,scalar_t__) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_RtlDetermineDosPathNameType_U(void)
{
    struct test
    {
        const char *path;
        UINT ret;
    };

    static const struct test tests[] =
    {
        { "\\\\foo", 1 },
        { "//foo", 1 },
        { "\\/foo", 1 },
        { "/\\foo", 1 },
        { "\\\\", 1 },
        { "//", 1 },
        { "c:\\foo", 2 },
        { "c:/foo", 2 },
        { "c://foo", 2 },
        { "c:\\", 2 },
        { "c:/", 2 },
        { "c:foo", 3 },
        { "c:f\\oo", 3 },
        { "c:foo/bar", 3 },
        { "\\foo", 4 },
        { "/foo", 4 },
        { "\\", 4 },
        { "/", 4 },
        { "foo", 5 },
        { "", 5 },
        { "\0:foo", 5 },
        { "\\\\.\\foo", 6 },
        { "//./foo", 6 },
        { "/\\./foo", 6 },
        { "\\\\.foo", 1 },
        { "//.foo", 1 },
        { "\\\\.", 7 },
        { "//.", 7 },
        { NULL, 0 }
    };

    const struct test *test;
    WCHAR buffer[MAX_PATH];
    UINT ret;

    if (!pRtlDetermineDosPathNameType_U)
    {
        win_skip("RtlDetermineDosPathNameType_U is not available\n");
        return;
    }

    for (test = tests; test->path; test++)
    {
        pRtlMultiByteToUnicodeN( buffer, sizeof(buffer), NULL, test->path, strlen(test->path)+1 );
        ret = pRtlDetermineDosPathNameType_U( buffer );
        ok( ret == test->ret, "Wrong result %d/%d for %s\n", ret, test->ret, test->path );
    }
}