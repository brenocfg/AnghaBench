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
typedef  int uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  runtest (int,char*,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int const**,size_t*)) ; 
 int /*<<< orphan*/  test_iterators (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int const**,size_t*) ; 
 int /*<<< orphan*/  testannexbin (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int const**,size_t*) ; 

__attribute__((used)) static void test_annexb()
{
    const uint8_t *p_res[3];
    size_t rgi_res[3];

    /* Full mixed set */
    const uint8_t test1_annexbdata[] = { 0, 0, 0, 1, 0x55, 0x55, 0x55, 0x55, 0x55,
                                         0, 0, 1, 0x22, 0x22,
                                         0, 0, 0, 1, 0x11,
                                         0, 0, 1, 0x11,
                                         0, 0, 0, 1, 0x33, 0x33, 0x33, };
    const uint8_t test1_avcdata1[] = { 5, 0x55, 0x55, 0x55, 0x55, 0x55,
                                       2, 0x22, 0x22,
                                       1, 0x11,
                                       1, 0x11,
                                       3, 0x33, 0x33, 0x33, };
    const uint8_t test1_avcdata2[] = { 0, 5, 0x55, 0x55, 0x55, 0x55, 0x55,
                                       0, 2, 0x22, 0x22,
                                       0, 1, 0x11,
                                       0, 1, 0x11,
                                       0, 3, 0x33, 0x33, 0x33, };
    const uint8_t test1_avcdata4[] = { 0, 0, 0, 5, 0x55, 0x55, 0x55, 0x55, 0x55,
                                       0, 0, 0, 2, 0x22, 0x22,
                                       0, 0, 0, 1, 0x11,
                                       0, 0, 0, 1, 0x11,
                                       0, 0, 0, 3, 0x33, 0x33, 0x33, };

    /* single nal test */
    const uint8_t test2_annexbdata[] = { 0, 0, 0, 1, 0x55, 0x55, 0x55, 0x55, 0x55 };
    const uint8_t test2_avcdata1[]   = { 5, 0x55, 0x55, 0x55, 0x55, 0x55 };
    const uint8_t test2_avcdata2[]   = { 0, 5, 0x55, 0x55, 0x55, 0x55, 0x55 };
    const uint8_t test2_avcdata4[]   = { 0, 0, 0, 5, 0x55, 0x55, 0x55, 0x55, 0x55 };

    /* single nal test, startcode 3 */
    const uint8_t test3_annexbdata[] = { 0, 0, 1, 0x11 };
    const uint8_t test3_avcdata1[] =   { 1, 0x11 };
    const uint8_t test3_avcdata2[] =   { 0, 1, 0x11 };
    const uint8_t test3_avcdata4[] =   { 0, 0, 0, 1, 0x11 };

    /* empty nal test */
    const uint8_t test4_annexbdata[] = { 0, 0, 1 };
    const uint8_t test4_avcdata1[]   = { 0 };
    const uint8_t test4_avcdata2[]   = { 0, 0 };
    const uint8_t test4_avcdata4[]   = { 0, 0, 0, 0 };

    /* 4 bytes prefixed nal only (4 prefix optz) */
    const uint8_t test5_annexbdata[] = { 0, 0, 0, 1, 0x11, 0, 0, 0, 1, 0x22, 0x22 };
    const uint8_t test5_avcdata1[]   = { 1, 0x11, 2, 0x22, 0x22 };
    const uint8_t test5_avcdata2[]   = { 0, 1, 0x11, 0, 2, 0x22, 0x22 };
    const uint8_t test5_avcdata4[]   = { 0, 0, 0, 1, 0x11, 0, 0, 0, 2, 0x22, 0x22 };

    /* startcode repeat / empty nal */
    const uint8_t test6_annexbdata[] = { 0, 0, 1, 0x11, 0, 0, 1, 0, 0, 1 };
    const uint8_t test6_avcdata1[] =   { 1, 0x11, 0, 0 };
    const uint8_t test6_avcdata2[] =   { 0, 1, 0x11, 0, 0, 0, 0 };
    const uint8_t test6_avcdata4[] =   { 0, 0, 0, 1, 0x11, 0, 0, 0, 0, 0, 0, 0, 0 };

    /* empty nal variation test */
    const uint8_t test7_annexbdata[] = { 0, 0, 0, 1 };
    const uint8_t test7_avcdata1[]   = { 0 };
    const uint8_t test7_avcdata2[]   = { 0, 0 };
    const uint8_t test7_avcdata4[]   = { 0, 0, 0, 0 };

    runtest(4, "empty nal test", testannexbin);
    runtest(2, "single nal test", testannexbin);
    runtest(3, "single nal test, startcode 3", testannexbin);
    runtest(5, "4 bytes prefixed nal only (4 prefix optz)", testannexbin);
    runtest(1, "mixed nal set", testannexbin);
    runtest(6, "startcode repeat / empty nal", testannexbin);

    runtest(1, "IT mixed nal set", test_iterators);
    runtest(2, "IT single nal test", test_iterators);
    runtest(3, "IT single nal test, startcode 3", test_iterators);
    runtest(4, "IT empty nal test", test_iterators);
    runtest(5, "IT 4 bytes prefixed nal only (4 prefix optz)", test_iterators);
    runtest(6, "startcode repeat / empty nal", test_iterators);
    runtest(7, "IT empty nal", test_iterators);

    printf("\nTEST 8 borkage test\n");\
    rgi_res[0] = 0;
    rgi_res[1] = rgi_res[2] = 1;
    p_res[0] = NULL;
    p_res[1] = p_res[2] = test7_avcdata1;
    test_iterators( NULL, 0, p_res, rgi_res );
}