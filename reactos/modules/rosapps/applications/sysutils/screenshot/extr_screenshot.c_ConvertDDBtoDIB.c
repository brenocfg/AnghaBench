#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int WORD ;
struct TYPE_6__ {int biSize; int biWidth; int biHeight; int biPlanes; int biBitCount; int biClrUsed; int biSizeImage; scalar_t__ biClrImportant; int /*<<< orphan*/  biCompression; } ;
struct TYPE_9__ {TYPE_1__ bmiHeader; } ;
struct TYPE_8__ {int bmPlanes; int bmBitsPixel; int bmWidth; int bmHeight; } ;
struct TYPE_7__ {TYPE_4__* lpbi; int /*<<< orphan*/ * lpvBits; int /*<<< orphan*/  Height; int /*<<< orphan*/  hBitmap; int /*<<< orphan*/  hDC; } ;
typedef  int /*<<< orphan*/  RGBQUAD ;
typedef  TYPE_2__* PSCREENSHOT ;
typedef  void* PBITMAPINFO ;
typedef  int /*<<< orphan*/  LPTSTR ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  int /*<<< orphan*/  BITMAPINFOHEADER ;
typedef  TYPE_3__ BITMAP ;

/* Variables and functions */
 int /*<<< orphan*/  BI_RGB ; 
 int /*<<< orphan*/  DIB_RGB_COLORS ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetDIBits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetError () ; 
 int /*<<< orphan*/  GetObjectW (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL
ConvertDDBtoDIB(PSCREENSHOT pScrSht)
{
    INT Ret;
    BITMAP bitmap;
    WORD cClrBits;


/*
    / * can't call GetDIBits with hBitmap selected * /
    //SelectObject(hDC, hOldBitmap);

    / * let GetDIBits fill the lpbi structure by passing NULL pointer * /
    Ret = GetDIBits(hDC,
                    hBitmap,
                    0,
                    Height,
                    NULL,
                    lpbi,
                    DIB_RGB_COLORS);
    if (Ret == 0)
    {
        GetError();
        ReleaseDC(hwnd, hDC);
        HeapFree(GetProcessHeap(), 0, lpbi);
        return -1;
    }
*/

////////////////////////////////////////////////////

	if (!GetObjectW(pScrSht->hBitmap,
                    sizeof(BITMAP),
                    (LPTSTR)&bitmap))
    {
        GetError();
		return FALSE;
	}

	cClrBits = (WORD)(bitmap.bmPlanes * bitmap.bmBitsPixel);
	if (cClrBits == 1)
		cClrBits = 1;
	else if (cClrBits <= 4)
		cClrBits = 4;
	else if (cClrBits <= 8)
		cClrBits = 8;
	else if (cClrBits <= 16)
		cClrBits = 16;
	else if (cClrBits <= 24)
		cClrBits = 24;
	else cClrBits = 32;

  if (cClrBits != 24)
  {
    pScrSht->lpbi = (PBITMAPINFO) HeapAlloc(GetProcessHeap(),
                                            0,
                                            sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * (1 << cClrBits));
  }
  else
  {
    pScrSht->lpbi = (PBITMAPINFO) HeapAlloc(GetProcessHeap(),
                                            0,
                                            sizeof(BITMAPINFOHEADER));
  }

	if (!pScrSht->lpbi)
	{
		GetError();
		return FALSE;
	}

	pScrSht->lpbi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	pScrSht->lpbi->bmiHeader.biWidth = bitmap.bmWidth;
	pScrSht->lpbi->bmiHeader.biHeight = bitmap.bmHeight;
	pScrSht->lpbi->bmiHeader.biPlanes = bitmap.bmPlanes;
	pScrSht->lpbi->bmiHeader.biBitCount = bitmap.bmBitsPixel;

	if (cClrBits < 24)
		pScrSht->lpbi->bmiHeader.biClrUsed = (1 << cClrBits);

	pScrSht->lpbi->bmiHeader.biCompression = BI_RGB;
	pScrSht->lpbi->bmiHeader.biSizeImage = ((pScrSht->lpbi->bmiHeader.biWidth * cClrBits +31) & ~31) /8
                                           * pScrSht->lpbi->bmiHeader.biHeight;

	pScrSht->lpbi->bmiHeader.biClrImportant = 0;

//////////////////////////////////////////////////////

    /* reserve memory to hold the screen bitmap */
    pScrSht->lpvBits = HeapAlloc(GetProcessHeap(),
                                 0,
                                 pScrSht->lpbi->bmiHeader.biSizeImage);
    if (pScrSht->lpvBits == NULL)
    {
        GetError();
        return FALSE;
    }

    /* convert the DDB to a DIB */
    Ret = GetDIBits(pScrSht->hDC,
                    pScrSht->hBitmap,
                    0,
                    pScrSht->Height,
                    pScrSht->lpvBits,
                    pScrSht->lpbi,
                    DIB_RGB_COLORS);
    if (Ret == 0)
    {
        GetError();
        return FALSE;
    }

    return TRUE;

}