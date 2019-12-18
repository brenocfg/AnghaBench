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
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_4__ {int nSize; int /*<<< orphan*/  iType; } ;
struct TYPE_3__ {TYPE_2__ emr; int /*<<< orphan*/  iMode; } ;
typedef  int /*<<< orphan*/  PHYSDEV ;
typedef  TYPE_1__ EMRSETTEXTALIGN ;

/* Variables and functions */
 scalar_t__ EMFDRV_WriteRecord (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  EMR_SETTEXTALIGN ; 
 int /*<<< orphan*/  GDI_ERROR ; 

UINT EMFDRV_SetTextAlign( PHYSDEV dev, UINT align )
{
    EMRSETTEXTALIGN emr;
    emr.emr.iType = EMR_SETTEXTALIGN;
    emr.emr.nSize = sizeof(emr);
    emr.iMode = align;
    return EMFDRV_WriteRecord( dev, &emr.emr ) ? align : GDI_ERROR;
}