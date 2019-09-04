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
typedef  int /*<<< orphan*/ * HWND ;
typedef  int /*<<< orphan*/ * HIMAGELIST ;

/* Variables and functions */
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAKELONG (int,int) ; 
 int SendMessageA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TB_GETIMAGELIST ; 
 int /*<<< orphan*/  TB_SETBITMAPSIZE ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int /*<<< orphan*/  rebuild_toolbar (int /*<<< orphan*/ **) ; 

__attribute__((used)) static void test_imagelist(void)
{
    HIMAGELIST imagelist;
    HWND hwnd = NULL;
    int ret;

    rebuild_toolbar(&hwnd);

    imagelist = (HIMAGELIST)SendMessageA(hwnd, TB_GETIMAGELIST, 0, 0);
    ok(imagelist == NULL, "got %p\n", imagelist);

    ret = SendMessageA(hwnd, TB_SETBITMAPSIZE, 0, MAKELONG(16, 16));
    ok(ret, "got %d\n", ret);

    imagelist = (HIMAGELIST)SendMessageA(hwnd, TB_GETIMAGELIST, 0, 0);
    ok(imagelist == NULL, "got %p\n", imagelist);

    DestroyWindow(hwnd);
}