#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int count; scalar_t__* message; int /*<<< orphan*/  print_user; int /*<<< orphan*/  (* print ) (int /*<<< orphan*/ ,char*) ;} ;
struct TYPE_5__ {TYPE_1__ warn; } ;
typedef  TYPE_2__ fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*) ; 

void fz_flush_warnings(fz_context *ctx)
{
	if (ctx->warn.count > 1)
	{
		char buf[50];
		fz_snprintf(buf, sizeof buf, "... repeated %d times...", ctx->warn.count);
		if (ctx->warn.print)
			ctx->warn.print(ctx->warn.print_user, buf);
	}
	ctx->warn.message[0] = 0;
	ctx->warn.count = 0;
}