#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct bitblt_coords {scalar_t__ log_height; scalar_t__ log_width; scalar_t__ log_y; scalar_t__ log_x; } ;
typedef  int /*<<< orphan*/  emr ;
struct TYPE_8__ {scalar_t__ bottom; scalar_t__ right; scalar_t__ top; scalar_t__ left; } ;
struct TYPE_7__ {int nSize; int /*<<< orphan*/  iType; } ;
struct TYPE_5__ {double eM11; double eM12; double eM21; double eM22; double eDx; double eDy; } ;
struct TYPE_6__ {TYPE_4__ rclBounds; TYPE_3__ emr; scalar_t__ cbBitsSrc; scalar_t__ offBitsSrc; scalar_t__ cbBmiSrc; scalar_t__ offBmiSrc; scalar_t__ iUsageSrc; scalar_t__ crBkColorSrc; TYPE_1__ xformSrc; scalar_t__ ySrc; scalar_t__ xSrc; int /*<<< orphan*/  dwRop; scalar_t__ cyDest; scalar_t__ cxDest; scalar_t__ yDest; scalar_t__ xDest; } ;
typedef  int /*<<< orphan*/  PHYSDEV ;
typedef  TYPE_2__ EMRBITBLT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EMFDRV_UpdateBBox (int /*<<< orphan*/ ,TYPE_4__*) ; 
 scalar_t__ EMFDRV_WriteRecord (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  EMR_BITBLT ; 

BOOL EMFDRV_PatBlt( PHYSDEV dev, struct bitblt_coords *dst, DWORD rop )
{
    EMRBITBLT emr;
    BOOL ret;

    emr.emr.iType = EMR_BITBLT;
    emr.emr.nSize = sizeof(emr);
    emr.rclBounds.left = dst->log_x;
    emr.rclBounds.top = dst->log_y;
    emr.rclBounds.right = dst->log_x + dst->log_width - 1;
    emr.rclBounds.bottom = dst->log_y + dst->log_height - 1;
    emr.xDest = dst->log_x;
    emr.yDest = dst->log_y;
    emr.cxDest = dst->log_width;
    emr.cyDest = dst->log_height;
    emr.dwRop = rop;
    emr.xSrc = 0;
    emr.ySrc = 0;
    emr.xformSrc.eM11 = 1.0;
    emr.xformSrc.eM12 = 0.0;
    emr.xformSrc.eM21 = 0.0;
    emr.xformSrc.eM22 = 1.0;
    emr.xformSrc.eDx = 0.0;
    emr.xformSrc.eDy = 0.0;
    emr.crBkColorSrc = 0;
    emr.iUsageSrc = 0;
    emr.offBmiSrc = 0;
    emr.cbBmiSrc = 0;
    emr.offBitsSrc = 0;
    emr.cbBitsSrc = 0;

    ret = EMFDRV_WriteRecord( dev, &emr.emr );
    if(ret)
        EMFDRV_UpdateBBox( dev, &emr.rclBounds );
    return ret;
}