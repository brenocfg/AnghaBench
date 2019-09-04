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
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EMR_STROKEANDFILLPATH ; 
 int /*<<< orphan*/  emfdrv_stroke_and_fill_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

BOOL EMFDRV_StrokeAndFillPath( PHYSDEV dev )
{
    return emfdrv_stroke_and_fill_path( dev, EMR_STROKEANDFILLPATH );
}