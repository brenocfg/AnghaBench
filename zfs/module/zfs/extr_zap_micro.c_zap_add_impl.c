#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  zap_ismicro; } ;
typedef  TYPE_1__ zap_t ;
struct TYPE_14__ {TYPE_1__* zn_zap; int /*<<< orphan*/  zn_hash; } ;
typedef  TYPE_2__ zap_name_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  EEXIST ; 
 int /*<<< orphan*/  ENOTSUP ; 
 scalar_t__ MZAP_NAME_LEN ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int fzap_add (TYPE_2__*,int,int,void const*,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mzap_addent (TYPE_2__*,int const) ; 
 int mzap_upgrade (TYPE_1__**,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mze_canfit_fzap_leaf (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mze_find (TYPE_2__*) ; 
 scalar_t__ strlen (char const*) ; 
 TYPE_2__* zap_name_alloc (TYPE_1__*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zap_name_free (TYPE_2__*) ; 
 int /*<<< orphan*/  zap_unlockdir (TYPE_1__*,void*) ; 

__attribute__((used)) static int
zap_add_impl(zap_t *zap, const char *key,
    int integer_size, uint64_t num_integers,
    const void *val, dmu_tx_t *tx, void *tag)
{
	const uint64_t *intval = val;
	int err = 0;

	zap_name_t *zn = zap_name_alloc(zap, key, 0);
	if (zn == NULL) {
		zap_unlockdir(zap, tag);
		return (SET_ERROR(ENOTSUP));
	}
	if (!zap->zap_ismicro) {
		err = fzap_add(zn, integer_size, num_integers, val, tag, tx);
		zap = zn->zn_zap;	/* fzap_add() may change zap */
	} else if (integer_size != 8 || num_integers != 1 ||
	    strlen(key) >= MZAP_NAME_LEN ||
	    !mze_canfit_fzap_leaf(zn, zn->zn_hash)) {
		err = mzap_upgrade(&zn->zn_zap, tag, tx, 0);
		if (err == 0) {
			err = fzap_add(zn, integer_size, num_integers, val,
			    tag, tx);
		}
		zap = zn->zn_zap;	/* fzap_add() may change zap */
	} else {
		if (mze_find(zn) != NULL) {
			err = SET_ERROR(EEXIST);
		} else {
			mzap_addent(zn, *intval);
		}
	}
	ASSERT(zap == zn->zn_zap);
	zap_name_free(zn);
	if (zap != NULL)	/* may be NULL if fzap_add() failed */
		zap_unlockdir(zap, tag);
	return (err);
}