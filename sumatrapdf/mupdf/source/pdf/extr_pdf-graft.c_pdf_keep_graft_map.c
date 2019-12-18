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
typedef  TYPE_1__ pdf_graft_map ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 TYPE_1__* fz_keep_imp (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 

pdf_graft_map *
pdf_keep_graft_map(fz_context *ctx, pdf_graft_map *map)
{
	return fz_keep_imp(ctx, map, &map->refs);
}