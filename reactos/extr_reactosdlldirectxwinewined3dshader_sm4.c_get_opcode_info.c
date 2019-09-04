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
struct wined3d_sm4_opcode_info {int opcode; } ;
typedef  enum wined3d_sm4_opcode { ____Placeholder_wined3d_sm4_opcode } wined3d_sm4_opcode ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct wined3d_sm4_opcode_info const*) ; 
 struct wined3d_sm4_opcode_info const* opcode_table ; 

__attribute__((used)) static const struct wined3d_sm4_opcode_info *get_opcode_info(enum wined3d_sm4_opcode opcode)
{
    unsigned int i;

    for (i = 0; i < ARRAY_SIZE(opcode_table); ++i)
    {
        if (opcode == opcode_table[i].opcode) return &opcode_table[i];
    }

    return NULL;
}