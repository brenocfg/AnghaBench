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
typedef  int /*<<< orphan*/  ZSTD_customMem ;
typedef  int /*<<< orphan*/  POOL_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  g_ctx ; 

POOL_ctx* POOL_create_advanced(size_t numThreads, size_t queueSize, ZSTD_customMem customMem) {
    (void)numThreads;
    (void)queueSize;
    (void)customMem;
    return &g_ctx;
}