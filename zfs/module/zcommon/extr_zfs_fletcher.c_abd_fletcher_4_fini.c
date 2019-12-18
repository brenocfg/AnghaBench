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
struct TYPE_5__ {scalar_t__ acd_byteorder; int /*<<< orphan*/  acd_zcp; int /*<<< orphan*/  acd_ctx; scalar_t__ acd_private; } ;
typedef  TYPE_1__ zio_abd_checksum_data_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* fini_byteswap ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* fini_native ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ fletcher_4_ops_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (TYPE_2__*) ; 
 scalar_t__ ZIO_CHECKSUM_NATIVE ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
abd_fletcher_4_fini(zio_abd_checksum_data_t *cdp)
{
	fletcher_4_ops_t *ops = (fletcher_4_ops_t *)cdp->acd_private;

	ASSERT(ops);

	if (cdp->acd_byteorder == ZIO_CHECKSUM_NATIVE)
		ops->fini_native(cdp->acd_ctx, cdp->acd_zcp);
	else
		ops->fini_byteswap(cdp->acd_ctx, cdp->acd_zcp);
}