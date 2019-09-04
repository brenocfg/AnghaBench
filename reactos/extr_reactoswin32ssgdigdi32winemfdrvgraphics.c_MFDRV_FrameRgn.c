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
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  HRGN ;
typedef  int /*<<< orphan*/  HBRUSH ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  META_FRAMEREGION ; 
 int MFDRV_CreateBrushIndirect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MFDRV_CreateRegion (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MFDRV_MetaParam4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

BOOL MFDRV_FrameRgn( PHYSDEV dev, HRGN hrgn, HBRUSH hbrush, INT x, INT y )
{
    INT16 iRgn, iBrush;
    iRgn = MFDRV_CreateRegion( dev, hrgn );
    if(iRgn == -1)
        return FALSE;
    iBrush = MFDRV_CreateBrushIndirect( dev, hbrush );
    if(!iBrush)
        return FALSE;
    return MFDRV_MetaParam4( dev, META_FRAMEREGION, iRgn, iBrush, x, y );
}