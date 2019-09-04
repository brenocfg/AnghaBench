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
typedef  int /*<<< orphan*/ * HIMAGELIST ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  ILC_COLOR16 ; 
 int /*<<< orphan*/  ILC_COLORDDB ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/ * pImageList_Create (int,int,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ pImageList_Destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pImageList_GetIconSize (int /*<<< orphan*/ *,int*,int*) ; 
 int pImageList_GetImageCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pImageList_SetImageCount (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void test_create_destroy(void)
{
    HIMAGELIST himl;
    INT cx, cy;
    BOOL rc;
    INT ret;

    /* list with zero or negative image dimensions */
    himl = pImageList_Create(0, 0, ILC_COLOR16, 0, 3);
    ok(himl == NULL, "got %p\n", himl);

    himl = pImageList_Create(0, 16, ILC_COLOR16, 0, 3);
    ok(himl == NULL, "got %p\n", himl);

    himl = pImageList_Create(16, 0, ILC_COLOR16, 0, 3);
    ok(himl == NULL, "got %p\n", himl);

    himl = pImageList_Create(16, -1, ILC_COLOR16, 0, 3);
    ok(himl == NULL, "got %p\n", himl);

    himl = pImageList_Create(-1, 16, ILC_COLOR16, 0, 3);
    ok(himl == NULL, "got %p\n", himl);

    rc = pImageList_Destroy((HIMAGELIST)0xdeadbeef);
    ok(rc == FALSE, "ImageList_Destroy(0xdeadbeef) should fail and not crash\n");

    /* DDB image lists */
    himl = pImageList_Create(0, 14, ILC_COLORDDB, 4, 4);
    ok(himl != NULL, "got %p\n", himl);

    pImageList_GetIconSize(himl, &cx, &cy);
    ok (cx == 0, "Wrong cx (%i)\n", cx);
    ok (cy == 14, "Wrong cy (%i)\n", cy);
    pImageList_Destroy(himl);

    himl = pImageList_Create(0, 0, ILC_COLORDDB, 4, 4);
    ok(himl != NULL, "got %p\n", himl);
    pImageList_GetIconSize(himl, &cx, &cy);
    ok (cx == 0, "Wrong cx (%i)\n", cx);
    ok (cy == 0, "Wrong cy (%i)\n", cy);
    pImageList_Destroy(himl);

    himl = pImageList_Create(0, 0, ILC_COLORDDB, 0, 4);
    ok(himl != NULL, "got %p\n", himl);
    pImageList_GetIconSize(himl, &cx, &cy);
    ok (cx == 0, "Wrong cx (%i)\n", cx);
    ok (cy == 0, "Wrong cy (%i)\n", cy);

    pImageList_SetImageCount(himl, 3);
    ret = pImageList_GetImageCount(himl);
    ok(ret == 3, "Unexpected image count after increase\n");

    /* Trying to actually add an image causes a crash on Windows */
    pImageList_Destroy(himl);

    /* Negative values fail */
    himl = pImageList_Create(-1, -1, ILC_COLORDDB, 4, 4);
    ok(himl == NULL, "got %p\n", himl);
    himl = pImageList_Create(-1, 1, ILC_COLORDDB, 4, 4);
    ok(himl == NULL, "got %p\n", himl);
    himl = pImageList_Create(1, -1, ILC_COLORDDB, 4, 4);
    ok(himl == NULL, "got %p\n", himl);
}