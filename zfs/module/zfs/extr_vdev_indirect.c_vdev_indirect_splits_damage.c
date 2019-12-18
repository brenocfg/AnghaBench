#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zio_t ;
struct TYPE_12__ {int iv_attempts_max; int /*<<< orphan*/  iv_splits; } ;
typedef  TYPE_1__ indirect_vsd_t ;
struct TYPE_13__ {int is_children; scalar_t__ is_unique_children; int /*<<< orphan*/  is_unique_child; TYPE_3__* is_good_child; TYPE_3__* is_child; } ;
typedef  TYPE_2__ indirect_split_t ;
struct TYPE_14__ {TYPE_10__* ic_data; } ;
typedef  TYPE_3__ indirect_child_t ;
struct TYPE_11__ {int /*<<< orphan*/  abd_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 unsigned long long UINT64_MAX ; 
 int /*<<< orphan*/  abd_zero (TYPE_10__*,int /*<<< orphan*/ ) ; 
 void* list_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_insert_tail (int /*<<< orphan*/ *,TYPE_3__*) ; 
 scalar_t__ list_is_empty (int /*<<< orphan*/ *) ; 
 TYPE_2__* list_next (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int vdev_indirect_splits_enumerate_randomly (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
vdev_indirect_splits_damage(indirect_vsd_t *iv, zio_t *zio)
{
	int error;

	/* Presume all the copies are unique for initial selection. */
	for (indirect_split_t *is = list_head(&iv->iv_splits);
	    is != NULL; is = list_next(&iv->iv_splits, is)) {
		is->is_unique_children = 0;

		for (int i = 0; i < is->is_children; i++) {
			indirect_child_t *ic = &is->is_child[i];
			if (ic->ic_data != NULL) {
				is->is_unique_children++;
				list_insert_tail(&is->is_unique_child, ic);
			}
		}

		if (list_is_empty(&is->is_unique_child)) {
			error = SET_ERROR(EIO);
			goto out;
		}
	}

	/*
	 * Set each is_good_child to a randomly-selected child which
	 * is known to contain validated data.
	 */
	error = vdev_indirect_splits_enumerate_randomly(iv, zio);
	if (error)
		goto out;

	/*
	 * Damage all but the known good copy by zeroing it.  This will
	 * result in two or less unique copies per indirect_child_t.
	 * Both may need to be checked in order to reconstruct the block.
	 * Set iv->iv_attempts_max such that all unique combinations will
	 * enumerated, but limit the damage to at most 12 indirect splits.
	 */
	iv->iv_attempts_max = 1;

	for (indirect_split_t *is = list_head(&iv->iv_splits);
	    is != NULL; is = list_next(&iv->iv_splits, is)) {
		for (int c = 0; c < is->is_children; c++) {
			indirect_child_t *ic = &is->is_child[c];

			if (ic == is->is_good_child)
				continue;
			if (ic->ic_data == NULL)
				continue;

			abd_zero(ic->ic_data, ic->ic_data->abd_size);
		}

		iv->iv_attempts_max *= 2;
		if (iv->iv_attempts_max >= (1ULL << 12)) {
			iv->iv_attempts_max = UINT64_MAX;
			break;
		}
	}

out:
	/* Empty the unique children lists so they can be reconstructed. */
	for (indirect_split_t *is = list_head(&iv->iv_splits);
	    is != NULL; is = list_next(&iv->iv_splits, is)) {
		indirect_child_t *ic;
		while ((ic = list_head(&is->is_unique_child)) != NULL)
			list_remove(&is->is_unique_child, ic);

		is->is_unique_children = 0;
	}

	return (error);
}