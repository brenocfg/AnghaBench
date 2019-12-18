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

/* Variables and functions */

__attribute__((used)) static float calc_percent(unsigned long current, unsigned long total) {
	float percent = 0.0;
	if (total <= 0)
		return percent;
	if (current >= total) {
		percent = 100.0f;
	} else {
		percent=(100.0f*(float)current/(float)total);
	}
	return percent;
}