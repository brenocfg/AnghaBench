#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ cCurImage; scalar_t__ cMaxImage; scalar_t__ cGrow; int flags; char* has_alpha; scalar_t__ hbmMask; int /*<<< orphan*/  hdcMask; scalar_t__ hbmImage; int /*<<< orphan*/  hdcImage; } ;
struct TYPE_8__ {scalar_t__ cx; scalar_t__ cy; } ;
typedef  TYPE_1__ SIZE ;
typedef  scalar_t__ INT ;
typedef  TYPE_2__* HIMAGELIST ;
typedef  int /*<<< orphan*/  HDC ;
typedef  scalar_t__ HBITMAP ;

/* Variables and functions */
 int /*<<< orphan*/  BitBlt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ CreateBitmap (scalar_t__,scalar_t__,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CreateCompatibleDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (scalar_t__) ; 
 int /*<<< orphan*/  ERR (char*,...) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 char* HeapReAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int ILC_MASK ; 
 scalar_t__ ImageList_CreateImage (int /*<<< orphan*/ ,TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  SRCCOPY ; 
 scalar_t__ SelectObject (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  heap_free (char*) ; 
 int /*<<< orphan*/  imagelist_get_bitmap_size (TYPE_2__*,scalar_t__,TYPE_1__*) ; 
 scalar_t__ max (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
IMAGELIST_InternalExpandBitmaps(HIMAGELIST himl, INT nImageCount)
{
    HDC     hdcBitmap;
    HBITMAP hbmNewBitmap, hbmNull;
    INT     nNewCount;
    SIZE    sz;

    TRACE("%p has allocated %d, max %d, grow %d images\n", himl, himl->cCurImage, himl->cMaxImage, himl->cGrow);

    if (himl->cCurImage + nImageCount < himl->cMaxImage)
        return;

    nNewCount = himl->cMaxImage + max(nImageCount, himl->cGrow) + 1;

    imagelist_get_bitmap_size(himl, nNewCount, &sz);

    TRACE("Create expanded bitmaps : himl=%p x=%d y=%d count=%d\n", himl, sz.cx, sz.cy, nNewCount);
    hdcBitmap = CreateCompatibleDC (0);

    hbmNewBitmap = ImageList_CreateImage(hdcBitmap, himl, nNewCount);

    if (hbmNewBitmap == 0)
        ERR("creating new image bitmap (x=%d y=%d)!\n", sz.cx, sz.cy);

    if (himl->cCurImage)
    {
        hbmNull = SelectObject (hdcBitmap, hbmNewBitmap);
        BitBlt (hdcBitmap, 0, 0, sz.cx, sz.cy,
                himl->hdcImage, 0, 0, SRCCOPY);
        SelectObject (hdcBitmap, hbmNull);
    }
    SelectObject (himl->hdcImage, hbmNewBitmap);
    DeleteObject (himl->hbmImage);
    himl->hbmImage = hbmNewBitmap;

    if (himl->flags & ILC_MASK)
    {
        hbmNewBitmap = CreateBitmap (sz.cx, sz.cy, 1, 1, NULL);

        if (hbmNewBitmap == 0)
            ERR("creating new mask bitmap!\n");

	if(himl->cCurImage)
	{
	    hbmNull = SelectObject (hdcBitmap, hbmNewBitmap);
	    BitBlt (hdcBitmap, 0, 0, sz.cx, sz.cy,
		    himl->hdcMask, 0, 0, SRCCOPY);
	    SelectObject (hdcBitmap, hbmNull);
	}
        SelectObject (himl->hdcMask, hbmNewBitmap);
        DeleteObject (himl->hbmMask);
        himl->hbmMask = hbmNewBitmap;
    }

    if (himl->has_alpha)
    {
        char *new_alpha = HeapReAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, himl->has_alpha, nNewCount );
        if (new_alpha) himl->has_alpha = new_alpha;
        else
        {
            heap_free( himl->has_alpha );
            himl->has_alpha = NULL;
        }
    }

    himl->cMaxImage = nNewCount;

    DeleteDC (hdcBitmap);
}