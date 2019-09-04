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
struct d3dx_const_tab {int const_set_count; int const_set_size; struct d3dx_const_param_eval_output* const_set; } ;
struct d3dx_const_param_eval_output {int dummy; } ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  D3D_OK ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 struct d3dx_const_param_eval_output* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct d3dx_const_param_eval_output* HeapReAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct d3dx_const_param_eval_output*,int) ; 
 unsigned int INITIAL_CONST_SET_SIZE ; 

__attribute__((used)) static HRESULT append_const_set(struct d3dx_const_tab *const_tab, struct d3dx_const_param_eval_output *set)
{
    if (const_tab->const_set_count >= const_tab->const_set_size)
    {
        unsigned int new_size;
        struct d3dx_const_param_eval_output *new_alloc;

        if (!const_tab->const_set_size)
        {
            new_size = INITIAL_CONST_SET_SIZE;
            new_alloc = HeapAlloc(GetProcessHeap(), 0, sizeof(*const_tab->const_set) * new_size);
            if (!new_alloc)
            {
                ERR("Out of memory.\n");
                return E_OUTOFMEMORY;
            }
        }
        else
        {
            new_size = const_tab->const_set_size * 2;
            new_alloc = HeapReAlloc(GetProcessHeap(), 0, const_tab->const_set,
                    sizeof(*const_tab->const_set) * new_size);
            if (!new_alloc)
            {
                ERR("Out of memory.\n");
                return E_OUTOFMEMORY;
            }
        }
        const_tab->const_set = new_alloc;
        const_tab->const_set_size = new_size;
    }
    const_tab->const_set[const_tab->const_set_count++] = *set;
    return D3D_OK;
}