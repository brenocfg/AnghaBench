#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  zap_ismicro; } ;
typedef  TYPE_1__ zap_t ;
typedef  int /*<<< orphan*/  zap_name_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  mzap_ent_t ;
typedef  int /*<<< orphan*/  matchtype_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_8__ {int mze_value; int /*<<< orphan*/  mze_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ENOTSUP ; 
 int /*<<< orphan*/  EOVERFLOW ; 
 TYPE_5__* MZE_PHYS (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int fzap_lookup (int /*<<< orphan*/ *,int,int,void*,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mzap_normalization_conflict (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mze_find (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * zap_name_alloc (TYPE_1__*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zap_name_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zap_lookup_impl(zap_t *zap, const char *name,
    uint64_t integer_size, uint64_t num_integers, void *buf,
    matchtype_t mt, char *realname, int rn_len,
    boolean_t *ncp)
{
	int err = 0;

	zap_name_t *zn = zap_name_alloc(zap, name, mt);
	if (zn == NULL)
		return (SET_ERROR(ENOTSUP));

	if (!zap->zap_ismicro) {
		err = fzap_lookup(zn, integer_size, num_integers, buf,
		    realname, rn_len, ncp);
	} else {
		mzap_ent_t *mze = mze_find(zn);
		if (mze == NULL) {
			err = SET_ERROR(ENOENT);
		} else {
			if (num_integers < 1) {
				err = SET_ERROR(EOVERFLOW);
			} else if (integer_size != 8) {
				err = SET_ERROR(EINVAL);
			} else {
				*(uint64_t *)buf =
				    MZE_PHYS(zap, mze)->mze_value;
				(void) strlcpy(realname,
				    MZE_PHYS(zap, mze)->mze_name, rn_len);
				if (ncp) {
					*ncp = mzap_normalization_conflict(zap,
					    zn, mze);
				}
			}
		}
	}
	zap_name_free(zn);
	return (err);
}