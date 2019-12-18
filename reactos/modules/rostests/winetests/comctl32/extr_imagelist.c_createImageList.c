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
typedef  int /*<<< orphan*/ * HIMAGELIST ;
typedef  int /*<<< orphan*/  HBITMAP ;

/* Variables and functions */
 int /*<<< orphan*/  CreateBitmap (int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ILC_COLOR ; 
 int /*<<< orphan*/  bitmap_bits ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  pImageList_Add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pImageList_Create (int,int,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static HIMAGELIST createImageList(int cx, int cy)
{
    /* Create an ImageList and put an image into it */
    HIMAGELIST himl = pImageList_Create(cx, cy, ILC_COLOR, 1, 1);
    HBITMAP hbm = CreateBitmap(48, 48, 1, 1, bitmap_bits);

    ok(himl != NULL, "Failed to create image list, %d x %d.\n", cx, cy);
    pImageList_Add(himl, hbm, NULL);
    DeleteObject(hbm);
    return himl;
}