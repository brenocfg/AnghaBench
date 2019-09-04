#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int appends_ordered; } ;
typedef  TYPE_1__ TimescaleDBPrivate ;
struct TYPE_11__ {int /*<<< orphan*/  restrictions; int /*<<< orphan*/ * chunk_exclusion_func; } ;
struct TYPE_10__ {int /*<<< orphan*/ * fdw_private; } ;
typedef  TYPE_2__ RelOptInfo ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  HypertableRestrictInfo ;
typedef  int /*<<< orphan*/  Hypertable ;
typedef  TYPE_3__ CollectQualCtx ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/ * find_children_oids (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_explicit_chunk_oids (TYPE_3__*,int /*<<< orphan*/ *) ; 
 scalar_t__ should_order_append (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  ts_hypertable_restrict_info_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ts_hypertable_restrict_info_create (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ts_hypertable_restrict_info_get_chunk_oids_ordered (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static List *
get_chunk_oids(CollectQualCtx *ctx, PlannerInfo *root, RelOptInfo *rel, Hypertable *ht)
{
	bool reverse;

	if (ctx->chunk_exclusion_func == NULL)
	{
		HypertableRestrictInfo *hri = ts_hypertable_restrict_info_create(rel, ht);

		/*
		 * This is where the magic happens: use our HypertableRestrictInfo
		 * infrastructure to deduce the appropriate chunks using our range
		 * exclusion
		 */
		ts_hypertable_restrict_info_add(hri, root, ctx->restrictions);

		if (should_order_append(root, rel, ht, &reverse))
		{
			if (rel->fdw_private != NULL)
				((TimescaleDBPrivate *) rel->fdw_private)->appends_ordered = true;
			return ts_hypertable_restrict_info_get_chunk_oids_ordered(hri,
																	  ht,
																	  AccessShareLock,
																	  reverse);
		}
		else
			return find_children_oids(hri, ht, AccessShareLock);
	}
	else
		return get_explicit_chunk_oids(ctx, ht);
}