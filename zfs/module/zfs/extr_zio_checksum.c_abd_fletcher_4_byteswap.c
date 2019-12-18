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
typedef  int /*<<< orphan*/  zio_cksum_t ;
struct TYPE_3__ {int /*<<< orphan*/ * acd_ctx; int /*<<< orphan*/ * acd_zcp; int /*<<< orphan*/  acd_byteorder; } ;
typedef  TYPE_1__ zio_abd_checksum_data_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  fletcher_4_ctx_t ;
typedef  int /*<<< orphan*/  abd_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZIO_CHECKSUM_BYTESWAP ; 
 int /*<<< orphan*/  abd_fletcher_4_impl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 

void
abd_fletcher_4_byteswap(abd_t *abd, uint64_t size,
    const void *ctx_template, zio_cksum_t *zcp)
{
	fletcher_4_ctx_t ctx;

	zio_abd_checksum_data_t acd = {
		.acd_byteorder	= ZIO_CHECKSUM_BYTESWAP,
		.acd_zcp 	= zcp,
		.acd_ctx	= &ctx
	};

	abd_fletcher_4_impl(abd, size, &acd);
}