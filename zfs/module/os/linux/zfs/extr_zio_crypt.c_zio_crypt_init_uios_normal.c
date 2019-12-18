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
struct TYPE_7__ {int uio_iovcnt; TYPE_2__* uio_iov; } ;
typedef  TYPE_1__ uio_t ;
typedef  int uint_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_8__ {int iov_len; int /*<<< orphan*/ * iov_base; } ;
typedef  TYPE_2__ iovec_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 TYPE_2__* kmem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (TYPE_2__*,int) ; 

__attribute__((used)) static int
zio_crypt_init_uios_normal(boolean_t encrypt, uint8_t *plainbuf,
    uint8_t *cipherbuf, uint_t datalen, uio_t *puio, uio_t *cuio,
    uint_t *enc_len)
{
	int ret;
	uint_t nr_plain = 1, nr_cipher = 2;
	iovec_t *plain_iovecs = NULL, *cipher_iovecs = NULL;

	/* allocate the iovecs for the plain and cipher data */
	plain_iovecs = kmem_alloc(nr_plain * sizeof (iovec_t),
	    KM_SLEEP);
	if (!plain_iovecs) {
		ret = SET_ERROR(ENOMEM);
		goto error;
	}

	cipher_iovecs = kmem_alloc(nr_cipher * sizeof (iovec_t),
	    KM_SLEEP);
	if (!cipher_iovecs) {
		ret = SET_ERROR(ENOMEM);
		goto error;
	}

	plain_iovecs[0].iov_base = plainbuf;
	plain_iovecs[0].iov_len = datalen;
	cipher_iovecs[0].iov_base = cipherbuf;
	cipher_iovecs[0].iov_len = datalen;

	*enc_len = datalen;
	puio->uio_iov = plain_iovecs;
	puio->uio_iovcnt = nr_plain;
	cuio->uio_iov = cipher_iovecs;
	cuio->uio_iovcnt = nr_cipher;

	return (0);

error:
	if (plain_iovecs != NULL)
		kmem_free(plain_iovecs, nr_plain * sizeof (iovec_t));
	if (cipher_iovecs != NULL)
		kmem_free(cipher_iovecs, nr_cipher * sizeof (iovec_t));

	*enc_len = 0;
	puio->uio_iov = NULL;
	puio->uio_iovcnt = 0;
	cuio->uio_iov = NULL;
	cuio->uio_iovcnt = 0;
	return (ret);
}