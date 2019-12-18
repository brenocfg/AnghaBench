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
struct TYPE_3__ {int bidx; struct TYPE_3__* dst; struct TYPE_3__* ref; int /*<<< orphan*/  chain; } ;
typedef  TYPE_1__ fz_faxd ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_drop_stream (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  fz_unread_byte (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
close_faxd(fz_context *ctx, void *state_)
{
	fz_faxd *fax = (fz_faxd *)state_;
	int i;

	/* if we read any extra bytes, try to put them back */
	i = (32 - fax->bidx) / 8;
	while (i--)
		fz_unread_byte(ctx, fax->chain);

	fz_drop_stream(ctx, fax->chain);
	fz_free(ctx, fax->ref);
	fz_free(ctx, fax->dst);
	fz_free(ctx, fax);
}