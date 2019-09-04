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
typedef  int /*<<< orphan*/  SIZE ;
typedef  int /*<<< orphan*/  PHYSDEV ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  META_SCALEWINDOWEXT ; 
 int /*<<< orphan*/  MFDRV_MetaParam4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

BOOL MFDRV_ScaleWindowExtEx( PHYSDEV dev, INT xNum, INT xDenom, INT yNum, INT yDenom, SIZE *size )
{
    return MFDRV_MetaParam4( dev, META_SCALEWINDOWEXT, xNum, xDenom, yNum, yDenom );
}