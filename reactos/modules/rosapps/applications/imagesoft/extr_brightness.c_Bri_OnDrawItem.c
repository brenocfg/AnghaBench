#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_7__ {scalar_t__ CtlID; int /*<<< orphan*/  hDC; } ;
struct TYPE_5__ {int /*<<< orphan*/  bottom; int /*<<< orphan*/  right; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct TYPE_6__ {TYPE_1__ ImageRect; int /*<<< orphan*/  hPreviewBitmap; } ;
typedef  TYPE_2__* PIMAGEADJUST ;
typedef  TYPE_3__* LPDRAWITEMSTRUCT ;
typedef  scalar_t__ LPARAM ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  BitBlt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateCompatibleDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ ) ; 
 scalar_t__ IDC_PICPREVIEW ; 
 int /*<<< orphan*/  SRCCOPY ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static VOID
Bri_OnDrawItem(PIMAGEADJUST pImgAdj,
           LPARAM lParam)
{
    LPDRAWITEMSTRUCT lpDrawItem;
    HDC hdcMem;

    lpDrawItem = (LPDRAWITEMSTRUCT)lParam;

    hdcMem = CreateCompatibleDC(lpDrawItem->hDC);

    if(lpDrawItem->CtlID == IDC_PICPREVIEW)
    {
        SelectObject(hdcMem,
                     pImgAdj->hPreviewBitmap);

        BitBlt(lpDrawItem->hDC,
               pImgAdj->ImageRect.left,
               pImgAdj->ImageRect.top,
               pImgAdj->ImageRect.right,
               pImgAdj->ImageRect.bottom,
               hdcMem,
               0,
               0,
               SRCCOPY);

        DeleteDC(hdcMem);
    }
}