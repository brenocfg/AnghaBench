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
typedef  int INT ;
typedef  int /*<<< orphan*/ * HIMAGELIST ;
typedef  int /*<<< orphan*/ * HICON ;

/* Variables and functions */
 int /*<<< orphan*/  DestroyIcon (int /*<<< orphan*/ *) ; 
 int ILC_COLOR32 ; 
 int ILC_MASK ; 
 int /*<<< orphan*/  IMAGE_ICON ; 
 int ImageList_AddIcon (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ImageList_Create (scalar_t__,scalar_t__,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ImageList_Destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LR_DEFAULTCOLOR ; 
 scalar_t__ LoadImageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKEINTRESOURCEW (scalar_t__) ; 
 int /*<<< orphan*/  hInstance ; 

HIMAGELIST
InitImageList(UINT StartResource,
              UINT EndResource,
              UINT Width,
              UINT Height)
{
    HICON hIcon;
    HIMAGELIST hImageList;
    UINT i;
    INT Ret;

    /* Create the toolbar icon image list */
    hImageList = ImageList_Create(Width,
                                  Height,
                                  ILC_MASK | ILC_COLOR32,
                                  EndResource - StartResource,
                                  0);
    if (hImageList == NULL)
        return NULL;

    /* Add all icons to the image list */
    for (i = StartResource; i <= EndResource; i++)
    {
        hIcon = (HICON)LoadImageW(hInstance,
                                  MAKEINTRESOURCEW(i),
                                  IMAGE_ICON,
                                  Width,
                                  Height,
                                  LR_DEFAULTCOLOR);
        if (hIcon == NULL)
            goto fail;

        Ret = ImageList_AddIcon(hImageList,
                                hIcon);
        if (Ret == -1)
            goto fail;

        DestroyIcon(hIcon);
    }

    return hImageList;

fail:
    ImageList_Destroy(hImageList);
    return NULL;
}