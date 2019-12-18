#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  emr ;
struct TYPE_17__ {scalar_t__ hBrush; } ;
struct TYPE_16__ {scalar_t__ dc_brush; } ;
struct TYPE_13__ {int nSize; int /*<<< orphan*/  iType; } ;
struct TYPE_15__ {TYPE_10__ emr; int /*<<< orphan*/  ihObject; } ;
struct TYPE_14__ {int /*<<< orphan*/  hdc; } ;
typedef  TYPE_1__* PHYSDEV ;
typedef  TYPE_2__ EMRSELECTOBJECT ;
typedef  TYPE_3__ EMFDRV_PDEVICE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  TYPE_4__ DC ;
typedef  int /*<<< orphan*/  COLORREF ;

/* Variables and functions */
 int /*<<< orphan*/  CLR_INVALID ; 
 scalar_t__ CreateSolidBrush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC_BRUSH ; 
 int /*<<< orphan*/  DeleteObject (scalar_t__) ; 
 int /*<<< orphan*/  EMFDRV_CreateBrushIndirect (TYPE_1__*,scalar_t__) ; 
 scalar_t__ EMFDRV_WriteRecord (TYPE_1__*,TYPE_10__*) ; 
 int /*<<< orphan*/  EMR_SELECTOBJECT ; 
 int /*<<< orphan*/  GDI_hdc_using_object (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ GetCurrentObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ GetStockObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OBJ_BRUSH ; 
 TYPE_3__* get_emf_physdev (TYPE_1__*) ; 
 TYPE_4__* get_physdev_dc (TYPE_1__*) ; 

COLORREF EMFDRV_SetDCBrushColor( PHYSDEV dev, COLORREF color )
{
    EMFDRV_PDEVICE *physDev = get_emf_physdev( dev );
#ifndef __REACTOS__
    DC *dc = get_physdev_dc( dev );
#endif
    EMRSELECTOBJECT emr;
    DWORD index;
#ifdef __REACTOS__
    if (GetCurrentObject( dev->hdc, OBJ_BRUSH ) != GetStockObject( DC_BRUSH )) return color;
#else
    if (dc->hBrush != GetStockObject( DC_BRUSH )) return color;
#endif
    if (physDev->dc_brush) DeleteObject( physDev->dc_brush );
    if (!(physDev->dc_brush = CreateSolidBrush( color ))) return CLR_INVALID;
    if (!(index = EMFDRV_CreateBrushIndirect(dev, physDev->dc_brush ))) return CLR_INVALID;
    GDI_hdc_using_object( physDev->dc_brush, dev->hdc );
    emr.emr.iType = EMR_SELECTOBJECT;
    emr.emr.nSize = sizeof(emr);
    emr.ihObject = index;
    return EMFDRV_WriteRecord( dev, &emr.emr ) ? color : CLR_INVALID;
}