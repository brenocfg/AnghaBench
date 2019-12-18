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
struct TYPE_3__ {int temperature; } ;
typedef  TYPE_1__ color_setting_t ;

/* Variables and functions */
 float F (double,int) ; 
 int /*<<< orphan*/ * blackbody_color ; 
 int /*<<< orphan*/  interpolate_color (float,int /*<<< orphan*/ *,int /*<<< orphan*/ *,float*) ; 

void
colorramp_fill_float(float *gamma_r, float *gamma_g, float *gamma_b,
		     int size, const color_setting_t *setting)
{
	/* Approximate white point */
	float white_point[3];
	float alpha = (setting->temperature % 100) / 100.0;
	int temp_index = ((setting->temperature - 1000) / 100)*3;
	interpolate_color(alpha, &blackbody_color[temp_index],
			  &blackbody_color[temp_index+3], white_point);

	for (int i = 0; i < size; i++) {
		gamma_r[i] = F((double)gamma_r[i], 0);
		gamma_g[i] = F((double)gamma_g[i], 1);
		gamma_b[i] = F((double)gamma_b[i], 2);
	}
}