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
struct TYPE_5__ {int /*<<< orphan*/  zap_ismicro; } ;
typedef  TYPE_1__ zap_t ;
typedef  int /*<<< orphan*/  zap_name_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  mzap_ent_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ENOTSUP ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  RW_READER ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int fzap_length (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/ * mze_find (int /*<<< orphan*/ *) ; 
 int zap_lockdir (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/ * zap_name_alloc (TYPE_1__*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zap_name_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_unlockdir (TYPE_1__*,int /*<<< orphan*/ ) ; 

int
zap_length(objset_t *os, uint64_t zapobj, const char *name,
    uint64_t *integer_size, uint64_t *num_integers)
{
	zap_t *zap;

	int err =
	    zap_lockdir(os, zapobj, NULL, RW_READER, TRUE, FALSE, FTAG, &zap);
	if (err != 0)
		return (err);
	zap_name_t *zn = zap_name_alloc(zap, name, 0);
	if (zn == NULL) {
		zap_unlockdir(zap, FTAG);
		return (SET_ERROR(ENOTSUP));
	}
	if (!zap->zap_ismicro) {
		err = fzap_length(zn, integer_size, num_integers);
	} else {
		mzap_ent_t *mze = mze_find(zn);
		if (mze == NULL) {
			err = SET_ERROR(ENOENT);
		} else {
			if (integer_size)
				*integer_size = 8;
			if (num_integers)
				*num_integers = 1;
		}
	}
	zap_name_free(zn);
	zap_unlockdir(zap, FTAG);
	return (err);
}