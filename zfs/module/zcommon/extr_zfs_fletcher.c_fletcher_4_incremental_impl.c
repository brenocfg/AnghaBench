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
typedef  int /*<<< orphan*/  zio_cksum_t ;
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ MIN (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZFS_FLETCHER_4_INC_MAX_SIZE ; 
 int /*<<< orphan*/  fletcher_4_byteswap (void const*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fletcher_4_incremental_combine (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fletcher_4_native (void const*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
fletcher_4_incremental_impl(boolean_t native, const void *buf, uint64_t size,
    zio_cksum_t *zcp)
{
	while (size > 0) {
		zio_cksum_t nzc;
		uint64_t len = MIN(size, ZFS_FLETCHER_4_INC_MAX_SIZE);

		if (native)
			fletcher_4_native(buf, len, NULL, &nzc);
		else
			fletcher_4_byteswap(buf, len, NULL, &nzc);

		fletcher_4_incremental_combine(zcp, len, &nzc);

		size -= len;
		buf += len;
	}
}