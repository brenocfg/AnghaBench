#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int compress; int strip_height; } ;
typedef  TYPE_1__ fz_pclm_options ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int fz_atoi (char const*) ; 
 scalar_t__ fz_has_option (int /*<<< orphan*/ *,char const*,char*,char const**) ; 
 scalar_t__ fz_option_eq (char const*,char*) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

fz_pclm_options *
fz_parse_pclm_options(fz_context *ctx, fz_pclm_options *opts, const char *args)
{
	const char *val;

	memset(opts, 0, sizeof *opts);

	if (fz_has_option(ctx, args, "compression", &val))
	{
		if (fz_option_eq(val, "none"))
			opts->compress = 0;
		else if (fz_option_eq(val, "flate"))
			opts->compress = 1;
		else
			fz_throw(ctx, FZ_ERROR_GENERIC, "Unsupported PCLm compression %s (none, or flate only)", val);
	}
	if (fz_has_option(ctx, args, "strip-height", &val))
	{
		int i = fz_atoi(val);
		if (i <= 0)
			fz_throw(ctx, FZ_ERROR_GENERIC, "Unsupported PCLm strip height %d (suggest 16)", i);
		opts->strip_height = i;
	}

	return opts;
}