#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {double* gamma; double brightness; int /*<<< orphan*/  temperature; } ;
typedef  TYPE_1__ color_setting_t ;

/* Variables and functions */
 int /*<<< orphan*/  NEUTRAL_TEMP ; 

__attribute__((used)) static void
color_setting_reset(color_setting_t *color)
{
	color->temperature = NEUTRAL_TEMP;
	color->gamma[0] = 1.0;
	color->gamma[1] = 1.0;
	color->gamma[2] = 1.0;
	color->brightness = 1.0;
}