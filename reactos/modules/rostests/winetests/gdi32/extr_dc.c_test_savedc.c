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
typedef  int /*<<< orphan*/ * HDC ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateDCA (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ *) ; 
 int RestoreDC (int /*<<< orphan*/ *,int) ; 
 int SaveDC (int /*<<< orphan*/ *) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 

__attribute__((used)) static void test_savedc(void)
{
    HDC hdc = CreateDCA("DISPLAY", NULL, NULL, NULL);
    int ret;

    ok(hdc != NULL, "CreateDC rets %p\n", hdc);

    ret = SaveDC(hdc);
    ok(ret == 1, "ret = %d\n", ret);
    ret = SaveDC(hdc);
    ok(ret == 2, "ret = %d\n", ret);
    ret = SaveDC(hdc);
    ok(ret == 3, "ret = %d\n", ret);
    ret = RestoreDC(hdc, -1);
    ok(ret, "ret = %d\n", ret);
    ret = SaveDC(hdc);
    ok(ret == 3, "ret = %d\n", ret);
    ret = RestoreDC(hdc, 1);
    ok(ret, "ret = %d\n", ret);
    ret = SaveDC(hdc);
    ok(ret == 1, "ret = %d\n", ret);
    ret = SaveDC(hdc);
    ok(ret == 2, "ret = %d\n", ret);
    ret = SaveDC(hdc);
    ok(ret == 3, "ret = %d\n", ret);
    ret = RestoreDC(hdc, -2);
    ok(ret, "ret = %d\n", ret);
    ret = SaveDC(hdc);
    ok(ret == 2, "ret = %d\n", ret);
    ret = RestoreDC(hdc, -2);
    ok(ret, "ret = %d\n", ret);
    ret = SaveDC(hdc);
    ok(ret == 1, "ret = %d\n", ret);
    ret = SaveDC(hdc);
    ok(ret == 2, "ret = %d\n", ret); 
    ret = RestoreDC(hdc, -4);
    ok(!ret, "ret = %d\n", ret);
    ret = RestoreDC(hdc, 3);
    ok(!ret, "ret = %d\n", ret);

    /* Under Win9x the following RestoreDC call succeeds and clears the save stack. */
    ret = RestoreDC(hdc, -3);
    ok(!ret ||
       broken(ret), /* Win9x */
       "ret = %d\n", ret);

    /* Trying to clear an empty save stack fails. */
    ret = RestoreDC(hdc, -3);
    ok(!ret, "ret = %d\n", ret);

    ret = SaveDC(hdc);
    ok(ret == 3 ||
       broken(ret == 1), /* Win9x */
       "ret = %d\n", ret);

    /* Under Win9x the following RestoreDC call succeeds and clears the save stack. */
    ret = RestoreDC(hdc, 0);
    ok(!ret ||
       broken(ret), /* Win9x */
       "ret = %d\n", ret);

    /* Trying to clear an empty save stack fails. */
    ret = RestoreDC(hdc, 0);
    ok(!ret, "ret = %d\n", ret);

    ret = RestoreDC(hdc, 1);
    ok(ret ||
       broken(!ret), /* Win9x */
       "ret = %d\n", ret);

    DeleteDC(hdc);
}