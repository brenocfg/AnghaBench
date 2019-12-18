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
struct TYPE_12__ {TYPE_8__ emr; int /*<<< orphan*/  iMode; } ;
struct TYPE_11__ {TYPE_1__* funcs; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* pSetMapMode ) (TYPE_2__*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__* PHYSDEV ;
typedef  int /*<<< orphan*/  INT ;
typedef  TYPE_3__ EMRSETMAPMODE ;

/* Variables and functions */
 int /*<<< orphan*/  EMFDRV_WriteRecord (TYPE_2__*,TYPE_8__*) ; 
 int /*<<< orphan*/  EMR_SETMAPMODE ; 
 TYPE_2__* GET_NEXT_PHYSDEV (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pSetMapMode ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 

INT EMFDRV_SetMapMode( PHYSDEV dev, INT mode )
{
    PHYSDEV next = GET_NEXT_PHYSDEV( dev, pSetMapMode );
    EMRSETMAPMODE emr;
    emr.emr.iType = EMR_SETMAPMODE;
    emr.emr.nSize = sizeof(emr);
    emr.iMode = mode;

    if (!EMFDRV_WriteRecord( dev, &emr.emr )) return 0;
    return next->funcs->pSetMapMode( next, mode );
}