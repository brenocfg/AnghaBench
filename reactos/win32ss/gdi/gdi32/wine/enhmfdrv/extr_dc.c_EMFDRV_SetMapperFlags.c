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
struct TYPE_3__ {TYPE_2__ emr; int /*<<< orphan*/  dwFlags; } ;
typedef  int /*<<< orphan*/  PHYSDEV ;
typedef  TYPE_1__ EMRSETMAPPERFLAGS ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 scalar_t__ EMFDRV_WriteRecord (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  EMR_SETMAPPERFLAGS ; 
 int /*<<< orphan*/  GDI_ERROR ; 

DWORD EMFDRV_SetMapperFlags( PHYSDEV dev, DWORD flags )
{
    EMRSETMAPPERFLAGS emr;

    emr.emr.iType = EMR_SETMAPPERFLAGS;
    emr.emr.nSize = sizeof(emr);
    emr.dwFlags   = flags;

    return EMFDRV_WriteRecord( dev, &emr.emr ) ? flags : GDI_ERROR;
}