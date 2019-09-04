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
typedef  int /*<<< orphan*/  REAL ;
typedef  int /*<<< orphan*/  GpUnit ;

/* Variables and functions */
 int /*<<< orphan*/  pixels_to_units (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  units_to_pixels (double,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static REAL units_scale(GpUnit from, GpUnit to, REAL dpi)
{
    REAL pixels = units_to_pixels(1.0, from, dpi);
    return pixels_to_units(pixels, to, dpi);
}