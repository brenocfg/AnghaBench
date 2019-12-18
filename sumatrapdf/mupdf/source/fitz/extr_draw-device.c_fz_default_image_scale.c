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

int
fz_default_image_scale(void *arg, int dst_w, int dst_h, int src_w, int src_h)
{
	(void)arg;
	return dst_w < src_w && dst_h < src_h;
}