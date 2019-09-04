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
struct wined3d_sm4_data {int dummy; } ;
struct wined3d_shader_instruction {int flags; } ;
typedef  int DWORD ;

/* Variables and functions */
 int WINED3D_SM4_GLOBAL_FLAGS_MASK ; 
 int WINED3D_SM4_GLOBAL_FLAGS_SHIFT ; 

__attribute__((used)) static void shader_sm4_read_dcl_global_flags(struct wined3d_shader_instruction *ins,
        DWORD opcode, DWORD opcode_token, const DWORD *tokens, unsigned int token_count,
        struct wined3d_sm4_data *priv)
{
    ins->flags = (opcode_token & WINED3D_SM4_GLOBAL_FLAGS_MASK) >> WINED3D_SM4_GLOBAL_FLAGS_SHIFT;
}