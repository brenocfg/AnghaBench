#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  zio_crypt_key_t ;
typedef  int /*<<< orphan*/  uint_t ;
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int SHA512_DIGEST_LENGTH ; 
 int ZIO_DATA_IV_LEN ; 
 int ZIO_DATA_SALT_LEN ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int zio_crypt_do_hmac (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int
zio_crypt_generate_iv_salt_dedup(zio_crypt_key_t *key, uint8_t *data,
    uint_t datalen, uint8_t *ivbuf, uint8_t *salt)
{
	int ret;
	uint8_t digestbuf[SHA512_DIGEST_LENGTH];

	ret = zio_crypt_do_hmac(key, data, datalen,
	    digestbuf, SHA512_DIGEST_LENGTH);
	if (ret != 0)
		return (ret);

	bcopy(digestbuf, salt, ZIO_DATA_SALT_LEN);
	bcopy(digestbuf + ZIO_DATA_SALT_LEN, ivbuf, ZIO_DATA_IV_LEN);

	return (0);
}