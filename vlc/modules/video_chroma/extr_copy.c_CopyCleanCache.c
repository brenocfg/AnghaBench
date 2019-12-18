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
struct TYPE_3__ {scalar_t__ size; int /*<<< orphan*/ * buffer; } ;
typedef  TYPE_1__ copy_cache_t ;

/* Variables and functions */
 int /*<<< orphan*/  aligned_free (int /*<<< orphan*/ *) ; 

void CopyCleanCache(copy_cache_t *cache)
{
#ifdef CAN_COMPILE_SSE2
    aligned_free(cache->buffer);
    cache->buffer = NULL;
    cache->size   = 0;
#else
    (void) cache;
#endif
}