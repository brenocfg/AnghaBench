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
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/ * HIMAGELIST ;
typedef  int /*<<< orphan*/  HBITMAP ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_UNREFERENCED_LOCAL_VARIABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int ILC_COLOR24 ; 
 int ILC_MASK ; 
 int /*<<< orphan*/  IMAGE_BITMAP ; 
 int /*<<< orphan*/  ImageList_AddMasked (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ImageList_Create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LR_LOADTRANSPARENT ; 
 int /*<<< orphan*/  LoadImage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKEINTRESOURCE (scalar_t__) ; 
 int /*<<< orphan*/  RGB (int,int,int) ; 
 int /*<<< orphan*/  TB_BMP_HEIGHT ; 
 int /*<<< orphan*/  TB_BMP_WIDTH ; 
 int /*<<< orphan*/  hInstance ; 

HIMAGELIST
InitImageList(UINT NumImages, UINT StartResource)
{
    HBITMAP hBitmap;
    HIMAGELIST hImageList;
    UINT i, k;
    INT Ret;
    DBG_UNREFERENCED_LOCAL_VARIABLE(Ret);

    /* Create the toolbar icon image list */
    hImageList = ImageList_Create(TB_BMP_WIDTH,
                                  TB_BMP_HEIGHT,
                                  ILC_MASK | ILC_COLOR24,
                                  NumImages,
                                  0);
    if (! hImageList)
        return NULL;

    /* Add all icons to the image list */
    for (i = StartResource, k = 0; k < NumImages; i++, k++)
    {
        hBitmap = LoadImage(hInstance,
                            MAKEINTRESOURCE(i),
                            IMAGE_BITMAP,
                            TB_BMP_WIDTH,
                            TB_BMP_HEIGHT,
                            LR_LOADTRANSPARENT);

        Ret = ImageList_AddMasked(hImageList,
                                  hBitmap,
                                  RGB(255, 255, 254));

        DeleteObject(hBitmap);
    }

    return hImageList;

}