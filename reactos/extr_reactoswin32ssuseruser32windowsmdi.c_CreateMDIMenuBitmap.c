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
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  HBITMAP ;

/* Variables and functions */
 int /*<<< orphan*/  BLACK_PEN ; 
 int /*<<< orphan*/  BitBlt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateCompatibleBitmap (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  CreateCompatibleDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetStockObject (int /*<<< orphan*/ ) ; 
 scalar_t__ GetSystemMetrics (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LineTo (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LoadBitmapW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKEINTRESOURCEW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MoveToEx (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OBM_OLD_CLOSE ; 
 int /*<<< orphan*/  SM_CXSIZE ; 
 int /*<<< orphan*/  SM_CYSIZE ; 
 int /*<<< orphan*/  SRCCOPY ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HBITMAP CreateMDIMenuBitmap(void)
{
 HDC 		hDCSrc  = CreateCompatibleDC(0);
 HDC		hDCDest	= CreateCompatibleDC(hDCSrc);
 HBITMAP	hbClose = LoadBitmapW(0, MAKEINTRESOURCEW(OBM_OLD_CLOSE) );
 HBITMAP	hbCopy;
 HBITMAP	hobjSrc, hobjDest;

 hobjSrc = SelectObject(hDCSrc, hbClose);
 hbCopy = CreateCompatibleBitmap(hDCSrc,GetSystemMetrics(SM_CXSIZE),GetSystemMetrics(SM_CYSIZE));
 hobjDest = SelectObject(hDCDest, hbCopy);

 BitBlt(hDCDest, 0, 0, GetSystemMetrics(SM_CXSIZE), GetSystemMetrics(SM_CYSIZE),
          hDCSrc, GetSystemMetrics(SM_CXSIZE), 0, SRCCOPY);

 SelectObject(hDCSrc, hobjSrc);
 DeleteObject(hbClose);
 DeleteDC(hDCSrc);

 hobjSrc = SelectObject( hDCDest, GetStockObject(BLACK_PEN) );

 MoveToEx( hDCDest, GetSystemMetrics(SM_CXSIZE) - 1, 0, NULL );
 LineTo( hDCDest, GetSystemMetrics(SM_CXSIZE) - 1, GetSystemMetrics(SM_CYSIZE) - 1);

 SelectObject(hDCDest, hobjSrc );
 SelectObject(hDCDest, hobjDest);
 DeleteDC(hDCDest);

 return hbCopy;
}