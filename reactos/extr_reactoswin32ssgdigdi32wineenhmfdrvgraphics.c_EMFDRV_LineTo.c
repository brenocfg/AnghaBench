#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_9__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  emr ;
struct TYPE_17__ {int nSize; int /*<<< orphan*/  iType; } ;
struct TYPE_13__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_16__ {TYPE_3__ cur_pos; } ;
struct TYPE_15__ {int /*<<< orphan*/  path; } ;
struct TYPE_11__ {void* y; void* x; } ;
struct TYPE_14__ {TYPE_9__ emr; TYPE_1__ ptl; } ;
struct TYPE_12__ {void* bottom; void* right; void* top; void* left; } ;
typedef  TYPE_2__ RECTL ;
typedef  TYPE_3__ POINT ;
typedef  int /*<<< orphan*/  PHYSDEV ;
typedef  void* INT ;
typedef  TYPE_4__ EMRLINETO ;
typedef  TYPE_5__ EMFDRV_PDEVICE ;
typedef  TYPE_6__ DC ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EMFDRV_UpdateBBox (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  EMFDRV_WriteRecord (int /*<<< orphan*/ ,TYPE_9__*) ; 
 int /*<<< orphan*/  EMR_LINETO ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_5__* get_emf_physdev (int /*<<< orphan*/ ) ; 
 TYPE_6__* get_physdev_dc (int /*<<< orphan*/ ) ; 
 void* max (void*,int /*<<< orphan*/ ) ; 
 void* min (void*,int /*<<< orphan*/ ) ; 

BOOL EMFDRV_LineTo( PHYSDEV dev, INT x, INT y )
{
    EMFDRV_PDEVICE *physDev = get_emf_physdev( dev );
#ifndef __REACTOS__
    DC *dc = get_physdev_dc( dev );
#endif
    POINT pt;
    EMRLINETO emr;
    RECTL bounds;

    emr.emr.iType = EMR_LINETO;
    emr.emr.nSize = sizeof(emr);
    emr.ptl.x = x;
    emr.ptl.y = y;

    if(!EMFDRV_WriteRecord( dev, &emr.emr ))
    	return FALSE;
#ifdef __REACTOS__
    GetCurrentPositionEx( dev->hdc, &pt );
#else
    pt = dc->cur_pos;
#endif
    bounds.left   = min(x, pt.x);
    bounds.top    = min(y, pt.y);
    bounds.right  = max(x, pt.x);
    bounds.bottom = max(y, pt.y);

    if(!physDev->path)
        EMFDRV_UpdateBBox( dev, &bounds );

    return TRUE;
}