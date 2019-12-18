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
struct TYPE_5__ {struct TYPE_5__* dst_from_src; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; int /*<<< orphan*/  refs; } ;
typedef  TYPE_1__ pdf_graft_map ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 scalar_t__ fz_drop_imp (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  pdf_drop_document (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
pdf_drop_graft_map(fz_context *ctx, pdf_graft_map *map)
{
	if (fz_drop_imp(ctx, map, &map->refs))
	{
		pdf_drop_document(ctx, map->src);
		pdf_drop_document(ctx, map->dst);
		fz_free(ctx, map->dst_from_src);
		fz_free(ctx, map);
	}
}