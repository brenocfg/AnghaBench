#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_14__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  emr ;
struct TYPE_21__ {int /*<<< orphan*/  physDev; } ;
struct TYPE_20__ {scalar_t__ path; int /*<<< orphan*/  pathdev; } ;
struct TYPE_16__ {int nSize; int /*<<< orphan*/  iType; } ;
struct TYPE_19__ {TYPE_14__ emr; } ;
struct TYPE_18__ {TYPE_1__* funcs; } ;
struct TYPE_17__ {int /*<<< orphan*/  (* pBeginPath ) (TYPE_2__*) ;} ;
typedef  TYPE_2__* PHYSDEV ;
typedef  TYPE_3__ EMRBEGINPATH ;
typedef  TYPE_4__ EMFDRV_PDEVICE ;
typedef  TYPE_5__ DC ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EMFDRV_WriteRecord (TYPE_2__*,TYPE_14__*) ; 
 int /*<<< orphan*/  EMR_BEGINPATH ; 
 scalar_t__ FALSE ; 
 TYPE_2__* GET_NEXT_PHYSDEV (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  emfpath_driver ; 
 TYPE_4__* get_emf_physdev (TYPE_2__*) ; 
 TYPE_5__* get_physdev_dc (TYPE_2__*) ; 
 int /*<<< orphan*/  pBeginPath ; 
 int /*<<< orphan*/  push_dc_driver (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

BOOL EMFDRV_BeginPath( PHYSDEV dev )
{
    EMFDRV_PDEVICE *physDev = get_emf_physdev( dev );
    PHYSDEV next = GET_NEXT_PHYSDEV( dev, pBeginPath );
    EMRBEGINPATH emr;
    DC *dc = get_physdev_dc( dev );

    emr.emr.iType = EMR_BEGINPATH;
    emr.emr.nSize = sizeof(emr);

    if (!EMFDRV_WriteRecord( dev, &emr.emr )) return FALSE;
    if (physDev->path) return TRUE;  /* already open */

    if (!next->funcs->pBeginPath( next )) return FALSE;
    push_dc_driver( &dc->physDev, &physDev->pathdev, &emfpath_driver );
    physDev->path = TRUE;
    return TRUE;
}