#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct assembly {int type; } ;
typedef  enum assembly_type { ____Placeholder_assembly_type } assembly_type ;
struct TYPE_4__ {int num_assemblies; int allocated_assemblies; struct assembly* assemblies; } ;
typedef  TYPE_1__ ACTIVATION_CONTEXT ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 void* RtlAllocateHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  RtlGetProcessHeap () ; 
 void* RtlReAllocateHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct assembly*,unsigned int) ; 

__attribute__((used)) static struct assembly *add_assembly(ACTIVATION_CONTEXT *actctx, enum assembly_type at)
{
    struct assembly *assembly;

    DPRINT("add_assembly() actctx %p, activeframe ??\n", actctx);

    if (actctx->num_assemblies == actctx->allocated_assemblies)
    {
        void *ptr;
        unsigned int new_count;
        if (actctx->assemblies)
        {
            new_count = actctx->allocated_assemblies * 2;
            ptr = RtlReAllocateHeap( RtlGetProcessHeap(), HEAP_ZERO_MEMORY,
                                     actctx->assemblies, new_count * sizeof(*assembly) );
        }
        else
        {
            new_count = 4;
            ptr = RtlAllocateHeap( RtlGetProcessHeap(), HEAP_ZERO_MEMORY, new_count * sizeof(*assembly) );
        }
        if (!ptr) return NULL;
        actctx->assemblies = ptr;
        actctx->allocated_assemblies = new_count;
    }

    assembly = &actctx->assemblies[actctx->num_assemblies++];
    assembly->type = at;
    return assembly;
}