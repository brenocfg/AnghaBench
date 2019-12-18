#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int member_0; int member_1; } ;
typedef  TYPE_1__ POINT ;
typedef  scalar_t__ HPEN ;
typedef  int /*<<< orphan*/  HDC ;
typedef  scalar_t__ HBRUSH ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ALTERNATE ; 
 int /*<<< orphan*/  ASSERT (scalar_t__) ; 
 scalar_t__ CreatePen (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ CreateSolidBrush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (scalar_t__) ; 
 int /*<<< orphan*/  GetPolyFillMode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PS_NULL ; 
 int /*<<< orphan*/  PS_SOLID ; 
 int /*<<< orphan*/  Polygon (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RGB (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Rectangle (int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  RoundRect (int /*<<< orphan*/ ,int,int,int,int,int,int) ; 
 scalar_t__ SelectObject (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  SetPolyFillMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WINDING ; 
 int /*<<< orphan*/  nelem (TYPE_1__*) ; 

void PolygonTest ( HDC hdc )
{
  HPEN Pen, OldPen;
  HBRUSH RedBrush, OldBrush;
  DWORD Mode;
  POINT PointsAlternate[] =
  {
    { 20, 80 },
    { 60, 20 },
    { 90, 80 },
    { 20, 40 },
    { 100, 40 }
  };
  POINT PointsWinding[] =
  {
    { 130, 80 },
    { 170, 20 },
    { 200, 80 },
    { 130, 40 },
    { 210, 40 }
  };
  POINT Tri1[] =
  {
    { 3, 3 },
    { 5, 3 },
    { 3, 5 }
  };
  POINT Tri2[] =
  {
    { 7, 3 },
    { 7, 7 },
    { 3, 7 },
  };
  POINT Square1[] =
  {
    { 1, 15 },
    { 3, 15 },
    { 3, 17 },
    { 1, 17 }
  };
  POINT Square2[] =
  {
    { 5, 15 },
    { 7, 15 },
    { 7, 17 },
    { 5, 17 }
  };
  POINT Square3[] =
  {
    { 1, 23 },
    { 3, 23 },
    { 3, 25 },
    { 1, 25 }
  };
  POINT Square4[] =
  {
    { 5, 23 },
    { 7, 23 },
    { 7, 25 },
    { 5, 25 }
  };
  POINT Square5[] =
  {
    { 1, 31 },
    { 3, 31 },
    { 3, 33 },
    { 1, 33 }
  };
  POINT Square6[] =
  {
    { 5, 31 },
    { 7, 31 },
    { 7, 33 },
    { 5, 33 }
  };

  //create a pen to draw the shape
  Pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0xff));
  ASSERT(Pen);
  RedBrush = CreateSolidBrush(RGB(0xff, 0, 0));
  ASSERT(RedBrush);

  OldPen = (HPEN)SelectObject(hdc, Pen);
  OldBrush = (HBRUSH)SelectObject(hdc, RedBrush);

  Mode = GetPolyFillMode(hdc);

  RoundRect ( hdc, 32, 8, 48, 24, 8, 8 );

  SetPolyFillMode(hdc, ALTERNATE);
  Polygon(hdc,PointsAlternate,nelem(PointsAlternate));

  SetPolyFillMode(hdc, WINDING);
  Polygon(hdc,PointsWinding,nelem(PointsWinding));

  Rectangle ( hdc, 1, 1, 10, 10 );
  Polygon(hdc,Tri1,nelem(Tri1));
  Polygon(hdc,Tri2,nelem(Tri2));

  Rectangle ( hdc,  1, 11,  4, 14 );
  Rectangle ( hdc,  5, 11,  8, 14 );
  Rectangle ( hdc,  9, 11, 12, 14 );
  Rectangle ( hdc, 13, 11, 16, 14 );
  Polygon(hdc,Square1,nelem(Square1));
  Polygon(hdc,Square2,nelem(Square2));
  Rectangle ( hdc,  1, 19,  4, 22 );
  Rectangle ( hdc,  5, 19,  8, 22 );
  Rectangle ( hdc,  9, 19, 12, 22 );
  Rectangle ( hdc, 13, 19, 16, 22 );
  Polygon(hdc,Square3,nelem(Square3));
  Polygon(hdc,Square4,nelem(Square4));
  Rectangle ( hdc,  1, 27,  4, 30 );
  Rectangle ( hdc,  5, 27,  8, 30 );
  Rectangle ( hdc,  9, 27, 12, 30 );
  Rectangle ( hdc, 13, 27, 16, 30 );

  // switch to null pen to make surey they display correctly
  DeleteObject ( SelectObject(hdc, OldPen) );
  Pen = CreatePen ( PS_NULL, 0, 0 );
  ASSERT(Pen);
  OldPen = (HPEN)SelectObject(hdc, Pen);

  Polygon(hdc,Square5,nelem(Square5));
  Polygon(hdc,Square6,nelem(Square6));
  Rectangle ( hdc,  1, 35,  4, 38 );
  Rectangle ( hdc,  5, 35,  8, 38 );
  Rectangle ( hdc,  9, 35, 12, 38 );
  Rectangle ( hdc, 13, 35, 16, 38 );

  //cleanup
  SetPolyFillMode(hdc, Mode);
  DeleteObject ( SelectObject(hdc, OldPen) );
  DeleteObject ( SelectObject(hdc, OldBrush) );
}