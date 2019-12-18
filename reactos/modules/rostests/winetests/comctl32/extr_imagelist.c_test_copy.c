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
typedef  int /*<<< orphan*/  HIMAGELIST ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ILCF_MOVE ; 
 int /*<<< orphan*/  ILC_COLOR ; 
 int /*<<< orphan*/  createImageList (int,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  pImageList_Copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pImageList_Create (int,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pImageList_Destroy (int /*<<< orphan*/ ) ; 
 int pImageList_GetImageCount (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_copy(void)
{
    HIMAGELIST dst, src;
    BOOL ret;
    int count;

    dst = pImageList_Create(5, 11, ILC_COLOR, 1, 1);
    count = pImageList_GetImageCount(dst);
    ok(!count, "ImageList not empty.\n");
    src = createImageList(7, 13);
    count = pImageList_GetImageCount(src);
    ok(count > 2, "Tests need an ImageList with more than 2 images\n");

    /* ImageList_Copy() cannot copy between two ImageLists */
    ret = pImageList_Copy(dst, 0, src, 2, ILCF_MOVE);
    ok(!ret, "ImageList_Copy() should have returned FALSE\n");
    count = pImageList_GetImageCount(dst);
    ok(count == 0, "Expected no image in dst ImageList, got %d\n", count);

    pImageList_Destroy(dst);
    pImageList_Destroy(src);
}