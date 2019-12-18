#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_12__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  zap_ismicro; } ;
typedef  TYPE_1__ zap_t ;
struct TYPE_16__ {TYPE_1__* zn_zap; } ;
typedef  TYPE_2__ zap_name_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  mzap_ent_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_14__ {int mze_value; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  ENOTSUP ; 
 int /*<<< orphan*/  FTAG ; 
 scalar_t__ MZAP_NAME_LEN ; 
 TYPE_12__* MZE_PHYS (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RW_WRITER ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  dprintf (char*,int,int,int,char const*) ; 
 int fzap_update (TYPE_2__*,int,int,void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mzap_addent (TYPE_2__*,int const) ; 
 int mzap_upgrade (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mze_find (TYPE_2__*) ; 
 scalar_t__ strlen (char const*) ; 
 int zap_lockdir (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__**) ; 
 TYPE_2__* zap_name_alloc (TYPE_1__*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zap_name_free (TYPE_2__*) ; 
 int /*<<< orphan*/  zap_unlockdir (TYPE_1__*,int /*<<< orphan*/ ) ; 

int
zap_update(objset_t *os, uint64_t zapobj, const char *name,
    int integer_size, uint64_t num_integers, const void *val, dmu_tx_t *tx)
{
	zap_t *zap;
	const uint64_t *intval = val;

	int err =
	    zap_lockdir(os, zapobj, tx, RW_WRITER, TRUE, TRUE, FTAG, &zap);
	if (err != 0)
		return (err);
	zap_name_t *zn = zap_name_alloc(zap, name, 0);
	if (zn == NULL) {
		zap_unlockdir(zap, FTAG);
		return (SET_ERROR(ENOTSUP));
	}
	if (!zap->zap_ismicro) {
		err = fzap_update(zn, integer_size, num_integers, val,
		    FTAG, tx);
		zap = zn->zn_zap;	/* fzap_update() may change zap */
	} else if (integer_size != 8 || num_integers != 1 ||
	    strlen(name) >= MZAP_NAME_LEN) {
		dprintf("upgrading obj %llu: intsz=%u numint=%llu name=%s\n",
		    zapobj, integer_size, num_integers, name);
		err = mzap_upgrade(&zn->zn_zap, FTAG, tx, 0);
		if (err == 0) {
			err = fzap_update(zn, integer_size, num_integers,
			    val, FTAG, tx);
		}
		zap = zn->zn_zap;	/* fzap_update() may change zap */
	} else {
		mzap_ent_t *mze = mze_find(zn);
		if (mze != NULL) {
			MZE_PHYS(zap, mze)->mze_value = *intval;
		} else {
			mzap_addent(zn, *intval);
		}
	}
	ASSERT(zap == zn->zn_zap);
	zap_name_free(zn);
	if (zap != NULL)	/* may be NULL if fzap_upgrade() failed */
		zap_unlockdir(zap, FTAG);
	return (err);
}