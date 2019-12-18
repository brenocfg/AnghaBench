#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  refs; } ;
typedef  TYPE_1__ fz_link ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 TYPE_1__* fz_keep_imp (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 

fz_link *
fz_keep_link(fz_context *ctx, fz_link *link)
{
	return fz_keep_imp(ctx, link, &link->refs);
}