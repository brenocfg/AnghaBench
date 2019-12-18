#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  va_list ;
struct TYPE_5__ {int count; int /*<<< orphan*/  message; int /*<<< orphan*/  print_user; int /*<<< orphan*/  (* print ) (int /*<<< orphan*/ ,char*) ;} ;
struct TYPE_6__ {TYPE_1__ warn; } ;
typedef  TYPE_2__ fz_context ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  fz_flush_warnings (TYPE_2__*) ; 
 int /*<<< orphan*/  fz_strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  fz_vsnprintf (char*,int,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*) ; 

void fz_vwarn(fz_context *ctx, const char *fmt, va_list ap)
{
	char buf[sizeof ctx->warn.message];

	fz_vsnprintf(buf, sizeof buf, fmt, ap);
	buf[sizeof(buf) - 1] = 0;

	if (!strcmp(buf, ctx->warn.message))
	{
		ctx->warn.count++;
	}
	else
	{
		fz_flush_warnings(ctx);
		if (ctx->warn.print)
			ctx->warn.print(ctx->warn.print_user, buf);
		fz_strlcpy(ctx->warn.message, buf, sizeof ctx->warn.message);
		ctx->warn.count = 1;
	}
}