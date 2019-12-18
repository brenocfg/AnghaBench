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
struct TYPE_7__ {scalar_t__ expect; scalar_t__ expectOpaque; scalar_t__ expectFile; int /*<<< orphan*/  url; int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ WCHAR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_1__*,size_t) ; 
 TYPE_1__* TEST_PATH_IS_URL ; 
 TYPE_1__* TEST_URLIS_ATTRIBS ; 
 int /*<<< orphan*/  URLIS_APPLIABLE ; 
 int /*<<< orphan*/  URLIS_DIRECTORY ; 
 int /*<<< orphan*/  URLIS_FILEURL ; 
 int /*<<< orphan*/  URLIS_HASQUERY ; 
 int /*<<< orphan*/  URLIS_NOHISTORY ; 
 int /*<<< orphan*/  URLIS_OPAQUE ; 
 int /*<<< orphan*/  URLIS_URL ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ pUrlIsA (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pUrlIsW (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_UrlIs_null (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_UrlIs(void)
{
    BOOL ret;
    size_t i;
    WCHAR wurl[80];

    if (!pUrlIsA) {
        win_skip("UrlIsA not found\n");
        return;
    }

    test_UrlIs_null(URLIS_APPLIABLE);
    test_UrlIs_null(URLIS_DIRECTORY);
    test_UrlIs_null(URLIS_FILEURL);
    test_UrlIs_null(URLIS_HASQUERY);
    test_UrlIs_null(URLIS_NOHISTORY);
    test_UrlIs_null(URLIS_OPAQUE);
    test_UrlIs_null(URLIS_URL);

    for (i = 0; i < ARRAY_SIZE(TEST_PATH_IS_URL); i++) {
        MultiByteToWideChar(CP_ACP, 0, TEST_PATH_IS_URL[i].path, -1, wurl, ARRAY_SIZE(wurl));

        ret = pUrlIsA( TEST_PATH_IS_URL[i].path, URLIS_URL );
        ok( ret == TEST_PATH_IS_URL[i].expect,
            "returned %d from path %s, expected %d\n", ret, TEST_PATH_IS_URL[i].path,
            TEST_PATH_IS_URL[i].expect );

        if (pUrlIsW) {
            ret = pUrlIsW( wurl, URLIS_URL );
            ok( ret == TEST_PATH_IS_URL[i].expect,
                "returned %d from path (UrlIsW) %s, expected %d\n", ret,
                TEST_PATH_IS_URL[i].path, TEST_PATH_IS_URL[i].expect );
        }
    }
    for (i = 0; i < ARRAY_SIZE(TEST_URLIS_ATTRIBS); i++) {
        MultiByteToWideChar(CP_ACP, 0, TEST_URLIS_ATTRIBS[i].url, -1, wurl, ARRAY_SIZE(wurl));

        ret = pUrlIsA( TEST_URLIS_ATTRIBS[i].url, URLIS_OPAQUE);
	ok( ret == TEST_URLIS_ATTRIBS[i].expectOpaque,
	    "returned %d for URLIS_OPAQUE, url \"%s\", expected %d\n", ret, TEST_URLIS_ATTRIBS[i].url,
	    TEST_URLIS_ATTRIBS[i].expectOpaque );
        ret = pUrlIsA( TEST_URLIS_ATTRIBS[i].url, URLIS_FILEURL);
	ok( ret == TEST_URLIS_ATTRIBS[i].expectFile,
	    "returned %d for URLIS_FILEURL, url \"%s\", expected %d\n", ret, TEST_URLIS_ATTRIBS[i].url,
	    TEST_URLIS_ATTRIBS[i].expectFile );

        if (pUrlIsW) {
            ret = pUrlIsW( wurl, URLIS_OPAQUE);
            ok( ret == TEST_URLIS_ATTRIBS[i].expectOpaque,
                "returned %d for URLIS_OPAQUE (UrlIsW), url \"%s\", expected %d\n",
                ret, TEST_URLIS_ATTRIBS[i].url, TEST_URLIS_ATTRIBS[i].expectOpaque );
            ret = pUrlIsW( wurl, URLIS_FILEURL);
            ok( ret == TEST_URLIS_ATTRIBS[i].expectFile,
                "returned %d for URLIS_FILEURL (UrlIsW), url \"%s\", expected %d\n",
                ret, TEST_URLIS_ATTRIBS[i].url, TEST_URLIS_ATTRIBS[i].expectFile );
        }
    }
}