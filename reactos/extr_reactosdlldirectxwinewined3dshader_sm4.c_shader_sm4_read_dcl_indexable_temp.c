#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wined3d_sm4_data {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  component_count; int /*<<< orphan*/  register_size; int /*<<< orphan*/  register_idx; } ;
struct TYPE_4__ {TYPE_1__ indexable_temp; } ;
struct wined3d_shader_instruction {TYPE_2__ declaration; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */

__attribute__((used)) static void shader_sm4_read_dcl_indexable_temp(struct wined3d_shader_instruction *ins,
        DWORD opcode, DWORD opcode_token, const DWORD *tokens, unsigned int token_count,
        struct wined3d_sm4_data *priv)
{
    ins->declaration.indexable_temp.register_idx = *tokens++;
    ins->declaration.indexable_temp.register_size = *tokens++;
    ins->declaration.indexable_temp.component_count = *tokens;
}