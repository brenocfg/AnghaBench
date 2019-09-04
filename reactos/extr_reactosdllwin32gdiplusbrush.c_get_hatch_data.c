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
typedef  int /*<<< orphan*/  GpStatus ;
typedef  size_t GpHatchStyle ;

/* Variables and functions */
 size_t ARRAY_SIZE (char**) ; 
 char** HatchBrushes ; 
 int /*<<< orphan*/  NotImplemented ; 
 int /*<<< orphan*/  Ok ; 

GpStatus get_hatch_data(GpHatchStyle hatchstyle, const char **result)
{
    if (hatchstyle < ARRAY_SIZE(HatchBrushes))
    {
        *result = HatchBrushes[hatchstyle];
        return Ok;
    }
    else
        return NotImplemented;
}