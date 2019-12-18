#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  emr ;
struct TYPE_4__ {int nSize; int /*<<< orphan*/  iType; } ;
struct TYPE_3__ {TYPE_2__ emr; int /*<<< orphan*/  iMode; } ;
typedef  int /*<<< orphan*/  PHYSDEV ;
typedef  int /*<<< orphan*/  INT ;
typedef  TYPE_1__ EMRSELECTCLIPPATH ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EMFDRV_WriteRecord (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  EMR_SELECTCLIPPATH ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

BOOL EMFDRV_SelectClipPath( PHYSDEV dev, INT iMode )
{
 //   PHYSDEV next = GET_NEXT_PHYSDEV( dev, pSelectClipPath ); This HACK breaks test_emf_clipping
    EMRSELECTCLIPPATH emr;
 //   BOOL ret = FALSE;
 //   HRGN hrgn;

    emr.emr.iType = EMR_SELECTCLIPPATH;
    emr.emr.nSize = sizeof(emr);
    emr.iMode = iMode;

    if (!EMFDRV_WriteRecord( dev, &emr.emr )) return FALSE;
/*    hrgn = PathToRegion( dev->hdc );
    if (hrgn)
    {
        ret = next->funcs->pExtSelectClipRgn( next, hrgn, iMode );
        DeleteObject( hrgn );
    } ERR("EMFDRV_SelectClipPath ret %d\n",ret);
    return ret;*/
    return TRUE;
}