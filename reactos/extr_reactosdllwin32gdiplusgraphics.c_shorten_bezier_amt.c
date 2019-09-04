#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ X; scalar_t__ Y; } ;
typedef  scalar_t__ REAL ;
typedef  size_t INT ;
typedef  TYPE_1__ GpPointF ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 size_t MAX_ITERS ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  shorten_line_percent (scalar_t__,scalar_t__,scalar_t__*,scalar_t__*,scalar_t__) ; 
 scalar_t__ sqrt (scalar_t__) ; 

__attribute__((used)) static void shorten_bezier_amt(GpPointF * pt, REAL amt, BOOL rev)
{
    GpPointF origpt[4];
    REAL percent = 0.00, dx, dy, origx, origy, diff = -1.0;
    INT i, first = 0, second = 1, third = 2, fourth = 3;

    if(rev){
        first = 3;
        second = 2;
        third = 1;
        fourth = 0;
    }

    origx = pt[fourth].X;
    origy = pt[fourth].Y;
    memcpy(origpt, pt, sizeof(GpPointF) * 4);

    for(i = 0; (i < MAX_ITERS) && (diff < amt); i++){
        /* reset bezier points to original values */
        memcpy(pt, origpt, sizeof(GpPointF) * 4);
        /* Perform magic on bezier points. Order is important here.*/
        shorten_line_percent(pt[third].X, pt[third].Y, &pt[fourth].X, &pt[fourth].Y, percent);
        shorten_line_percent(pt[second].X, pt[second].Y, &pt[third].X, &pt[third].Y, percent);
        shorten_line_percent(pt[third].X, pt[third].Y, &pt[fourth].X, &pt[fourth].Y, percent);
        shorten_line_percent(pt[first].X, pt[first].Y, &pt[second].X, &pt[second].Y, percent);
        shorten_line_percent(pt[second].X, pt[second].Y, &pt[third].X, &pt[third].Y, percent);
        shorten_line_percent(pt[third].X, pt[third].Y, &pt[fourth].X, &pt[fourth].Y, percent);

        dx = pt[fourth].X - origx;
        dy = pt[fourth].Y - origy;

        diff = sqrt(dx * dx + dy * dy);
        percent += 0.0005 * amt;
    }
}