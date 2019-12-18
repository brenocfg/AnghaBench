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
typedef  int /*<<< orphan*/  INT ;

/* Variables and functions */
 int /*<<< orphan*/  META_INTERSECTCLIPRECT ; 
 int /*<<< orphan*/  MFDRV_MetaParam4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

INT MFDRV_IntersectClipRect( PHYSDEV dev, INT left, INT top, INT right, INT bottom )
{
    return MFDRV_MetaParam4( dev, META_INTERSECTCLIPRECT, left, top, right, bottom );
}