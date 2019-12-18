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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZIO_DATA_IV_LEN ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int random_get_pseudo_bytes (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
zio_crypt_generate_iv(uint8_t *ivbuf)
{
	int ret;

	/* randomly generate the IV */
	ret = random_get_pseudo_bytes(ivbuf, ZIO_DATA_IV_LEN);
	if (ret != 0)
		goto error;

	return (0);

error:
	bzero(ivbuf, ZIO_DATA_IV_LEN);
	return (ret);
}