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
struct TYPE_6__ {int /*<<< orphan*/  hDC; } ;
struct TYPE_5__ {scalar_t__ nWidth; int /*<<< orphan*/  style; } ;
typedef  TYPE_1__ ME_Run ;
typedef  TYPE_2__ ME_Context ;
typedef  scalar_t__ HPEN ;
typedef  int /*<<< orphan*/  COLORREF ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteObject (scalar_t__) ; 
 int /*<<< orphan*/  LineTo (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  MoveToEx (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ SelectObject (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ get_underline_pen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void draw_underline( ME_Context *c, ME_Run *run, int x, int y, COLORREF color )
{
    HPEN pen;

    pen = get_underline_pen( run->style, color );
    if (pen)
    {
        HPEN old_pen = SelectObject( c->hDC, pen );
        MoveToEx( c->hDC, x, y + 1, NULL );
        LineTo( c->hDC, x + run->nWidth, y + 1 );
        SelectObject( c->hDC, old_pen );
        DeleteObject( pen );
    }
    return;
}