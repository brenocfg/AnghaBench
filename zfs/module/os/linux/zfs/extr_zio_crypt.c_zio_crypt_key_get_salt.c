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
struct TYPE_4__ {int /*<<< orphan*/  zk_salt_lock; int /*<<< orphan*/  zk_salt_count; int /*<<< orphan*/  zk_salt; } ;
typedef  TYPE_1__ zio_crypt_key_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  RW_READER ; 
 scalar_t__ ZFS_CURRENT_MAX_SALT_USES ; 
 int /*<<< orphan*/  ZIO_DATA_SALT_LEN ; 
 scalar_t__ atomic_inc_64_nv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_exit (int /*<<< orphan*/ *) ; 
 int zio_crypt_key_change_salt (TYPE_1__*) ; 

int
zio_crypt_key_get_salt(zio_crypt_key_t *key, uint8_t *salt)
{
	int ret;
	boolean_t salt_change;

	rw_enter(&key->zk_salt_lock, RW_READER);

	bcopy(key->zk_salt, salt, ZIO_DATA_SALT_LEN);
	salt_change = (atomic_inc_64_nv(&key->zk_salt_count) >=
	    ZFS_CURRENT_MAX_SALT_USES);

	rw_exit(&key->zk_salt_lock);

	if (salt_change) {
		ret = zio_crypt_key_change_salt(key);
		if (ret != 0)
			goto error;
	}

	return (0);

error:
	return (ret);
}