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
struct d3dx_parameter {int /*<<< orphan*/  flags; } ;
struct d3dx_object {int dummy; } ;
struct d3dx9_base_effect {int dummy; } ;
typedef  scalar_t__ HRESULT ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  D3DX_PARAMETER_ANNOTATION ; 
 scalar_t__ D3D_OK ; 
 int /*<<< orphan*/  TRACE (char*,int) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 scalar_t__ d3dx9_parse_effect_typedef (struct d3dx9_base_effect*,struct d3dx_parameter*,char const*,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ d3dx9_parse_init_value (struct d3dx9_base_effect*,struct d3dx_parameter*,char const*,char const*,struct d3dx_object*) ; 
 int /*<<< orphan*/  read_dword (char const**,int*) ; 

__attribute__((used)) static HRESULT d3dx9_parse_effect_annotation(struct d3dx9_base_effect *base, struct d3dx_parameter *anno,
        const char *data, const char **ptr, struct d3dx_object *objects)
{
    DWORD offset;
    const char *ptr2;
    HRESULT hr;

    anno->flags = D3DX_PARAMETER_ANNOTATION;

    read_dword(ptr, &offset);
    TRACE("Typedef offset: %#x\n", offset);
    ptr2 = data + offset;
    hr = d3dx9_parse_effect_typedef(base, anno, data, &ptr2, NULL, D3DX_PARAMETER_ANNOTATION);
    if (hr != D3D_OK)
    {
        WARN("Failed to parse type definition\n");
        return hr;
    }

    read_dword(ptr, &offset);
    TRACE("Value offset: %#x\n", offset);
    hr = d3dx9_parse_init_value(base, anno, data, data + offset, objects);
    if (hr != D3D_OK)
    {
        WARN("Failed to parse value\n");
        return hr;
    }

    return D3D_OK;
}