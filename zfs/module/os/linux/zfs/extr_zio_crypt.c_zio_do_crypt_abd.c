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
typedef  int /*<<< orphan*/  dmu_object_type_t ;
typedef  scalar_t__ boolean_t ;
typedef  int /*<<< orphan*/  abd_t ;

/* Variables and functions */
 void* abd_borrow_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* abd_borrow_buf_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abd_return_buf (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abd_return_buf_copy (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 int zio_do_crypt_data (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,void*,scalar_t__*) ; 

int
zio_do_crypt_abd(boolean_t encrypt, zio_crypt_key_t *key, dmu_object_type_t ot,
    boolean_t byteswap, uint8_t *salt, uint8_t *iv, uint8_t *mac,
    uint_t datalen, abd_t *pabd, abd_t *cabd, boolean_t *no_crypt)
{
	int ret;
	void *ptmp, *ctmp;

	if (encrypt) {
		ptmp = abd_borrow_buf_copy(pabd, datalen);
		ctmp = abd_borrow_buf(cabd, datalen);
	} else {
		ptmp = abd_borrow_buf(pabd, datalen);
		ctmp = abd_borrow_buf_copy(cabd, datalen);
	}

	ret = zio_do_crypt_data(encrypt, key, ot, byteswap, salt, iv, mac,
	    datalen, ptmp, ctmp, no_crypt);
	if (ret != 0)
		goto error;

	if (encrypt) {
		abd_return_buf(pabd, ptmp, datalen);
		abd_return_buf_copy(cabd, ctmp, datalen);
	} else {
		abd_return_buf_copy(pabd, ptmp, datalen);
		abd_return_buf(cabd, ctmp, datalen);
	}

	return (0);

error:
	if (encrypt) {
		abd_return_buf(pabd, ptmp, datalen);
		abd_return_buf_copy(cabd, ctmp, datalen);
	} else {
		abd_return_buf_copy(pabd, ptmp, datalen);
		abd_return_buf(cabd, ctmp, datalen);
	}

	return (ret);
}