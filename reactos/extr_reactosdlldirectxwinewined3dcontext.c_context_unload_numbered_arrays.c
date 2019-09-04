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
struct wined3d_context {scalar_t__ numbered_array_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  context_unload_numbered_array (struct wined3d_context*,unsigned int) ; 
 unsigned int wined3d_bit_scan (scalar_t__*) ; 

__attribute__((used)) static void context_unload_numbered_arrays(struct wined3d_context *context)
{
    unsigned int i;

    while (context->numbered_array_mask)
    {
        i = wined3d_bit_scan(&context->numbered_array_mask);
        context_unload_numbered_array(context, i);
    }
}