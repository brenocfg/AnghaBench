#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uchar_t ;
struct TYPE_5__ {int iov_len; scalar_t__ iov_base; } ;
struct TYPE_6__ {int cd_format; int cd_length; scalar_t__ cd_offset; TYPE_1__ cd_raw; } ;
typedef  TYPE_2__ crypto_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  COPY_TO_DATA ; 
 int CRYPTO_ARGUMENTS_BAD ; 
 int CRYPTO_BUFFER_TOO_SMALL ; 
#define  CRYPTO_DATA_RAW 129 
#define  CRYPTO_DATA_UIO 128 
 int CRYPTO_SUCCESS ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int crypto_uio_data (TYPE_2__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
crypto_put_output_data(uchar_t *buf, crypto_data_t *output, int len)
{
	switch (output->cd_format) {
	case CRYPTO_DATA_RAW:
		if (output->cd_raw.iov_len < len) {
			output->cd_length = len;
			return (CRYPTO_BUFFER_TOO_SMALL);
		}
		bcopy(buf, (uchar_t *)(output->cd_raw.iov_base +
		    output->cd_offset), len);
		break;

	case CRYPTO_DATA_UIO:
		return (crypto_uio_data(output, buf, len,
		    COPY_TO_DATA, NULL, NULL));
	default:
		return (CRYPTO_ARGUMENTS_BAD);
	}

	return (CRYPTO_SUCCESS);
}