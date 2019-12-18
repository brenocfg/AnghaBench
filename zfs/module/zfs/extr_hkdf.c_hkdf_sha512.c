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
typedef  int /*<<< orphan*/  uint_t ;
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int SHA512_DIGEST_LENGTH ; 
 int hkdf_sha512_expand (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int hkdf_sha512_extract (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
hkdf_sha512(uint8_t *key_material, uint_t km_len, uint8_t *salt,
    uint_t salt_len, uint8_t *info, uint_t info_len, uint8_t *output_key,
    uint_t out_len)
{
	int ret;
	uint8_t extract_key[SHA512_DIGEST_LENGTH];

	ret = hkdf_sha512_extract(salt, salt_len, key_material, km_len,
	    extract_key);
	if (ret != 0)
		return (ret);

	ret = hkdf_sha512_expand(extract_key, info, info_len, output_key,
	    out_len);
	if (ret != 0)
		return (ret);

	return (0);
}