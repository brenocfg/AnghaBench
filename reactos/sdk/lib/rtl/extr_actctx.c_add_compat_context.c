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
struct assembly {int num_compat_contexts; int /*<<< orphan*/ * compat_contexts; } ;
typedef  int /*<<< orphan*/ * PCOMPATIBILITY_CONTEXT_ELEMENT ;
typedef  int /*<<< orphan*/  COMPATIBILITY_CONTEXT_ELEMENT ;

/* Variables and functions */
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 void* RtlAllocateHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RtlGetProcessHeap () ; 
 void* RtlReAllocateHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static PCOMPATIBILITY_CONTEXT_ELEMENT add_compat_context(struct assembly* assembly)
{
    void *ptr;
    if (assembly->num_compat_contexts)
    {
        unsigned int new_count = assembly->num_compat_contexts + 1;
        ptr = RtlReAllocateHeap( RtlGetProcessHeap(), HEAP_ZERO_MEMORY,
                                 assembly->compat_contexts,
                                 new_count * sizeof(COMPATIBILITY_CONTEXT_ELEMENT) );
    }
    else
    {
        ptr = RtlAllocateHeap( RtlGetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(COMPATIBILITY_CONTEXT_ELEMENT) );
    }
    if (!ptr) return NULL;
    assembly->compat_contexts = ptr;
    return &assembly->compat_contexts[assembly->num_compat_contexts++];
}