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
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int ECKSUM ; 
 int /*<<< orphan*/  ZIO_CRYPT_KEY_CURRENT_VERSION ; 
 int zio_crypt_do_indirect_mac_checksum_impl (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
zio_crypt_do_indirect_mac_checksum(boolean_t generate, void *buf,
    uint_t datalen, boolean_t byteswap, uint8_t *cksum)
{
	int ret;

	/*
	 * Unfortunately, callers of this function will not always have
	 * easy access to the on-disk format version. This info is
	 * normally found in the DSL Crypto Key, but the checksum-of-MACs
	 * is expected to be verifiable even when the key isn't loaded.
	 * Here, instead of doing a ZAP lookup for the version for each
	 * zio, we simply try both existing formats.
	 */
	ret = zio_crypt_do_indirect_mac_checksum_impl(generate, buf,
	    datalen, ZIO_CRYPT_KEY_CURRENT_VERSION, byteswap, cksum);
	if (ret == ECKSUM) {
		ASSERT(!generate);
		ret = zio_crypt_do_indirect_mac_checksum_impl(generate,
		    buf, datalen, 0, byteswap, cksum);
	}

	return (ret);
}