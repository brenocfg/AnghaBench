#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int flags; } ;
struct d3dx_top_level_parameter {int annotation_count; int /*<<< orphan*/ * annotations; TYPE_1__ param; } ;
struct d3dx_object {int dummy; } ;
struct d3dx9_base_effect {int dummy; } ;
typedef  scalar_t__ HRESULT ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ D3D_OK ; 
 int /*<<< orphan*/  ERR (char*) ; 
 scalar_t__ E_OUTOFMEMORY ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,int) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 scalar_t__ d3dx9_parse_effect_annotation (struct d3dx9_base_effect*,int /*<<< orphan*/ *,char const*,char const**,struct d3dx_object*) ; 
 scalar_t__ d3dx9_parse_effect_typedef (struct d3dx9_base_effect*,TYPE_1__*,char const*,char const**,int /*<<< orphan*/ *,int) ; 
 scalar_t__ d3dx9_parse_init_value (struct d3dx9_base_effect*,TYPE_1__*,char const*,char const*,struct d3dx_object*) ; 
 int /*<<< orphan*/  free_parameter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  param_set_magic_number (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_dword (char const**,int*) ; 

__attribute__((used)) static HRESULT d3dx9_parse_effect_parameter(struct d3dx9_base_effect *base, struct d3dx_top_level_parameter *param,
        const char *data, const char **ptr, struct d3dx_object *objects)
{
    DWORD offset;
    HRESULT hr;
    unsigned int i;
    const char *ptr2;

    read_dword(ptr, &offset);
    TRACE("Typedef offset: %#x.\n", offset);
    ptr2 = data + offset;

    read_dword(ptr, &offset);
    TRACE("Value offset: %#x.\n", offset);

    read_dword(ptr, &param->param.flags);
    TRACE("Flags: %#x.\n", param->param.flags);

    read_dword(ptr, &param->annotation_count);
    TRACE("Annotation count: %u.\n", param->annotation_count);

    hr = d3dx9_parse_effect_typedef(base, &param->param, data, &ptr2, NULL, param->param.flags);
    if (hr != D3D_OK)
    {
        WARN("Failed to parse type definition.\n");
        return hr;
    }

    hr = d3dx9_parse_init_value(base, &param->param, data, data + offset, objects);
    if (hr != D3D_OK)
    {
        WARN("Failed to parse value.\n");
        return hr;
    }

    if (param->annotation_count)
    {
        param->annotations = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,
                sizeof(*param->annotations) * param->annotation_count);
        if (!param->annotations)
        {
            ERR("Out of memory.\n");
            hr = E_OUTOFMEMORY;
            goto err_out;
        }

        for (i = 0; i < param->annotation_count; ++i)
        {
            param_set_magic_number(&param->annotations[i]);
            hr = d3dx9_parse_effect_annotation(base, &param->annotations[i], data, ptr, objects);
            if (hr != D3D_OK)
            {
                WARN("Failed to parse annotation.\n");
                goto err_out;
            }
        }
    }

    return D3D_OK;

err_out:

    if (param->annotations)
    {
        for (i = 0; i < param->annotation_count; ++i)
            free_parameter(&param->annotations[i], FALSE, FALSE);
        HeapFree(GetProcessHeap(), 0, param->annotations);
        param->annotations = NULL;
    }

    return hr;
}