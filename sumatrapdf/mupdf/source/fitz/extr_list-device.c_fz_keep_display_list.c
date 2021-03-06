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
struct TYPE_5__ {int /*<<< orphan*/  storable; } ;
typedef  TYPE_1__ fz_display_list ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 TYPE_1__* fz_keep_storable (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

fz_display_list *
fz_keep_display_list(fz_context *ctx, fz_display_list *list)
{
	return fz_keep_storable(ctx, &list->storable);
}