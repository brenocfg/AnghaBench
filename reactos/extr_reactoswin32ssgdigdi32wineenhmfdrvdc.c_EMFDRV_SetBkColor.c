#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  emr ;
struct TYPE_7__ {int nSize; int /*<<< orphan*/  iType; } ;
struct TYPE_6__ {scalar_t__ restoring; } ;
struct TYPE_5__ {TYPE_4__ emr; int /*<<< orphan*/  crColor; } ;
typedef  int /*<<< orphan*/  PHYSDEV ;
typedef  TYPE_1__ EMRSETBKCOLOR ;
typedef  TYPE_2__ EMFDRV_PDEVICE ;
typedef  int /*<<< orphan*/  COLORREF ;

/* Variables and functions */
 int /*<<< orphan*/  CLR_INVALID ; 
 scalar_t__ EMFDRV_WriteRecord (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  EMR_SETBKCOLOR ; 
 TYPE_2__* get_emf_physdev (int /*<<< orphan*/ ) ; 

COLORREF EMFDRV_SetBkColor( PHYSDEV dev, COLORREF color )
{
    EMRSETBKCOLOR emr;
    EMFDRV_PDEVICE *physDev = get_emf_physdev( dev );

    if (physDev->restoring) return color;  /* don't output records during RestoreDC */

    emr.emr.iType = EMR_SETBKCOLOR;
    emr.emr.nSize = sizeof(emr);
    emr.crColor = color;
    return EMFDRV_WriteRecord( dev, &emr.emr ) ? color : CLR_INVALID;
}