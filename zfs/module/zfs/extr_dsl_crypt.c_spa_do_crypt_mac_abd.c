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
typedef  int /*<<< orphan*/  uint_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
struct TYPE_4__ {int /*<<< orphan*/  dck_key; } ;
typedef  TYPE_1__ dsl_crypto_key_t ;
typedef  scalar_t__ boolean_t ;
typedef  int /*<<< orphan*/  abd_t ;

/* Variables and functions */
 int /*<<< orphan*/  ECKSUM ; 
 int /*<<< orphan*/  FTAG ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int ZIO_DATA_MAC_LEN ; 
 int /*<<< orphan*/ * abd_borrow_buf_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abd_return_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ bcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spa_keystore_dsl_key_rele (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int spa_keystore_lookup_key (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int zio_crypt_do_hmac (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int
spa_do_crypt_mac_abd(boolean_t generate, spa_t *spa, uint64_t dsobj, abd_t *abd,
    uint_t datalen, uint8_t *mac)
{
	int ret;
	dsl_crypto_key_t *dck = NULL;
	uint8_t *buf = abd_borrow_buf_copy(abd, datalen);
	uint8_t digestbuf[ZIO_DATA_MAC_LEN];

	/* look up the key from the spa's keystore */
	ret = spa_keystore_lookup_key(spa, dsobj, FTAG, &dck);
	if (ret != 0)
		goto error;

	/* perform the hmac */
	ret = zio_crypt_do_hmac(&dck->dck_key, buf, datalen,
	    digestbuf, ZIO_DATA_MAC_LEN);
	if (ret != 0)
		goto error;

	abd_return_buf(abd, buf, datalen);
	spa_keystore_dsl_key_rele(spa, dck, FTAG);

	/*
	 * Truncate and fill in mac buffer if we were asked to generate a MAC.
	 * Otherwise verify that the MAC matched what we expected.
	 */
	if (generate) {
		bcopy(digestbuf, mac, ZIO_DATA_MAC_LEN);
		return (0);
	}

	if (bcmp(digestbuf, mac, ZIO_DATA_MAC_LEN) != 0)
		return (SET_ERROR(ECKSUM));

	return (0);

error:
	if (dck != NULL)
		spa_keystore_dsl_key_rele(spa, dck, FTAG);
	abd_return_buf(abd, buf, datalen);
	return (ret);
}