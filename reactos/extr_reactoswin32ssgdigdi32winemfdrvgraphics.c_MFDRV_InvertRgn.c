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
typedef  int /*<<< orphan*/  HRGN ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  META_INVERTREGION ; 
 int MFDRV_CreateRegion (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MFDRV_MetaParam1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

BOOL MFDRV_InvertRgn( PHYSDEV dev, HRGN hrgn )
{
    INT16 index;
    index = MFDRV_CreateRegion( dev, hrgn );
    if(index == -1)
        return FALSE;
    return MFDRV_MetaParam1( dev, META_INVERTREGION, index );
}