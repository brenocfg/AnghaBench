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
struct d3dx_technique {int /*<<< orphan*/  annotation_count; int /*<<< orphan*/  pass_count; int /*<<< orphan*/  name; } ;
struct d3dx9_base_effect {struct d3dx_technique* techniques; } ;
struct TYPE_3__ {int /*<<< orphan*/  Annotations; int /*<<< orphan*/  Passes; int /*<<< orphan*/  Name; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_1__ D3DXTECHNIQUE_DESC ;
typedef  scalar_t__ D3DXHANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  D3DERR_INVALIDCALL ; 
 int /*<<< orphan*/  D3D_OK ; 
 int /*<<< orphan*/  WARN (char*) ; 
 struct d3dx_technique* get_valid_technique (struct d3dx9_base_effect*,scalar_t__) ; 

__attribute__((used)) static HRESULT d3dx9_base_effect_get_technique_desc(struct d3dx9_base_effect *base,
        D3DXHANDLE technique, D3DXTECHNIQUE_DESC *desc)
{
    struct d3dx_technique *tech = technique ? get_valid_technique(base, technique) : &base->techniques[0];

    if (!desc || !tech)
    {
        WARN("Invalid argument specified.\n");
        return D3DERR_INVALIDCALL;
    }

    desc->Name = tech->name;
    desc->Passes = tech->pass_count;
    desc->Annotations = tech->annotation_count;

    return D3D_OK;
}