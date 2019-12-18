#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  emr ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_6__ {int nSize; int /*<<< orphan*/  iType; } ;
struct TYPE_4__ {void* y; void* x; } ;
struct TYPE_5__ {TYPE_3__ emr; int /*<<< orphan*/  iMode; int /*<<< orphan*/  crColor; TYPE_1__ ptlStart; } ;
typedef  int /*<<< orphan*/  PHYSDEV ;
typedef  void* INT ;
typedef  TYPE_2__ EMREXTFLOODFILL ;
typedef  int /*<<< orphan*/  COLORREF ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EMFDRV_WriteRecord (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  EMR_EXTFLOODFILL ; 

BOOL EMFDRV_ExtFloodFill( PHYSDEV dev, INT x, INT y, COLORREF color, UINT fillType )
{
    EMREXTFLOODFILL emr;

    emr.emr.iType = EMR_EXTFLOODFILL;
    emr.emr.nSize = sizeof(emr);
    emr.ptlStart.x = x;
    emr.ptlStart.y = y;
    emr.crColor = color;
    emr.iMode = fillType;

    return EMFDRV_WriteRecord( dev, &emr.emr );
}