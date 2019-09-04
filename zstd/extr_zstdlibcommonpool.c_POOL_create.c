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
typedef  int /*<<< orphan*/  POOL_ctx ;

/* Variables and functions */
 int /*<<< orphan*/ * POOL_create_advanced (size_t,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_defaultCMem ; 

POOL_ctx* POOL_create(size_t numThreads, size_t queueSize) {
    return POOL_create_advanced(numThreads, queueSize, ZSTD_defaultCMem);
}