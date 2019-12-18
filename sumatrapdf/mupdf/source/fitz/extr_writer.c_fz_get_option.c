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

__attribute__((used)) static const char *
fz_get_option(fz_context *ctx, const char **key, const char **val, const char *opts)
{
	if (!opts || *opts == 0)
		return NULL;

	if (*opts == ',')
		++opts;

	*key = opts;
	while (*opts != 0 && *opts != ',' && *opts != '=')
		++opts;

	if (*opts == '=')
	{
		*val = ++opts;
		while (*opts != 0 && *opts != ',')
			++opts;
	}
	else
	{
		*val = "yes";
	}

	return opts;
}