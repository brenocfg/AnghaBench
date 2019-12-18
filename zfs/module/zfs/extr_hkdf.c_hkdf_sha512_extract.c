#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_10__ {scalar_t__ cm_param_len; int /*<<< orphan*/ * cm_param; int /*<<< orphan*/  cm_type; } ;
typedef  TYPE_2__ crypto_mechanism_t ;
struct TYPE_11__ {int /*<<< orphan*/ * ck_data; int /*<<< orphan*/  ck_length; int /*<<< orphan*/  ck_format; } ;
typedef  TYPE_3__ crypto_key_t ;
struct TYPE_9__ {char* iov_base; int /*<<< orphan*/  iov_len; } ;
struct TYPE_12__ {int /*<<< orphan*/  cd_length; TYPE_1__ cd_raw; scalar_t__ cd_offset; void* cd_format; } ;
typedef  TYPE_4__ crypto_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_BYTES2BITS (int /*<<< orphan*/ ) ; 
 void* CRYPTO_DATA_RAW ; 
 int /*<<< orphan*/  CRYPTO_KEY_RAW ; 
 int CRYPTO_SUCCESS ; 
 int /*<<< orphan*/  EIO ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHA512_DIGEST_LENGTH ; 
 int /*<<< orphan*/  SUN_CKM_SHA512_HMAC ; 
 int crypto_mac (TYPE_2__*,TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_mech2id (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hkdf_sha512_extract(uint8_t *salt, uint_t salt_len, uint8_t *key_material,
    uint_t km_len, uint8_t *out_buf)
{
	int ret;
	crypto_mechanism_t mech;
	crypto_key_t key;
	crypto_data_t input_cd, output_cd;

	/* initialize HMAC mechanism */
	mech.cm_type = crypto_mech2id(SUN_CKM_SHA512_HMAC);
	mech.cm_param = NULL;
	mech.cm_param_len = 0;

	/* initialize the salt as a crypto key */
	key.ck_format = CRYPTO_KEY_RAW;
	key.ck_length = CRYPTO_BYTES2BITS(salt_len);
	key.ck_data = salt;

	/* initialize crypto data for the input and output data */
	input_cd.cd_format = CRYPTO_DATA_RAW;
	input_cd.cd_offset = 0;
	input_cd.cd_length = km_len;
	input_cd.cd_raw.iov_base = (char *)key_material;
	input_cd.cd_raw.iov_len = input_cd.cd_length;

	output_cd.cd_format = CRYPTO_DATA_RAW;
	output_cd.cd_offset = 0;
	output_cd.cd_length = SHA512_DIGEST_LENGTH;
	output_cd.cd_raw.iov_base = (char *)out_buf;
	output_cd.cd_raw.iov_len = output_cd.cd_length;

	ret = crypto_mac(&mech, &input_cd, &key, NULL, &output_cd, NULL);
	if (ret != CRYPTO_SUCCESS)
		return (SET_ERROR(EIO));

	return (0);
}