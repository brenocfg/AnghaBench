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
struct TYPE_4__ {int array_size; int table_count; int /*<<< orphan*/  body_count; int /*<<< orphan*/  index; } ;
struct TYPE_3__ {TYPE_2__ fp; } ;
struct wined3d_shader_instruction {TYPE_1__ declaration; } ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int const WINED3D_SM5_FP_ARRAY_SIZE_SHIFT ; 
 int WINED3D_SM5_FP_TABLE_COUNT_MASK ; 

__attribute__((used)) static void shader_sm5_read_dcl_interface(struct wined3d_shader_instruction *ins,
        DWORD opcode, DWORD opcode_token, const DWORD *tokens, unsigned int token_count,
        struct wined3d_sm4_data *priv)
{
    ins->declaration.fp.index = *tokens++;
    ins->declaration.fp.body_count = *tokens++;
    ins->declaration.fp.array_size = *tokens >> WINED3D_SM5_FP_ARRAY_SIZE_SHIFT;
    ins->declaration.fp.table_count = *tokens++ & WINED3D_SM5_FP_TABLE_COUNT_MASK;
    FIXME("Ignoring set of function tables (count %u).\n", ins->declaration.fp.table_count);
}