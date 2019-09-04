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
struct wined3d_sm1_opcode_info {unsigned int param_count; } ;
struct TYPE_2__ {int major; } ;
struct wined3d_sm1_data {TYPE_1__ shader_version; } ;
typedef  unsigned int DWORD ;

/* Variables and functions */
 unsigned int WINED3D_SM1_INSTRUCTION_LENGTH_MASK ; 
 unsigned int WINED3D_SM1_INSTRUCTION_LENGTH_SHIFT ; 

__attribute__((used)) static unsigned int shader_skip_opcode(const struct wined3d_sm1_data *priv,
        const struct wined3d_sm1_opcode_info *opcode_info, DWORD opcode_token)
{
    unsigned int length;
    /* Shaders >= 2.0 may contain address tokens, but fortunately they
     * have a useful length mask - use it here. Shaders 1.0 contain no such tokens */
    length = (opcode_token & WINED3D_SM1_INSTRUCTION_LENGTH_MASK) >> WINED3D_SM1_INSTRUCTION_LENGTH_SHIFT;
    return (priv->shader_version.major >= 2) ? length : opcode_info->param_count;
}