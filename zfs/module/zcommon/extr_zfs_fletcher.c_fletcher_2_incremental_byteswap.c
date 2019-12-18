#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__* zc_word; } ;
typedef  TYPE_1__ zio_cksum_t ;
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 scalar_t__ BSWAP_64 (scalar_t__ const) ; 
 int /*<<< orphan*/  ZIO_SET_CHECKSUM (TYPE_1__*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 

int
fletcher_2_incremental_byteswap(void *buf, size_t size, void *data)
{
	zio_cksum_t *zcp = data;

	const uint64_t *ip = buf;
	const uint64_t *ipend = ip + (size / sizeof (uint64_t));
	uint64_t a0, b0, a1, b1;

	a0 = zcp->zc_word[0];
	a1 = zcp->zc_word[1];
	b0 = zcp->zc_word[2];
	b1 = zcp->zc_word[3];

	for (; ip < ipend; ip += 2) {
		a0 += BSWAP_64(ip[0]);
		a1 += BSWAP_64(ip[1]);
		b0 += a0;
		b1 += a1;
	}

	ZIO_SET_CHECKSUM(zcp, a0, a1, b0, b1);
	return (0);
}