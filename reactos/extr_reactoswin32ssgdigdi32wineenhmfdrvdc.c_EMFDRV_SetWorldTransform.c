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
typedef  int /*<<< orphan*/  XFORM ;
struct TYPE_13__ {int nSize; int /*<<< orphan*/  iType; } ;
struct TYPE_12__ {TYPE_8__ emr; int /*<<< orphan*/  xform; } ;
struct TYPE_11__ {TYPE_1__* funcs; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* pSetWorldTransform ) (TYPE_2__*,int /*<<< orphan*/  const*) ;} ;
typedef  TYPE_2__* PHYSDEV ;
typedef  TYPE_3__ EMRSETWORLDTRANSFORM ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EMFDRV_WriteRecord (TYPE_2__*,TYPE_8__*) ; 
 int /*<<< orphan*/  EMR_SETWORLDTRANSFORM ; 
 int /*<<< orphan*/  FALSE ; 
 TYPE_2__* GET_NEXT_PHYSDEV (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pSetWorldTransform ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/  const*) ; 

BOOL EMFDRV_SetWorldTransform( PHYSDEV dev, const XFORM *xform)
{
    PHYSDEV next = GET_NEXT_PHYSDEV( dev, pSetWorldTransform );
    EMRSETWORLDTRANSFORM emr;

    emr.emr.iType = EMR_SETWORLDTRANSFORM;
    emr.emr.nSize = sizeof(emr);
    emr.xform = *xform;

    if (!EMFDRV_WriteRecord( dev, &emr.emr )) return FALSE;
    return next->funcs->pSetWorldTransform( next, xform );
}