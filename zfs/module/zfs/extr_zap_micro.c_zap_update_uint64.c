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
typedef  int /*<<< orphan*/  zap_t ;
struct TYPE_5__ {int /*<<< orphan*/ * zn_zap; } ;
typedef  TYPE_1__ zap_name_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOTSUP ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  RW_WRITER ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int fzap_update (TYPE_1__*,int,int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int zap_lockdir (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 TYPE_1__* zap_name_alloc_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  zap_name_free (TYPE_1__*) ; 
 int /*<<< orphan*/  zap_unlockdir (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
zap_update_uint64(objset_t *os, uint64_t zapobj, const uint64_t *key,
    int key_numints,
    int integer_size, uint64_t num_integers, const void *val, dmu_tx_t *tx)
{
	zap_t *zap;

	int err =
	    zap_lockdir(os, zapobj, tx, RW_WRITER, TRUE, TRUE, FTAG, &zap);
	if (err != 0)
		return (err);
	zap_name_t *zn = zap_name_alloc_uint64(zap, key, key_numints);
	if (zn == NULL) {
		zap_unlockdir(zap, FTAG);
		return (SET_ERROR(ENOTSUP));
	}
	err = fzap_update(zn, integer_size, num_integers, val, FTAG, tx);
	zap = zn->zn_zap;	/* fzap_update() may change zap */
	zap_name_free(zn);
	if (zap != NULL)	/* may be NULL if fzap_upgrade() failed */
		zap_unlockdir(zap, FTAG);
	return (err);
}