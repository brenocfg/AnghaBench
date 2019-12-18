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
typedef  int INT ;
typedef  int /*<<< orphan*/  HIMAGELIST ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ILC_COLOR16 ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int /*<<< orphan*/  pImageList_Create (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pImageList_Destroy (int /*<<< orphan*/ ) ; 
 int pImageList_GetIconSize (int /*<<< orphan*/ ,int*,int*) ; 

__attribute__((used)) static void test_iconsize(void)
{
    HIMAGELIST himl;
    INT cx, cy;
    BOOL ret;

    himl = pImageList_Create(16, 16, ILC_COLOR16, 0, 3);
    /* null pointers, not zero imagelist dimensions */
    ret = pImageList_GetIconSize(himl, NULL, NULL);
    ok(!ret, "got %d\n", ret);

    /* doesn't touch return pointers */
    cx = 0x1abe11ed;
    ret = pImageList_GetIconSize(himl, &cx, NULL);
    ok(!ret, "got %d\n", ret);
    ok(cx == 0x1abe11ed, "got %d\n", cx);

    cy = 0x1abe11ed;
    ret = pImageList_GetIconSize(himl, NULL, &cy);
    ok(!ret, "got %d\n", ret);
    ok(cy == 0x1abe11ed, "got %d\n", cy);

    pImageList_Destroy(himl);

    ret = pImageList_GetIconSize((HIMAGELIST)0xdeadbeef, &cx, &cy);
    ok(!ret, "got %d\n", ret);
}