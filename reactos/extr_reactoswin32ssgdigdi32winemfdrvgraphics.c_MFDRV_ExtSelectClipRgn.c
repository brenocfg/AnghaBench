#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  PHYSDEV ;
typedef  int INT16 ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  HRGN ;

/* Variables and functions */
 scalar_t__ ERROR ; 
 int /*<<< orphan*/  META_DELETEOBJECT ; 
 int /*<<< orphan*/  META_SELECTOBJECT ; 
 int MFDRV_CreateRegion (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MFDRV_MetaParam1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MFDRV_RemoveHandle (int /*<<< orphan*/ ,int) ; 
 scalar_t__ NULLREGION ; 
 scalar_t__ RGN_COPY ; 

INT MFDRV_ExtSelectClipRgn( PHYSDEV dev, HRGN hrgn, INT mode )
{
    INT16 iRgn;
    INT ret;

    if (mode != RGN_COPY) return ERROR;
    if (!hrgn) return NULLREGION;
    iRgn = MFDRV_CreateRegion( dev, hrgn );
    if(iRgn == -1) return ERROR;
    ret = MFDRV_MetaParam1( dev, META_SELECTOBJECT, iRgn ) ? NULLREGION : ERROR;
    MFDRV_MetaParam1( dev, META_DELETEOBJECT, iRgn );
    MFDRV_RemoveHandle( dev, iRgn );
    return ret;
}