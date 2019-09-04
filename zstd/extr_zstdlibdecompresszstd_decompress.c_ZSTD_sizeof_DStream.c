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
typedef  int /*<<< orphan*/  ZSTD_DStream ;

/* Variables and functions */
 size_t ZSTD_sizeof_DCtx (int /*<<< orphan*/  const*) ; 

size_t ZSTD_sizeof_DStream(const ZSTD_DStream* dctx)
{
    return ZSTD_sizeof_DCtx(dctx);
}