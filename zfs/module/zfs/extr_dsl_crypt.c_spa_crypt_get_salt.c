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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
struct TYPE_4__ {int /*<<< orphan*/  dck_key; } ;
typedef  TYPE_1__ dsl_crypto_key_t ;

/* Variables and functions */
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  spa_keystore_dsl_key_rele (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int spa_keystore_lookup_key (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int zio_crypt_key_get_salt (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
spa_crypt_get_salt(spa_t *spa, uint64_t dsobj, uint8_t *salt)
{
	int ret;
	dsl_crypto_key_t *dck = NULL;

	/* look up the key from the spa's keystore */
	ret = spa_keystore_lookup_key(spa, dsobj, FTAG, &dck);
	if (ret != 0)
		goto error;

	ret = zio_crypt_key_get_salt(&dck->dck_key, salt);
	if (ret != 0)
		goto error;

	spa_keystore_dsl_key_rele(spa, dck, FTAG);
	return (0);

error:
	if (dck != NULL)
		spa_keystore_dsl_key_rele(spa, dck, FTAG);
	return (ret);
}