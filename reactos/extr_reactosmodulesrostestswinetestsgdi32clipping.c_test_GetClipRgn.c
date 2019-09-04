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
typedef  int /*<<< orphan*/ * HRGN ;
typedef  int /*<<< orphan*/ * HDC ;

/* Variables and functions */
 int COMPLEXREGION ; 
 int /*<<< orphan*/ * CreateRectRgn (int,int,int,int) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ *) ; 
 int EqualRgn (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int GetClipRgn (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetDC (int /*<<< orphan*/ *) ; 
 int GetSystemMetrics (int /*<<< orphan*/ ) ; 
 int NULLREGION ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int SIMPLEREGION ; 
 int /*<<< orphan*/  SM_CMONITORS ; 
 int SelectClipRgn (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_GetClipRgn(void)
{
    HDC hdc;
    HRGN hrgn, hrgn2, hrgn3, hrgn4;
    int ret;

    /* Test calling GetClipRgn with NULL device context and region handles. */
    ret = GetClipRgn(NULL, NULL);
    ok(ret == -1, "Expected GetClipRgn to return -1, got %d\n", ret);

    hdc = GetDC(NULL);
    ok(hdc != NULL, "Expected GetDC to return a valid device context handle\n");

    /* Test calling GetClipRgn with a valid device context and NULL region. */
    ret = GetClipRgn(hdc, NULL);
    ok(ret == 0 ||
       ret == -1 /* Win9x */,
       "Expected GetClipRgn to return 0, got %d\n", ret);

    /* Initialize the test regions. */
    hrgn = CreateRectRgn(100, 100, 100, 100);
    ok(hrgn != NULL,
       "Expected CreateRectRgn to return a handle to a new rectangular region\n");

    hrgn2 = CreateRectRgn(1, 2, 3, 4);
    ok(hrgn2 != NULL,
       "Expected CreateRectRgn to return a handle to a new rectangular region\n");

    hrgn3 = CreateRectRgn(1, 2, 3, 4);
    ok(hrgn3 != NULL,
       "Expected CreateRectRgn to return a handle to a new rectangular region\n");

    hrgn4 = CreateRectRgn(1, 2, 3, 4);
    ok(hrgn4 != NULL,
       "Expected CreateRectRgn to return a handle to a new rectangular region\n");

    /* Try getting a clipping region from the device context
     * when the device context's clipping region isn't set. */
    ret = GetClipRgn(hdc, hrgn2);
    ok(ret == 0, "Expected GetClipRgn to return 0, got %d\n", ret);

    /* The region passed to GetClipRgn should be unchanged. */
    ret = EqualRgn(hrgn2, hrgn3);
    ok(ret == 1,
       "Expected EqualRgn to compare the two regions as equal, got %d\n", ret);

    /* Try setting and getting back a clipping region. */
    ret = SelectClipRgn(hdc, hrgn);
    ok(ret == NULLREGION,
       "Expected SelectClipRgn to return NULLREGION, got %d\n", ret);

    /* Passing a NULL region handle when the device context
     * has a clipping region results in an error. */
    ret = GetClipRgn(hdc, NULL);
    ok(ret == -1, "Expected GetClipRgn to return -1, got %d\n", ret);

    ret = GetClipRgn(hdc, hrgn2);
    ok(ret == 1, "Expected GetClipRgn to return 1, got %d\n", ret);

    ret = EqualRgn(hrgn, hrgn2);
    ok(ret == 1,
       "Expected EqualRgn to compare the two regions as equal, got %d\n", ret);

    /* Try unsetting and then query the clipping region. */
    ret = SelectClipRgn(hdc, NULL);
    ok(ret == SIMPLEREGION || (ret == COMPLEXREGION && GetSystemMetrics(SM_CMONITORS) > 1),
       "Expected SelectClipRgn to return SIMPLEREGION, got %d\n", ret);

    ret = GetClipRgn(hdc, NULL);
    ok(ret == 0 ||
       ret == -1 /* Win9x */,
       "Expected GetClipRgn to return 0, got %d\n", ret);

    ret = GetClipRgn(hdc, hrgn3);
    ok(ret == 0, "Expected GetClipRgn to return 0, got %d\n", ret);

    ret = EqualRgn(hrgn3, hrgn4);
    ok(ret == 1,
       "Expected EqualRgn to compare the two regions as equal, got %d\n", ret);

    DeleteObject(hrgn4);
    DeleteObject(hrgn3);
    DeleteObject(hrgn2);
    DeleteObject(hrgn);
    ReleaseDC(NULL, hdc);
}