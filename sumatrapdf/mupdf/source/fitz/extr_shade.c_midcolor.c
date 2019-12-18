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

__attribute__((used)) static inline void midcolor(float *c, float *c1, float *c2, int n)
{
	int i;
	for (i = 0; i < n; i++)
		c[i] = (c1[i] + c2[i]) * 0.5f;
}