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
struct TYPE_12__ {void* y; void* x; } ;
struct TYPE_14__ {TYPE_9__ emr; TYPE_2__ ptlOrigin; } ;
struct TYPE_13__ {TYPE_1__* funcs; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* pSetViewportOrgEx ) (TYPE_3__*,void*,void*,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  POINT ;
typedef  TYPE_3__* PHYSDEV ;
typedef  void* INT ;
typedef  TYPE_4__ EMRSETVIEWPORTORGEX ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EMFDRV_WriteRecord (TYPE_3__*,TYPE_9__*) ; 
 int /*<<< orphan*/  EMR_SETVIEWPORTORGEX ; 
 int /*<<< orphan*/  FALSE ; 
 TYPE_3__* GET_NEXT_PHYSDEV (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pSetViewportOrgEx ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,void*,void*,int /*<<< orphan*/ *) ; 

BOOL EMFDRV_SetViewportOrgEx( PHYSDEV dev, INT x, INT y, POINT *pt )
{
    PHYSDEV next = GET_NEXT_PHYSDEV( dev, pSetViewportOrgEx );
    EMRSETVIEWPORTORGEX emr;

    emr.emr.iType = EMR_SETVIEWPORTORGEX;
    emr.emr.nSize = sizeof(emr);
    emr.ptlOrigin.x = x;
    emr.ptlOrigin.y = y;

    if (!EMFDRV_WriteRecord( dev, &emr.emr )) return FALSE;
    return next->funcs->pSetViewportOrgEx( next, x, y, pt );
}