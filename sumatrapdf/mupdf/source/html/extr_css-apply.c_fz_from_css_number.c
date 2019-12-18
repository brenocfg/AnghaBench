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
struct TYPE_3__ {int unit; float value; } ;
typedef  TYPE_1__ fz_css_number ;

/* Variables and functions */
#define  N_AUTO 132 
#define  N_LENGTH 131 
#define  N_NUMBER 130 
#define  N_PERCENT 129 
#define  N_SCALE 128 

float
fz_from_css_number(fz_css_number number, float em, float percent_value, float auto_value)
{
	switch (number.unit) {
	default:
	case N_NUMBER: return number.value;
	case N_LENGTH: return number.value;
	case N_SCALE: return number.value * em;
	case N_PERCENT: return number.value * 0.01f * percent_value;
	case N_AUTO: return auto_value;
	}
}