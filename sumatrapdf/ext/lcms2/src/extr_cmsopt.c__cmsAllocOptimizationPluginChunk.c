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
struct _cmsContext_struct {int /*<<< orphan*/  MemPool; int /*<<< orphan*/ * chunks; } ;
struct TYPE_3__ {int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_1__ _cmsOptimizationPluginChunkType ;

/* Variables and functions */
 int /*<<< orphan*/  DupPluginOptimizationList (struct _cmsContext_struct*,struct _cmsContext_struct const*) ; 
 size_t OptimizationPlugin ; 
 int /*<<< orphan*/  _cmsSubAllocDup (int /*<<< orphan*/ ,TYPE_1__*,int) ; 

void  _cmsAllocOptimizationPluginChunk(struct _cmsContext_struct* ctx,
                                         const struct _cmsContext_struct* src)
{
  if (src != NULL) {

        // Copy all linked list
       DupPluginOptimizationList(ctx, src);
    }
    else {
        static _cmsOptimizationPluginChunkType OptimizationPluginChunkType = { NULL };
        ctx ->chunks[OptimizationPlugin] = _cmsSubAllocDup(ctx ->MemPool, &OptimizationPluginChunkType, sizeof(_cmsOptimizationPluginChunkType));
    }
}