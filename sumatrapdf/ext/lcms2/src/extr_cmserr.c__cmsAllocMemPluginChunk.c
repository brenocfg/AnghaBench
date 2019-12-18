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
struct _cmsContext_struct {int /*<<< orphan*/  DefaultMemoryManager; int /*<<< orphan*/ ** chunks; int /*<<< orphan*/  MemPool; } ;
typedef  int /*<<< orphan*/  _cmsMemPluginChunkType ;

/* Variables and functions */
 size_t MemPlugin ; 
 int /*<<< orphan*/  _cmsAssert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * _cmsSubAllocDup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

void _cmsAllocMemPluginChunk(struct _cmsContext_struct* ctx, const struct _cmsContext_struct* src)
{
    _cmsAssert(ctx != NULL);

    if (src != NULL) {

        // Duplicate
        ctx ->chunks[MemPlugin] = _cmsSubAllocDup(ctx ->MemPool, src ->chunks[MemPlugin], sizeof(_cmsMemPluginChunkType));
    }
    else {

        // To reset it, we use the default allocators, which cannot be overridden
        ctx ->chunks[MemPlugin] = &ctx ->DefaultMemoryManager;
    }
}