#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mod_hash_val_t ;
struct TYPE_4__ {int /*<<< orphan*/  mh_contents; } ;
typedef  TYPE_1__ mod_hash_t ;
typedef  int /*<<< orphan*/  mod_hash_key_t ;

/* Variables and functions */
 int /*<<< orphan*/  RW_READER ; 
 int i_mod_hash_find_nosync (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_exit (int /*<<< orphan*/ *) ; 

int
mod_hash_find_cb_rval(mod_hash_t *hash, mod_hash_key_t key, mod_hash_val_t *val,
    int (*find_cb)(mod_hash_key_t, mod_hash_val_t), int *cb_rval)
{
	int res;

	rw_enter(&hash->mh_contents, RW_READER);
	res = i_mod_hash_find_nosync(hash, key, val);
	if (res == 0) {
		*cb_rval = find_cb(key, *val);
	}
	rw_exit(&hash->mh_contents);

	return (res);
}