#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  hSelf; scalar_t__ Height; scalar_t__ Width; int /*<<< orphan*/  hDC; int /*<<< orphan*/ * hBitmap; } ;
struct TYPE_5__ {scalar_t__ top; scalar_t__ bottom; scalar_t__ left; scalar_t__ right; } ;
typedef  TYPE_1__ RECT ;
typedef  TYPE_2__* PSCREENSHOT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BitBlt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CreateCompatibleBitmap (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  CreateCompatibleDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetError () ; 
 int /*<<< orphan*/  GetWindowRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SRCCOPY ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL
CaptureScreen(PSCREENSHOT pScrSht)
{
    HDC ScreenDC;
    RECT rect;

    /* get window resolution */
    //pScrSht->Width = GetSystemMetrics(SM_CXSCREEN);
    //pScrSht->Height = GetSystemMetrics(SM_CYSCREEN);

    GetWindowRect(pScrSht->hSelf, &rect);
    pScrSht->Width = rect.right - rect.left;
    pScrSht->Height = rect.bottom - rect.top;

    /* get a DC for the screen */
    if (!(ScreenDC = GetDC(pScrSht->hSelf)))
        return FALSE;

    /* get a bitmap handle for the screen
     * needed to convert to a DIB */
    pScrSht->hBitmap = CreateCompatibleBitmap(ScreenDC,
                                              pScrSht->Width,
                                              pScrSht->Height);
    if (pScrSht->hBitmap == NULL)
    {
        GetError();
        ReleaseDC(pScrSht->hSelf, ScreenDC);
        return FALSE;
    }

    /* get a DC compatable with the screen DC */
    if (!(pScrSht->hDC = CreateCompatibleDC(ScreenDC)))
    {
        GetError();
        ReleaseDC(pScrSht->hSelf, ScreenDC);
        return FALSE;
    }

    /* select the bitmap into the DC */
    SelectObject(pScrSht->hDC,
                 pScrSht->hBitmap);

    /* copy the screen DC to the bitmap */
    BitBlt(pScrSht->hDC,
           0,
           0,
           pScrSht->Width,
           pScrSht->Height,
           ScreenDC,
           0,
           0,
           SRCCOPY);

    /* we're finished with the screen DC */
    ReleaseDC(pScrSht->hSelf, ScreenDC);

    return TRUE;
}