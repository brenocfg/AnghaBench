#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {uintptr_t uio_iovcnt; TYPE_1__* uio_iov; } ;
typedef  TYPE_2__ uio_t ;
typedef  int /*<<< orphan*/  offset_t ;
struct TYPE_7__ {int cd_format; int /*<<< orphan*/  cd_offset; TYPE_2__* cd_uio; } ;
typedef  TYPE_3__ crypto_data_t ;
struct TYPE_5__ {int /*<<< orphan*/  iov_len; } ;

/* Variables and functions */
#define  CRYPTO_DATA_RAW 129 
#define  CRYPTO_DATA_UIO 128 

void
crypto_init_ptrs(crypto_data_t *out, void **iov_or_mp, offset_t *current_offset)
{
	offset_t offset;

	switch (out->cd_format) {
	case CRYPTO_DATA_RAW:
		*current_offset = out->cd_offset;
		break;

	case CRYPTO_DATA_UIO: {
		uio_t *uiop = out->cd_uio;
		uintptr_t vec_idx;

		offset = out->cd_offset;
		for (vec_idx = 0; vec_idx < uiop->uio_iovcnt &&
		    offset >= uiop->uio_iov[vec_idx].iov_len;
		    offset -= uiop->uio_iov[vec_idx++].iov_len)
			;

		*current_offset = offset;
		*iov_or_mp = (void *)vec_idx;
		break;
	}
	} /* end switch */
}