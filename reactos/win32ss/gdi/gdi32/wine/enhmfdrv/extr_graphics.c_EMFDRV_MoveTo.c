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
struct TYPE_6__ {int nSize; int /*<<< orphan*/  iType; } ;
struct TYPE_4__ {void* y; void* x; } ;
struct TYPE_5__ {TYPE_3__ emr; TYPE_1__ ptl; } ;
typedef  int /*<<< orphan*/  PHYSDEV ;
typedef  void* INT ;
typedef  TYPE_2__ EMRMOVETOEX ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EMFDRV_WriteRecord (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  EMR_MOVETOEX ; 

BOOL EMFDRV_MoveTo(PHYSDEV dev, INT x, INT y)
{
    EMRMOVETOEX emr;

    emr.emr.iType = EMR_MOVETOEX;
    emr.emr.nSize = sizeof(emr);
    emr.ptl.x = x;
    emr.ptl.y = y;

    return EMFDRV_WriteRecord( dev, &emr.emr );
}