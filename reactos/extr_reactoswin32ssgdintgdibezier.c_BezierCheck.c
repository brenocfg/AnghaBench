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
struct TYPE_3__ {int x; int y; } ;
typedef  TYPE_1__ POINT ;
typedef  int INT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ BEZIERPIXEL ; 
 int BEZIERSHIFTDOWN (int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ abs (int) ; 

__attribute__((used)) static BOOL BezierCheck( int level, POINT *Points)
{
    INT dx, dy;
    dx=Points[3].x-Points[0].x;
    dy=Points[3].y-Points[0].y;
    if(abs(dy)<=abs(dx)){/* shallow line */
        /* check that control points are between begin and end */
        if(Points[1].x < Points[0].x){
            if(Points[1].x < Points[3].x)
                return FALSE;
        }else
            if(Points[1].x > Points[3].x)
                return FALSE;
        if(Points[2].x < Points[0].x){
            if(Points[2].x < Points[3].x)
                return FALSE;
        }else
            if(Points[2].x > Points[3].x)
                return FALSE;
        dx=BEZIERSHIFTDOWN(dx);
        if(!dx) return TRUE;
        if(abs(Points[1].y-Points[0].y-(dy/dx)*
                BEZIERSHIFTDOWN(Points[1].x-Points[0].x)) > BEZIERPIXEL ||
           abs(Points[2].y-Points[0].y-(dy/dx)*
                   BEZIERSHIFTDOWN(Points[2].x-Points[0].x)) > BEZIERPIXEL )
            return FALSE;
        else
            return TRUE;
    }else{ /* steep line */
        /* check that control points are between begin and end */
        if(Points[1].y < Points[0].y){
            if(Points[1].y < Points[3].y)
                return FALSE;
        }else
            if(Points[1].y > Points[3].y)
                return FALSE;
        if(Points[2].y < Points[0].y){
            if(Points[2].y < Points[3].y)
                return FALSE;
        }else
            if(Points[2].y > Points[3].y)
                return FALSE;
        dy=BEZIERSHIFTDOWN(dy);
        if(!dy) return TRUE;
        if(abs(Points[1].x-Points[0].x-(dx/dy)*
                BEZIERSHIFTDOWN(Points[1].y-Points[0].y)) > BEZIERPIXEL ||
           abs(Points[2].x-Points[0].x-(dx/dy)*
                   BEZIERSHIFTDOWN(Points[2].y-Points[0].y)) > BEZIERPIXEL )
            return FALSE;
        else
            return TRUE;
    }
}