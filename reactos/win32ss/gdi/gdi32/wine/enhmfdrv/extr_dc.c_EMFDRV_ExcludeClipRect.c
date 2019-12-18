#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  emr ;
struct TYPE_15__ {int nSize; int /*<<< orphan*/  iType; } ;
struct TYPE_11__ {void* bottom; void* right; void* top; void* left; } ;
struct TYPE_14__ {TYPE_9__ emr; TYPE_1__ rclClip; } ;
struct TYPE_13__ {TYPE_2__* funcs; } ;
struct TYPE_12__ {void* (* pExcludeClipRect ) (TYPE_3__*,void*,void*,void*,void*) ;} ;
typedef  TYPE_3__* PHYSDEV ;
typedef  void* INT ;
typedef  TYPE_4__ EMREXCLUDECLIPRECT ;

/* Variables and functions */
 int /*<<< orphan*/  EMFDRV_WriteRecord (TYPE_3__*,TYPE_9__*) ; 
 int /*<<< orphan*/  EMR_EXCLUDECLIPRECT ; 
 void* ERROR ; 
 TYPE_3__* GET_NEXT_PHYSDEV (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pExcludeClipRect ; 
 void* stub1 (TYPE_3__*,void*,void*,void*,void*) ; 

INT EMFDRV_ExcludeClipRect( PHYSDEV dev, INT left, INT top, INT right, INT bottom )
{
    PHYSDEV next = GET_NEXT_PHYSDEV( dev, pExcludeClipRect );
    EMREXCLUDECLIPRECT emr;

    emr.emr.iType      = EMR_EXCLUDECLIPRECT;
    emr.emr.nSize      = sizeof(emr);
    emr.rclClip.left   = left;
    emr.rclClip.top    = top;
    emr.rclClip.right  = right;
    emr.rclClip.bottom = bottom;
    if (!EMFDRV_WriteRecord( dev, &emr.emr )) return ERROR;
    return next->funcs->pExcludeClipRect( next, left, top, right, bottom );
}