#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bm ;
struct TYPE_15__ {int bmHeight; int /*<<< orphan*/  bmWidth; } ;
struct TYPE_14__ {scalar_t__ hbmColor; scalar_t__ hbmMask; } ;
struct TYPE_10__ {scalar_t__ hicon; } ;
struct TYPE_11__ {TYPE_1__ icon; } ;
struct TYPE_12__ {TYPE_2__ u; } ;
struct TYPE_13__ {int origHeight; TYPE_3__ desc; int /*<<< orphan*/  himetricHeight; int /*<<< orphan*/  origWidth; int /*<<< orphan*/  himetricWidth; } ;
typedef  TYPE_4__ OLEPictureImpl ;
typedef  TYPE_5__ ICONINFO ;
typedef  int /*<<< orphan*/  HDC ;
typedef  TYPE_6__ BITMAP ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteObject (scalar_t__) ; 
 int /*<<< orphan*/  ERR (char*,...) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 scalar_t__ GetIconInfo (scalar_t__,TYPE_5__*) ; 
 int GetObjectW (scalar_t__,int,TYPE_6__*) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__) ; 
 int /*<<< orphan*/  xpixels_to_himetric (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ypixels_to_himetric (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void OLEPictureImpl_SetIcon(OLEPictureImpl * This)
{
    ICONINFO infoIcon;

    TRACE("icon handle %p\n", This->desc.u.icon.hicon);
    if (GetIconInfo(This->desc.u.icon.hicon, &infoIcon)) {
        HDC hdcRef;
        BITMAP bm;

        TRACE("bitmap handle for icon is %p\n", infoIcon.hbmColor);
        if(GetObjectW(infoIcon.hbmColor ? infoIcon.hbmColor : infoIcon.hbmMask, sizeof(bm), &bm) != sizeof(bm)) {
            ERR("GetObject fails on icon bitmap\n");
            return;
        }

        This->origWidth = bm.bmWidth;
        This->origHeight = infoIcon.hbmColor ? bm.bmHeight : bm.bmHeight / 2;
        /* see comment on HIMETRIC on OLEPictureImpl_SetBitmap() */
        hdcRef = GetDC(0);

        This->himetricWidth  = xpixels_to_himetric(This->origWidth, hdcRef);
        This->himetricHeight = ypixels_to_himetric(This->origHeight, hdcRef);

        ReleaseDC(0, hdcRef);

        DeleteObject(infoIcon.hbmMask);
        if (infoIcon.hbmColor) DeleteObject(infoIcon.hbmColor);
    } else {
        ERR("GetIconInfo() fails on icon %p\n", This->desc.u.icon.hicon);
    }
}