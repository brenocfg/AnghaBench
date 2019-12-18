#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_9__ {int /*<<< orphan*/  os_raw_receive; } ;
typedef  TYPE_1__ objset_t ;
struct TYPE_10__ {int /*<<< orphan*/ * gme_ds; int /*<<< orphan*/  guid; scalar_t__ raw; } ;
typedef  TYPE_2__ guid_map_entry_t ;
typedef  int /*<<< orphan*/  dsl_pool_t ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;
typedef  int /*<<< orphan*/  ds_hold_flags_t ;
typedef  scalar_t__ boolean_t ;
typedef  int /*<<< orphan*/  avl_tree_t ;
struct TYPE_11__ {int /*<<< orphan*/  ds_guid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  DS_HOLD_FLAG_DECRYPT ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  avl_add (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int dmu_objset_from_ds (int /*<<< orphan*/ *,TYPE_1__**) ; 
 int /*<<< orphan*/  dsl_dataset_disown (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dsl_dataset_own_obj (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ **) ; 
 TYPE_5__* dsl_dataset_phys (int /*<<< orphan*/ *) ; 
 int dsl_pool_hold (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dsl_pool_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* kmem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (TYPE_2__*,int) ; 

__attribute__((used)) static int
add_ds_to_guidmap(const char *name, avl_tree_t *guid_map, uint64_t snapobj,
    boolean_t raw)
{
	dsl_pool_t *dp;
	dsl_dataset_t *snapds;
	guid_map_entry_t *gmep;
	objset_t *os;
	ds_hold_flags_t dsflags = (raw) ? 0 : DS_HOLD_FLAG_DECRYPT;
	int err;

	ASSERT(guid_map != NULL);

	err = dsl_pool_hold(name, FTAG, &dp);
	if (err != 0)
		return (err);
	gmep = kmem_alloc(sizeof (*gmep), KM_SLEEP);
	err = dsl_dataset_own_obj(dp, snapobj, dsflags, gmep, &snapds);

	if (err == 0) {
		/*
		 * If this is a deduplicated raw send stream, we need
		 * to make sure that we can still read raw blocks from
		 * earlier datasets in the stream, so we set the
		 * os_raw_receive flag now.
		 */
		if (raw) {
			err = dmu_objset_from_ds(snapds, &os);
			if (err != 0) {
				dsl_dataset_disown(snapds, dsflags, FTAG);
				dsl_pool_rele(dp, FTAG);
				kmem_free(gmep, sizeof (*gmep));
				return (err);
			}
			os->os_raw_receive = B_TRUE;
		}

		gmep->raw = raw;
		gmep->guid = dsl_dataset_phys(snapds)->ds_guid;
		gmep->gme_ds = snapds;
		avl_add(guid_map, gmep);
	} else {
		kmem_free(gmep, sizeof (*gmep));
	}

	dsl_pool_rele(dp, FTAG);
	return (err);
}