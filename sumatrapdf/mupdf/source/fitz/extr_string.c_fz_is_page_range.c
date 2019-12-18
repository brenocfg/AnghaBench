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
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */

int fz_is_page_range(fz_context *ctx, const char *s)
{
	/* TODO: check the actual syntax... */
	while (*s)
	{
		if ((*s < '0' || *s > '9') && *s != 'N' && *s != '-' && *s != ',')
			return 0;
		s++;
	}
	return 1;
}