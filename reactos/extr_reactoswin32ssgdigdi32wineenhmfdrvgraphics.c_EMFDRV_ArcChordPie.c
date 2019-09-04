#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  emr ;
struct TYPE_18__ {double x; double y; } ;
struct TYPE_21__ {scalar_t__ GraphicsMode; TYPE_5__ cur_pos; } ;
struct TYPE_20__ {int /*<<< orphan*/  path; } ;
struct TYPE_13__ {int nSize; scalar_t__ iType; } ;
struct TYPE_16__ {int x; int y; } ;
struct TYPE_15__ {int x; int y; } ;
struct TYPE_14__ {int left; int top; int right; int bottom; } ;
struct TYPE_19__ {TYPE_11__ emr; TYPE_3__ ptlEnd; TYPE_2__ ptlStart; TYPE_1__ rclBox; } ;
struct TYPE_17__ {int left; int top; int right; int bottom; } ;
typedef  TYPE_4__ RECTL ;
typedef  TYPE_5__ POINT ;
typedef  int /*<<< orphan*/  PHYSDEV ;
typedef  int INT ;
typedef  TYPE_6__ EMRARC ;
typedef  TYPE_7__ EMFDRV_PDEVICE ;
typedef  scalar_t__ DWORD ;
typedef  TYPE_8__ DC ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EMFDRV_UpdateBBox (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  EMFDRV_WriteRecord (int /*<<< orphan*/ ,TYPE_11__*) ; 
 scalar_t__ EMR_ARCTO ; 
 scalar_t__ EMR_PIE ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GM_COMPATIBLE ; 
 int M_PI ; 
 int /*<<< orphan*/  TRUE ; 
 double atan2 (double,double) ; 
 int cos (double) ; 
 TYPE_7__* get_emf_physdev (int /*<<< orphan*/ ) ; 
 TYPE_8__* get_physdev_dc (int /*<<< orphan*/ ) ; 
 void* max (double,double) ; 
 void* min (double,double) ; 
 int sin (double) ; 

__attribute__((used)) static BOOL
EMFDRV_ArcChordPie( PHYSDEV dev, INT left, INT top, INT right, INT bottom,
		    INT xstart, INT ystart, INT xend, INT yend, DWORD iType )
{
    EMFDRV_PDEVICE *physDev = get_emf_physdev( dev );
#ifndef __REACTOS__
    DC *dc = get_physdev_dc( dev );
#endif
    INT temp, xCentre, yCentre, i;
    double angleStart, angleEnd;
    double xinterStart, yinterStart, xinterEnd, yinterEnd;
    EMRARC emr;
    RECTL bounds;

    if(left == right || top == bottom) return FALSE;

    if(left > right) {temp = left; left = right; right = temp;}
    if(top > bottom) {temp = top; top = bottom; bottom = temp;}
#ifdef __REACTOS__
    if(GetGraphicsMode(dev->hdc) == GM_COMPATIBLE) {
#else
    if(dc->GraphicsMode == GM_COMPATIBLE) {
#endif
        right--;
	bottom--;
    }

    emr.emr.iType     = iType;
    emr.emr.nSize     = sizeof(emr);
    emr.rclBox.left   = left;
    emr.rclBox.top    = top;
    emr.rclBox.right  = right;
    emr.rclBox.bottom = bottom;
    emr.ptlStart.x    = xstart;
    emr.ptlStart.y    = ystart;
    emr.ptlEnd.x      = xend;
    emr.ptlEnd.y      = yend;


    /* Now calculate the BBox */
    xCentre = (left + right + 1) / 2;
    yCentre = (top + bottom + 1) / 2;

    xstart -= xCentre;
    ystart -= yCentre;
    xend   -= xCentre;
    yend   -= yCentre;

    /* invert y co-ords to get angle anti-clockwise from x-axis */
    angleStart = atan2( -(double)ystart, (double)xstart);
    angleEnd   = atan2( -(double)yend, (double)xend);

    /* These are the intercepts of the start/end lines with the arc */

    xinterStart = (right - left + 1)/2 * cos(angleStart) + xCentre;
    yinterStart = -(bottom - top + 1)/2 * sin(angleStart) + yCentre;
    xinterEnd   = (right - left + 1)/2 * cos(angleEnd) + xCentre;
    yinterEnd   = -(bottom - top + 1)/2 * sin(angleEnd) + yCentre;

    if(angleStart < 0) angleStart += 2 * M_PI;
    if(angleEnd < 0) angleEnd += 2 * M_PI;
    if(angleEnd < angleStart) angleEnd += 2 * M_PI;

    bounds.left   = min(xinterStart, xinterEnd);
    bounds.top    = min(yinterStart, yinterEnd);
    bounds.right  = max(xinterStart, xinterEnd);
    bounds.bottom = max(yinterStart, yinterEnd);

    for(i = 0; i <= 8; i++) {
        if(i * M_PI / 2 < angleStart) /* loop until we're past start */
	    continue;
	if(i * M_PI / 2 > angleEnd)   /* if we're past end we're finished */
	    break;

	/* the arc touches the rectangle at the start of quadrant i, so adjust
	   BBox to reflect this. */

	switch(i % 4) {
	case 0:
	    bounds.right = right;
	    break;
	case 1:
	    bounds.top = top;
	    break;
	case 2:
	    bounds.left = left;
	    break;
	case 3:
	    bounds.bottom = bottom;
	    break;
	}
    }

    /* If we're drawing a pie then make sure we include the centre */
    if(iType == EMR_PIE) {
        if(bounds.left > xCentre) bounds.left = xCentre;
	else if(bounds.right < xCentre) bounds.right = xCentre;
	if(bounds.top > yCentre) bounds.top = yCentre;
	else if(bounds.bottom < yCentre) bounds.bottom = yCentre;
    }
    if (iType == EMR_ARCTO)
    {
        POINT pt;
#ifdef __REACTOS__
        GetCurrentPositionEx( dev->hdc, &pt );
#else
        pt = dc->cur_pos;
#endif
        bounds.left   = min( bounds.left, pt.x );
        bounds.top    = min( bounds.top, pt.y );
        bounds.right  = max( bounds.right, pt.x );
        bounds.bottom = max( bounds.bottom, pt.y );
    }
    if(!EMFDRV_WriteRecord( dev, &emr.emr ))
        return FALSE;
    if(!physDev->path)
        EMFDRV_UpdateBBox( dev, &bounds );
    return TRUE;
}