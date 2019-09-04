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
struct d3dx_parameter {scalar_t__ type; scalar_t__ class; unsigned int columns; unsigned int rows; scalar_t__ element_count; int /*<<< orphan*/  name; int /*<<< orphan*/ * data; } ;
struct d3dx_const_tab {int const_set_count; struct d3dx_const_param_eval_output* const_set; } ;
struct d3dx_const_param_eval_output {int table; int register_index; int register_count; int element_count; scalar_t__ direct_copy; struct d3dx_parameter* param; } ;
typedef  enum pres_reg_tables { ____Placeholder_pres_reg_tables } pres_reg_tables ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  D3DERR_INVALIDCALL ; 
 scalar_t__ D3DXPC_STRUCT ; 
 scalar_t__ D3DXPT_VOID ; 
 int /*<<< orphan*/  D3D_OK ; 
 scalar_t__ PRES_VT_COUNT ; 
 int /*<<< orphan*/  TRACE (char*,unsigned int,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  debugstr_a (int /*<<< orphan*/ ) ; 
 unsigned int get_offset_reg (int,int) ; 
 int get_reg_offset (int,unsigned int) ; 
 int /*<<< orphan*/  memmove (struct d3dx_const_param_eval_output*,struct d3dx_const_param_eval_output*,int) ; 
 scalar_t__ table_type_from_param_type (scalar_t__) ; 

__attribute__((used)) static HRESULT merge_const_set_entries(struct d3dx_const_tab *const_tab,
        struct d3dx_parameter *param, unsigned int index)
{
    unsigned int i, start_index = index;
    DWORD *current_data;
    enum pres_reg_tables current_table;
    unsigned int current_start_offset, element_count;
    struct d3dx_const_param_eval_output *first_const;

    if (!const_tab->const_set_count)
        return D3D_OK;

    while (index < const_tab->const_set_count - 1)
    {
        first_const = &const_tab->const_set[index];
        current_data = first_const->param->data;
        current_table = first_const->table;
        current_start_offset = get_offset_reg(current_table, first_const->register_index);
        element_count = 0;
        for (i = index; i < const_tab->const_set_count; ++i)
        {
            struct d3dx_const_param_eval_output *const_set = &const_tab->const_set[i];
            unsigned int count = get_offset_reg(const_set->table,
                    const_set->register_count * const_set->element_count);
            unsigned int start_offset = get_offset_reg(const_set->table, const_set->register_index);

            if (!(const_set->table == current_table && current_start_offset == start_offset
                    && const_set->direct_copy == first_const->direct_copy
                    && current_data == const_set->param->data
                    && (const_set->direct_copy || (first_const->param->type == const_set->param->type
                    && first_const->param->class == const_set->param->class
                    && first_const->param->columns == const_set->param->columns
                    && first_const->param->rows == const_set->param->rows
                    && first_const->register_count == const_set->register_count
                    && (i == const_tab->const_set_count - 1
                    || first_const->param->element_count == const_set->param->element_count)))))
                break;

            current_start_offset += count;
            current_data += const_set->direct_copy ? count : const_set->param->rows
                    * const_set->param->columns * const_set->element_count;
            element_count += const_set->element_count;
        }

        if (i > index + 1)
        {
            TRACE("Merging %u child parameters for %s, not merging %u, direct_copy %#x.\n", i - index,
                    debugstr_a(param->name), const_tab->const_set_count - i, first_const->direct_copy);

            first_const->element_count = element_count;
            if (first_const->direct_copy)
            {
                first_const->element_count = 1;
                if (index == start_index
                        && !(param->type == D3DXPT_VOID && param->class == D3DXPC_STRUCT))
                {
                    if (table_type_from_param_type(param->type) == PRES_VT_COUNT)
                        return D3DERR_INVALIDCALL;
                    first_const->param = param;
                }
                first_const->register_count = get_reg_offset(current_table, current_start_offset)
                        - first_const->register_index;
            }
            memmove(&const_tab->const_set[index + 1], &const_tab->const_set[i],
                    sizeof(*const_tab->const_set) * (const_tab->const_set_count - i));
            const_tab->const_set_count -= i - index - 1;
        }
        else
        {
            TRACE("Not merging %u child parameters for %s, direct_copy %#x.\n",
                    const_tab->const_set_count - i, debugstr_a(param->name), first_const->direct_copy);
        }
        index = i;
    }
    return D3D_OK;
}