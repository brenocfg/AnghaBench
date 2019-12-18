#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  zn_zap; int /*<<< orphan*/  zn_hash; } ;
typedef  TYPE_1__ zap_name_t ;
typedef  int /*<<< orphan*/  zap_leaf_t ;
typedef  int /*<<< orphan*/  zap_entry_handle_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  RW_READER ; 
 int fzap_checkname (TYPE_1__*) ; 
 int fzap_checksize (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int zap_deref_leaf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  zap_entry_normalization_conflict (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int zap_entry_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  zap_entry_read_name (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*) ; 
 int zap_leaf_lookup (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_put_leaf (int /*<<< orphan*/ *) ; 

int
fzap_lookup(zap_name_t *zn,
    uint64_t integer_size, uint64_t num_integers, void *buf,
    char *realname, int rn_len, boolean_t *ncp)
{
	zap_leaf_t *l;
	zap_entry_handle_t zeh;

	int err = fzap_checkname(zn);
	if (err != 0)
		return (err);

	err = zap_deref_leaf(zn->zn_zap, zn->zn_hash, NULL, RW_READER, &l);
	if (err != 0)
		return (err);
	err = zap_leaf_lookup(l, zn, &zeh);
	if (err == 0) {
		if ((err = fzap_checksize(integer_size, num_integers)) != 0) {
			zap_put_leaf(l);
			return (err);
		}

		err = zap_entry_read(&zeh, integer_size, num_integers, buf);
		(void) zap_entry_read_name(zn->zn_zap, &zeh, rn_len, realname);
		if (ncp) {
			*ncp = zap_entry_normalization_conflict(&zeh,
			    zn, NULL, zn->zn_zap);
		}
	}

	zap_put_leaf(l);
	return (err);
}