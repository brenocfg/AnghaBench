#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nmgd ;
struct TYPE_11__ {int dwMask; int iImage; int /*<<< orphan*/  hdr; int /*<<< orphan*/  lParam; int /*<<< orphan*/  idCommand; } ;
struct TYPE_10__ {scalar_t__ iBitmap; int /*<<< orphan*/  dwData; int /*<<< orphan*/  idCommand; } ;
struct TYPE_9__ {int /*<<< orphan*/  nNumBitmaps; } ;
typedef  TYPE_1__ TOOLBAR_INFO ;
typedef  TYPE_2__ TBUTTON_INFO ;
typedef  TYPE_3__ NMTBDISPINFOW ;
typedef  scalar_t__ INT ;

/* Variables and functions */
 scalar_t__ GETIBITMAP (TYPE_1__ const*,scalar_t__) ; 
 scalar_t__ I_IMAGECALLBACK ; 
 scalar_t__ I_IMAGENONE ; 
 int TBNF_DI_SETITEM ; 
 int TBNF_IMAGE ; 
 int /*<<< orphan*/  TBN_GETDISPINFOW ; 
 int /*<<< orphan*/  TOOLBAR_SendNotify (int /*<<< orphan*/ *,TYPE_1__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static INT
TOOLBAR_GetBitmapIndex(const TOOLBAR_INFO *infoPtr, TBUTTON_INFO *btnPtr)
{
    INT ret = btnPtr->iBitmap;

    if (ret == I_IMAGECALLBACK)
    {
        /* issue TBN_GETDISPINFO */
        NMTBDISPINFOW nmgd;

        memset(&nmgd, 0, sizeof(nmgd));
        nmgd.idCommand = btnPtr->idCommand;
        nmgd.lParam = btnPtr->dwData;
        nmgd.dwMask = TBNF_IMAGE;
        nmgd.iImage = -1;
        /* Windows also send TBN_GETDISPINFOW even if the control is ANSI */
        TOOLBAR_SendNotify(&nmgd.hdr, infoPtr, TBN_GETDISPINFOW);
        if (nmgd.dwMask & TBNF_DI_SETITEM)
            btnPtr->iBitmap = nmgd.iImage;
        ret = nmgd.iImage;
        TRACE("TBN_GETDISPINFO returned bitmap id %d, mask=%08x, nNumBitmaps=%d\n",
            ret, nmgd.dwMask, infoPtr->nNumBitmaps);
    }

    if (ret != I_IMAGENONE)
        ret = GETIBITMAP(infoPtr, ret);

    return ret;
}