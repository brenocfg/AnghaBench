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
typedef  int /*<<< orphan*/  abd_t ;

/* Variables and functions */
 void* abd_borrow_buf_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abd_return_buf (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 int zio_crypt_do_indirect_mac_checksum (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
zio_crypt_do_indirect_mac_checksum_abd(boolean_t generate, abd_t *abd,
    uint_t datalen, boolean_t byteswap, uint8_t *cksum)
{
	int ret;
	void *buf;

	buf = abd_borrow_buf_copy(abd, datalen);
	ret = zio_crypt_do_indirect_mac_checksum(generate, buf, datalen,
	    byteswap, cksum);
	abd_return_buf(abd, buf, datalen);

	return (ret);
}