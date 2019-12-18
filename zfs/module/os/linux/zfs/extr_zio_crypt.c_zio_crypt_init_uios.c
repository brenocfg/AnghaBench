#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int uio_iovcnt; int /*<<< orphan*/ * uio_iov; void* uio_segflg; } ;
typedef  TYPE_1__ uio_t ;
typedef  int /*<<< orphan*/  uint_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_12__ {int /*<<< orphan*/  iov_len; int /*<<< orphan*/ * iov_base; } ;
typedef  TYPE_2__ iovec_t ;
typedef  int dmu_object_type_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  B_FALSE ; 
#define  DMU_OT_DNODE 129 
#define  DMU_OT_INTENT_LOG 128 
 scalar_t__ DMU_OT_IS_ENCRYPTED (int) ; 
 int DMU_OT_NONE ; 
 void* UIO_SYSSPACE ; 
 int /*<<< orphan*/  ZIO_DATA_MAC_LEN ; 
 int zio_crypt_init_uios_dnode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int zio_crypt_init_uios_normal (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int zio_crypt_init_uios_zil (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zio_crypt_init_uios(boolean_t encrypt, uint64_t version, dmu_object_type_t ot,
    uint8_t *plainbuf, uint8_t *cipherbuf, uint_t datalen, boolean_t byteswap,
    uint8_t *mac, uio_t *puio, uio_t *cuio, uint_t *enc_len, uint8_t **authbuf,
    uint_t *auth_len, boolean_t *no_crypt)
{
	int ret;
	iovec_t *mac_iov;

	ASSERT(DMU_OT_IS_ENCRYPTED(ot) || ot == DMU_OT_NONE);

	/* route to handler */
	switch (ot) {
	case DMU_OT_INTENT_LOG:
		ret = zio_crypt_init_uios_zil(encrypt, plainbuf, cipherbuf,
		    datalen, byteswap, puio, cuio, enc_len, authbuf, auth_len,
		    no_crypt);
		break;
	case DMU_OT_DNODE:
		ret = zio_crypt_init_uios_dnode(encrypt, version, plainbuf,
		    cipherbuf, datalen, byteswap, puio, cuio, enc_len, authbuf,
		    auth_len, no_crypt);
		break;
	default:
		ret = zio_crypt_init_uios_normal(encrypt, plainbuf, cipherbuf,
		    datalen, puio, cuio, enc_len);
		*authbuf = NULL;
		*auth_len = 0;
		*no_crypt = B_FALSE;
		break;
	}

	if (ret != 0)
		goto error;

	/* populate the uios */
	puio->uio_segflg = UIO_SYSSPACE;
	cuio->uio_segflg = UIO_SYSSPACE;

	mac_iov = ((iovec_t *)&cuio->uio_iov[cuio->uio_iovcnt - 1]);
	mac_iov->iov_base = mac;
	mac_iov->iov_len = ZIO_DATA_MAC_LEN;

	return (0);

error:
	return (ret);
}