#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bm ;
struct TYPE_3__ {int /*<<< orphan*/  bmWidth; int /*<<< orphan*/  bmHeight; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  scalar_t__ HBITMAP ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  TYPE_1__ BITMAP ;

/* Variables and functions */
 int /*<<< orphan*/  CBitHeight ; 
 int /*<<< orphan*/  CBitWidth ; 
 int /*<<< orphan*/  CreateCompatibleDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetObjectW (scalar_t__,int,TYPE_1__*) ; 
 int /*<<< orphan*/  InvertRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ LoadBitmapW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKEINTRESOURCEW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OBM_COMBO ; 
 scalar_t__ SelectObject (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  SetRect (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ hComboBmp ; 

__attribute__((used)) static BOOL COMBO_Init(void)
{
  HDC		hDC;

  if( hComboBmp ) return TRUE;
  if( (hDC = CreateCompatibleDC(0)) )
  {
    BOOL	bRet = FALSE;
    if( (hComboBmp = LoadBitmapW(0, MAKEINTRESOURCEW(OBM_COMBO))) )
    {
      BITMAP      bm;
      HBITMAP     hPrevB;
      RECT        r;

      GetObjectW( hComboBmp, sizeof(bm), &bm );
      CBitHeight = bm.bmHeight;
      CBitWidth  = bm.bmWidth;

      TRACE("combo bitmap [%i,%i]\n", CBitWidth, CBitHeight );

      hPrevB = SelectObject( hDC, hComboBmp);
      SetRect( &r, 0, 0, CBitWidth, CBitHeight );
      InvertRect( hDC, &r );
      SelectObject( hDC, hPrevB );
      bRet = TRUE;
    }
    DeleteDC( hDC );
    return bRet;
  }
  return FALSE;
}