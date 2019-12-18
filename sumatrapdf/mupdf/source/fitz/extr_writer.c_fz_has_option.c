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
 char* fz_get_option (int /*<<< orphan*/ *,char const**,char const**,char const*) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char const*,size_t) ; 

int
fz_has_option(fz_context *ctx, const char *opts, const char *key, const char **val)
{
	const char *straw;
	size_t n = strlen(key);
	while ((opts = fz_get_option(ctx, &straw, val, opts)))
		if (!strncmp(straw, key, n) && (straw[n] == '=' || straw[n] == ',' || straw[n] == 0))
			return 1;
	return 0;
}