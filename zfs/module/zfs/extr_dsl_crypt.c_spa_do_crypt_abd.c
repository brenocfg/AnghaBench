#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  zb_objset; } ;
typedef  TYPE_1__ zbookmark_phys_t ;
typedef  int /*<<< orphan*/  uint_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  spa_t ;
struct TYPE_8__ {int /*<<< orphan*/  dck_key; } ;
typedef  TYPE_2__ dsl_crypto_key_t ;
typedef  int /*<<< orphan*/  dmu_object_type_t ;
typedef  scalar_t__ boolean_t ;
typedef  int /*<<< orphan*/  abd_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMU_OT_DNODE ; 
 int /*<<< orphan*/  DMU_OT_INTENT_LOG ; 
 int /*<<< orphan*/  EACCES ; 
 int /*<<< orphan*/  ECKSUM ; 
 int /*<<< orphan*/  FTAG ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPA_FEATURE_ENCRYPTION ; 
 int /*<<< orphan*/  ZIO_DATA_IV_LEN ; 
 int /*<<< orphan*/  ZIO_DATA_MAC_LEN ; 
 int /*<<< orphan*/  ZIO_DATA_SALT_LEN ; 
 int /*<<< orphan*/ * abd_borrow_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * abd_borrow_buf_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abd_return_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abd_return_buf_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_feature_is_active (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_keystore_dsl_key_rele (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int spa_keystore_lookup_key (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__**) ; 
 int zio_crypt_generate_iv (int /*<<< orphan*/ *) ; 
 int zio_crypt_generate_iv_salt_dedup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int zio_crypt_key_get_salt (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int zio_do_crypt_data (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int zio_handle_decrypt_injection (int /*<<< orphan*/ *,TYPE_1__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ zio_injection_enabled ; 

int
spa_do_crypt_abd(boolean_t encrypt, spa_t *spa, const zbookmark_phys_t *zb,
    dmu_object_type_t ot, boolean_t dedup, boolean_t bswap, uint8_t *salt,
    uint8_t *iv, uint8_t *mac, uint_t datalen, abd_t *pabd, abd_t *cabd,
    boolean_t *no_crypt)
{
	int ret;
	dsl_crypto_key_t *dck = NULL;
	uint8_t *plainbuf = NULL, *cipherbuf = NULL;

	ASSERT(spa_feature_is_active(spa, SPA_FEATURE_ENCRYPTION));

	/* look up the key from the spa's keystore */
	ret = spa_keystore_lookup_key(spa, zb->zb_objset, FTAG, &dck);
	if (ret != 0) {
		ret = SET_ERROR(EACCES);
		return (ret);
	}

	if (encrypt) {
		plainbuf = abd_borrow_buf_copy(pabd, datalen);
		cipherbuf = abd_borrow_buf(cabd, datalen);
	} else {
		plainbuf = abd_borrow_buf(pabd, datalen);
		cipherbuf = abd_borrow_buf_copy(cabd, datalen);
	}

	/*
	 * Both encryption and decryption functions need a salt for key
	 * generation and an IV. When encrypting a non-dedup block, we
	 * generate the salt and IV randomly to be stored by the caller. Dedup
	 * blocks perform a (more expensive) HMAC of the plaintext to obtain
	 * the salt and the IV. ZIL blocks have their salt and IV generated
	 * at allocation time in zio_alloc_zil(). On decryption, we simply use
	 * the provided values.
	 */
	if (encrypt && ot != DMU_OT_INTENT_LOG && !dedup) {
		ret = zio_crypt_key_get_salt(&dck->dck_key, salt);
		if (ret != 0)
			goto error;

		ret = zio_crypt_generate_iv(iv);
		if (ret != 0)
			goto error;
	} else if (encrypt && dedup) {
		ret = zio_crypt_generate_iv_salt_dedup(&dck->dck_key,
		    plainbuf, datalen, iv, salt);
		if (ret != 0)
			goto error;
	}

	/* call lower level function to perform encryption / decryption */
	ret = zio_do_crypt_data(encrypt, &dck->dck_key, ot, bswap, salt, iv,
	    mac, datalen, plainbuf, cipherbuf, no_crypt);

	/*
	 * Handle injected decryption faults. Unfortunately, we cannot inject
	 * faults for dnode blocks because we might trigger the panic in
	 * dbuf_prepare_encrypted_dnode_leaf(), which exists because syncing
	 * context is not prepared to handle malicious decryption failures.
	 */
	if (zio_injection_enabled && !encrypt && ot != DMU_OT_DNODE && ret == 0)
		ret = zio_handle_decrypt_injection(spa, zb, ot, ECKSUM);
	if (ret != 0)
		goto error;

	if (encrypt) {
		abd_return_buf(pabd, plainbuf, datalen);
		abd_return_buf_copy(cabd, cipherbuf, datalen);
	} else {
		abd_return_buf_copy(pabd, plainbuf, datalen);
		abd_return_buf(cabd, cipherbuf, datalen);
	}

	spa_keystore_dsl_key_rele(spa, dck, FTAG);

	return (0);

error:
	if (encrypt) {
		/* zero out any state we might have changed while encrypting */
		bzero(salt, ZIO_DATA_SALT_LEN);
		bzero(iv, ZIO_DATA_IV_LEN);
		bzero(mac, ZIO_DATA_MAC_LEN);
		abd_return_buf(pabd, plainbuf, datalen);
		abd_return_buf_copy(cabd, cipherbuf, datalen);
	} else {
		abd_return_buf_copy(pabd, plainbuf, datalen);
		abd_return_buf(cabd, cipherbuf, datalen);
	}

	spa_keystore_dsl_key_rele(spa, dck, FTAG);

	return (ret);
}