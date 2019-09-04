#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct d3dx_parameter {int /*<<< orphan*/  bytes; int /*<<< orphan*/  flags; int /*<<< orphan*/  member_count; int /*<<< orphan*/  element_count; int /*<<< orphan*/  columns; int /*<<< orphan*/  rows; int /*<<< orphan*/  type; int /*<<< orphan*/  class; int /*<<< orphan*/  semantic; int /*<<< orphan*/  name; } ;
struct d3dx9_base_effect {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  annotation_count; } ;
struct TYPE_4__ {int /*<<< orphan*/  Bytes; int /*<<< orphan*/  Flags; int /*<<< orphan*/  StructMembers; int /*<<< orphan*/  Annotations; int /*<<< orphan*/  Elements; int /*<<< orphan*/  Columns; int /*<<< orphan*/  Rows; int /*<<< orphan*/  Type; int /*<<< orphan*/  Class; int /*<<< orphan*/  Semantic; int /*<<< orphan*/  Name; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_1__ D3DXPARAMETER_DESC ;
typedef  int /*<<< orphan*/  D3DXHANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  D3DERR_INVALIDCALL ; 
 int /*<<< orphan*/  D3D_OK ; 
 int /*<<< orphan*/  WARN (char*) ; 
 struct d3dx_parameter* get_valid_parameter (struct d3dx9_base_effect*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_top_level_parameter (struct d3dx_parameter*) ; 
 TYPE_2__* top_level_parameter_from_parameter (struct d3dx_parameter*) ; 

__attribute__((used)) static HRESULT d3dx9_base_effect_get_parameter_desc(struct d3dx9_base_effect *base,
        D3DXHANDLE parameter, D3DXPARAMETER_DESC *desc)
{
    struct d3dx_parameter *param = get_valid_parameter(base, parameter);

    if (!desc || !param)
    {
        WARN("Invalid argument specified.\n");
        return D3DERR_INVALIDCALL;
    }

    desc->Name = param->name;
    desc->Semantic = param->semantic;
    desc->Class = param->class;
    desc->Type = param->type;
    desc->Rows = param->rows;
    desc->Columns = param->columns;
    desc->Elements = param->element_count;
    desc->Annotations = is_top_level_parameter(param)
            ? top_level_parameter_from_parameter(param)->annotation_count : 0;
    desc->StructMembers = param->member_count;
    desc->Flags = param->flags;
    desc->Bytes = param->bytes;

    return D3D_OK;
}