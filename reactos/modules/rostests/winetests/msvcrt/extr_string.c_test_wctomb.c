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
typedef  int mbstate_t ;
typedef  int /*<<< orphan*/  dst ;

/* Variables and functions */
 int EILSEQ ; 
 int /*<<< orphan*/  LC_ALL ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 size_t p_wcrtomb (char*,int,int*) ; 
 int p_wcrtomb_s (size_t*,char*,int,int,int*) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_wctomb(void)
{
    mbstate_t state;
    unsigned char dst[10];
    size_t ret;
    int err;

    if(!p_wcrtomb || !setlocale(LC_ALL, "Japanese_Japan.932")) {
        win_skip("wcrtomb tests\n");
        return;
    }

    ret = p_wcrtomb(NULL, 0x3042, NULL);
    ok(ret == 2, "wcrtomb did not return 2\n");

    state = 1;
    dst[2] = 'a';
    ret = p_wcrtomb((char*)dst, 0x3042, &state);
    ok(ret == 2, "wcrtomb did not return 2\n");
    ok(state == 0, "state != 0\n");
    ok(dst[0] == 0x82, "dst[0] = %x, expected 0x82\n", dst[0]);
    ok(dst[1] == 0xa0, "dst[1] = %x, expected 0xa0\n", dst[1]);
    ok(dst[2] == 'a', "dst[2] != 'a'\n");

    ret = p_wcrtomb((char*)dst, 0x3043, NULL);
    ok(ret == 2, "wcrtomb did not return 2\n");
    ok(dst[0] == 0x82, "dst[0] = %x, expected 0x82\n", dst[0]);
    ok(dst[1] == 0xa1, "dst[1] = %x, expected 0xa1\n", dst[1]);

    ret = p_wcrtomb((char*)dst, 0x20, NULL);
    ok(ret == 1, "wcrtomb did not return 1\n");
    ok(dst[0] == 0x20, "dst[0] = %x, expected 0x20\n", dst[0]);

    ret = p_wcrtomb((char*)dst, 0xffff, NULL);
    ok(ret == -1, "wcrtomb did not return -1\n");
    ok(dst[0] == 0x3f, "dst[0] = %x, expected 0x3f\n", dst[0]);

    if(!p_wcrtomb_s) {
        win_skip("wcrtomb_s tests\n");
        setlocale(LC_ALL, "C");
        return;
    }

    state = 1;
    dst[2] = 'a';
    err = p_wcrtomb_s(&ret, (char*)dst, sizeof(dst), 0x3042, &state);
    ok(!err, "err = %d\n", err);
    ok(ret == 2, "ret != 2\n");
    ok(!state, "state != 0\n");
    ok(dst[0] == 0x82, "dst[0] = %x, expected 0x82\n", dst[0]);
    ok(dst[1] == 0xa0, "dst[1] = %x, expected 0xa0\n", dst[1]);
    ok(dst[2] == 'a', "dst[2] != 'a'\n");

    err = p_wcrtomb_s(&ret, (char*)dst, sizeof(dst), 0x3042, NULL);
    ok(!err, "err = %d\n", err);
    ok(ret == 2, "ret != 2\n");
    ok(!state, "state != 0\n");
    ok(dst[0] == 0x82, "dst[0] = %x, expected 0x82\n", dst[0]);
    ok(dst[1] == 0xa0, "dst[1] = %x, expected 0xa0\n", dst[1]);

    err = p_wcrtomb_s(&ret, (char*)dst, sizeof(dst), 0x20, NULL);
    ok(!err, "err = %d\n", err);
    ok(ret == 1, "ret != 1\n");
    ok(dst[0] == 0x20, "dst[0] = %x, expected 0x20\n", dst[0]);

    err = p_wcrtomb_s(&ret, NULL, 0, 0x20, NULL);
    ok(!err, "err = %d\n", err);
    ok(ret == 1, "ret != 1\n");

    err = p_wcrtomb_s(&ret, (char*)dst, sizeof(dst), 0xffff, NULL);
    ok(err == EILSEQ, "err = %d\n", err);
    ok(ret == -1, "wcrtomb did not return -1\n");
    ok(dst[0] == 0x3f, "dst[0] = %x, expected 0x3f\n", dst[0]);

    setlocale(LC_ALL, "C");
}