#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_6__ {scalar_t__ top; scalar_t__ left; scalar_t__ bottom; scalar_t__ right; } ;
struct TYPE_8__ {TYPE_1__ rcPaint; } ;
struct TYPE_7__ {int /*<<< orphan*/  hDCMem; scalar_t__ hBitmap; } ;
typedef  TYPE_2__* PEDIT_WND_INFO ;
typedef  TYPE_3__* LPPAINTSTRUCT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  scalar_t__ HBITMAP ;

/* Variables and functions */
 int /*<<< orphan*/  BitBlt (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SRCCOPY ; 
 scalar_t__ SelectObject (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static VOID
ImageEditWndRepaint(PEDIT_WND_INFO Info,
                    HDC hDC,
                    LPPAINTSTRUCT lpps)
{
    HBITMAP hOldBitmap;

    if (Info->hBitmap)
    {
        hOldBitmap = (HBITMAP) SelectObject(Info->hDCMem,
                                            Info->hBitmap);

        BitBlt(hDC,
               lpps->rcPaint.left,
               lpps->rcPaint.top,
               lpps->rcPaint.right - lpps->rcPaint.left,
               lpps->rcPaint.bottom - lpps->rcPaint.top,
               Info->hDCMem,
               lpps->rcPaint.left,
               lpps->rcPaint.top,
               SRCCOPY);

        Info->hBitmap = SelectObject(Info->hDCMem, hOldBitmap);
    }
}