#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wined3d_context {size_t* dirtyArray; unsigned int* isStateDirty; int /*<<< orphan*/  numDirtyEntries; TYPE_1__* state_table; } ;
struct TYPE_2__ {size_t representative; } ;
typedef  size_t DWORD ;
typedef  unsigned int BYTE ;

/* Variables and functions */
 int CHAR_BIT ; 
 scalar_t__ isStateDirty (struct wined3d_context*,size_t) ; 

void context_invalidate_state(struct wined3d_context *context, DWORD state)
{
    DWORD rep = context->state_table[state].representative;
    DWORD idx;
    BYTE shift;

    if (isStateDirty(context, rep)) return;

    context->dirtyArray[context->numDirtyEntries++] = rep;
    idx = rep / (sizeof(*context->isStateDirty) * CHAR_BIT);
    shift = rep & ((sizeof(*context->isStateDirty) * CHAR_BIT) - 1);
    context->isStateDirty[idx] |= (1u << shift);
}