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
struct TYPE_3__ {int /*<<< orphan*/  buffer; int /*<<< orphan*/  size; } ;
typedef  TYPE_1__ copy_cache_t ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  __MAX (unsigned int,int) ; 
 int /*<<< orphan*/  aligned_alloc (int,int /*<<< orphan*/ ) ; 

int CopyInitCache(copy_cache_t *cache, unsigned width)
{
#ifdef CAN_COMPILE_SSE2
    cache->size = __MAX((width + 0x3f) & ~ 0x3f, 16384);
    cache->buffer = aligned_alloc(64, cache->size);
    if (!cache->buffer)
        return VLC_EGENERIC;
#else
    (void) cache; (void) width;
#endif
    return VLC_SUCCESS;
}