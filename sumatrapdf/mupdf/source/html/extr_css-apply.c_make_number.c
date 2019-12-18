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
struct TYPE_3__ {float value; int unit; } ;
typedef  TYPE_1__ fz_css_number ;

/* Variables and functions */

__attribute__((used)) static fz_css_number
make_number(float v, int u)
{
	fz_css_number n;
	n.value = v;
	n.unit = u;
	return n;
}