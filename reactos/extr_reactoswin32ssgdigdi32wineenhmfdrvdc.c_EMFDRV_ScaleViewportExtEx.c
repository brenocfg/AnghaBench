#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  emr ;
struct TYPE_13__ {int nSize; int /*<<< orphan*/  iType; } ;
struct TYPE_12__ {TYPE_8__ emr; void* yDenom; void* yNum; void* xDenom; void* xNum; } ;
struct TYPE_11__ {TYPE_1__* funcs; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* pScaleViewportExtEx ) (TYPE_2__*,void*,void*,void*,void*,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  SIZE ;
typedef  TYPE_2__* PHYSDEV ;
typedef  void* INT ;
typedef  TYPE_3__ EMRSCALEVIEWPORTEXTEX ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EMFDRV_WriteRecord (TYPE_2__*,TYPE_8__*) ; 
 int /*<<< orphan*/  EMR_SCALEVIEWPORTEXTEX ; 
 int /*<<< orphan*/  FALSE ; 
 TYPE_2__* GET_NEXT_PHYSDEV (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pScaleViewportExtEx ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,void*,void*,void*,void*,int /*<<< orphan*/ *) ; 

BOOL EMFDRV_ScaleViewportExtEx( PHYSDEV dev, INT xNum, INT xDenom, INT yNum, INT yDenom, SIZE *size )
{
    PHYSDEV next = GET_NEXT_PHYSDEV( dev, pScaleViewportExtEx );
    EMRSCALEVIEWPORTEXTEX emr;

    emr.emr.iType = EMR_SCALEVIEWPORTEXTEX;
    emr.emr.nSize = sizeof(emr);
    emr.xNum      = xNum;
    emr.xDenom    = xDenom;
    emr.yNum      = yNum;
    emr.yDenom    = yDenom;

    if (!EMFDRV_WriteRecord( dev, &emr.emr )) return FALSE;
    return next->funcs->pScaleViewportExtEx( next, xNum, xDenom, yNum, yDenom, size );
}