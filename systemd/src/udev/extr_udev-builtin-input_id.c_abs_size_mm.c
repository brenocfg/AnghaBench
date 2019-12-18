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
struct input_absinfo {int maximum; int minimum; int resolution; } ;

/* Variables and functions */

__attribute__((used)) static int abs_size_mm(const struct input_absinfo *absinfo) {
        /* Resolution is defined to be in units/mm for ABS_X/Y */
        return (absinfo->maximum - absinfo->minimum) / absinfo->resolution;
}