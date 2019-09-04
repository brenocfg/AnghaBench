#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  emr ;
struct TYPE_12__ {scalar_t__ bottom; scalar_t__ right; scalar_t__ top; scalar_t__ left; } ;
struct TYPE_11__ {int nSize; int /*<<< orphan*/  iType; } ;
struct TYPE_10__ {scalar_t__ GraphicsMode; } ;
struct TYPE_9__ {int /*<<< orphan*/  path; } ;
struct TYPE_8__ {TYPE_6__ emr; TYPE_7__ rclBox; } ;
typedef  int /*<<< orphan*/  PHYSDEV ;
typedef  scalar_t__ INT ;
typedef  TYPE_1__ EMRRECTANGLE ;
typedef  TYPE_2__ EMFDRV_PDEVICE ;
typedef  TYPE_3__ DC ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EMFDRV_UpdateBBox (int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  EMFDRV_WriteRecord (int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  EMR_RECTANGLE ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GM_COMPATIBLE ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 TYPE_2__* get_emf_physdev (int /*<<< orphan*/ ) ; 
 TYPE_3__* get_physdev_dc (int /*<<< orphan*/ ) ; 

BOOL EMFDRV_Rectangle(PHYSDEV dev, INT left, INT top, INT right, INT bottom)
{
    EMFDRV_PDEVICE *physDev = get_emf_physdev( dev );
#ifndef __REACTOS__
    DC *dc = get_physdev_dc( dev );
#endif
    EMRRECTANGLE emr;
    INT temp;

    TRACE("%d,%d - %d,%d\n", left, top, right, bottom);

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

    emr.emr.iType     = EMR_RECTANGLE;
    emr.emr.nSize     = sizeof(emr);
    emr.rclBox.left   = left;
    emr.rclBox.top    = top;
    emr.rclBox.right  = right;
    emr.rclBox.bottom = bottom;

    if(!physDev->path)
        EMFDRV_UpdateBBox( dev, &emr.rclBox );
    return EMFDRV_WriteRecord( dev, &emr.emr );
}