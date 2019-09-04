#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  tsd_t ;
typedef  int /*<<< orphan*/  ckh_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ ckh_grow (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ckh_search (int /*<<< orphan*/ *,void const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ckh_try_insert (int /*<<< orphan*/ *,void const**,void const**) ; 

bool
ckh_insert(tsd_t *tsd, ckh_t *ckh, const void *key, const void *data) {
	bool ret;

	assert(ckh != NULL);
	assert(ckh_search(ckh, key, NULL, NULL));

#ifdef CKH_COUNT
	ckh->ninserts++;
#endif

	while (ckh_try_insert(ckh, &key, &data)) {
		if (ckh_grow(tsd, ckh)) {
			ret = true;
			goto label_return;
		}
	}

	ret = false;
label_return:
	return ret;
}