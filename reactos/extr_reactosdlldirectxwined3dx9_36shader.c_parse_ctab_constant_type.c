#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char const* DefaultValue; scalar_t__ Class; int Rows; int Columns; int Elements; int StructMembers; char const* Name; int RegisterSet; int RegisterIndex; int Bytes; scalar_t__ RegisterCount; int /*<<< orphan*/  Type; } ;
struct ctab_constant {struct ctab_constant* constants; TYPE_1__ desc; } ;
typedef  int WORD ;
typedef  int UINT ;
struct TYPE_7__ {int TypeInfo; int Name; } ;
struct TYPE_6__ {scalar_t__ Class; int Rows; int Columns; int Elements; int StructMembers; int StructMemberInfo; int /*<<< orphan*/  Type; } ;
typedef  TYPE_2__* LPD3DXSHADER_TYPEINFO ;
typedef  scalar_t__ HRESULT ;
typedef  int DWORD ;
typedef  TYPE_2__ D3DXSHADER_TYPEINFO ;
typedef  TYPE_4__ D3DXSHADER_STRUCTMEMBERINFO ;
typedef  int BOOL ;

/* Variables and functions */
#define  D3DXPC_MATRIX_COLUMNS 135 
#define  D3DXPC_MATRIX_ROWS 134 
 int D3DXPC_OBJECT ; 
#define  D3DXPC_SCALAR 133 
 scalar_t__ D3DXPC_STRUCT ; 
#define  D3DXPC_VECTOR 132 
#define  D3DXRS_BOOL 131 
#define  D3DXRS_FLOAT4 130 
#define  D3DXRS_INT4 129 
#define  D3DXRS_SAMPLER 128 
 scalar_t__ D3D_OK ; 
 int /*<<< orphan*/  ERR (char*) ; 
 scalar_t__ E_OUTOFMEMORY ; 
 int FALSE ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 struct ctab_constant* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ctab_constant*) ; 
 int /*<<< orphan*/  TRACE (char*,char const*,int,int,...) ; 
 int TRUE ; 
 int /*<<< orphan*/  debug_d3dxparameter_class (scalar_t__) ; 
 int /*<<< orphan*/  debug_d3dxparameter_registerset (int) ; 
 int /*<<< orphan*/  debug_d3dxparameter_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_constant (struct ctab_constant*) ; 
 scalar_t__ max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int,int) ; 

__attribute__((used)) static HRESULT parse_ctab_constant_type(const char *ctab, DWORD typeoffset, struct ctab_constant *constant,
        BOOL is_element, WORD index, WORD max_index, DWORD *offset, DWORD nameoffset, UINT regset)
{
    const D3DXSHADER_TYPEINFO *type = (LPD3DXSHADER_TYPEINFO)(ctab + typeoffset);
    const D3DXSHADER_STRUCTMEMBERINFO *memberinfo = NULL;
    HRESULT hr = D3D_OK;
    UINT i, count = 0;
    WORD size = 0;

    constant->desc.DefaultValue = offset ? ctab + *offset : NULL;
    constant->desc.Class = type->Class;
    constant->desc.Type = type->Type;
    constant->desc.Rows = type->Rows;
    constant->desc.Columns = type->Columns;
    constant->desc.Elements = is_element ? 1 : type->Elements;
    constant->desc.StructMembers = type->StructMembers;
    constant->desc.Name = ctab + nameoffset;
    constant->desc.RegisterSet = regset;
    constant->desc.RegisterIndex = index;

    TRACE("name %s, elements %u, index %u, defaultvalue %p, regset %s\n", constant->desc.Name,
            constant->desc.Elements, index, constant->desc.DefaultValue,
            debug_d3dxparameter_registerset(regset));
    TRACE("class %s, type %s, rows %d, columns %d, elements %d, struct_members %d\n",
            debug_d3dxparameter_class(type->Class), debug_d3dxparameter_type(type->Type),
            type->Rows, type->Columns, type->Elements, type->StructMembers);

    if (type->Elements > 1 && !is_element)
    {
        count = type->Elements;
    }
    else if ((type->Class == D3DXPC_STRUCT) && type->StructMembers)
    {
        memberinfo = (D3DXSHADER_STRUCTMEMBERINFO*)(ctab + type->StructMemberInfo);
        count = type->StructMembers;
    }

    if (count)
    {
        constant->constants = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*constant->constants) * count);
        if (!constant->constants)
        {
             ERR("Out of memory\n");
             hr = E_OUTOFMEMORY;
             goto error;
        }

        for (i = 0; i < count; ++i)
        {
            hr = parse_ctab_constant_type(ctab, memberinfo ? memberinfo[i].TypeInfo : typeoffset,
                    &constant->constants[i], memberinfo == NULL, index + size, max_index, offset,
                    memberinfo ? memberinfo[i].Name : nameoffset, regset);
            if (hr != D3D_OK)
                goto error;

            size += constant->constants[i].desc.RegisterCount;
        }
    }
    else
    {
        WORD offsetdiff = type->Columns * type->Rows;
        BOOL fail = FALSE;

        size = type->Columns * type->Rows;

        switch (regset)
        {
            case D3DXRS_BOOL:
                fail = type->Class != D3DXPC_SCALAR && type->Class != D3DXPC_VECTOR
                        && type->Class != D3DXPC_MATRIX_ROWS && type->Class != D3DXPC_MATRIX_COLUMNS;
                break;

            case D3DXRS_FLOAT4:
            case D3DXRS_INT4:
                switch (type->Class)
                {
                    case D3DXPC_VECTOR:
                        size = 1;
                        /* fall through */
                    case D3DXPC_SCALAR:
                        offsetdiff = type->Rows * 4;
                        break;

                    case D3DXPC_MATRIX_ROWS:
                        offsetdiff = type->Rows * 4;
                        size = type->Rows;
                        break;

                    case D3DXPC_MATRIX_COLUMNS:
                        offsetdiff = type->Columns * 4;
                        size = type->Columns;
                        break;

                    default:
                        fail = TRUE;
                        break;
                }
                break;

            case D3DXRS_SAMPLER:
                size = 1;
                fail = type->Class != D3DXPC_OBJECT;
                break;

            default:
                fail = TRUE;
                break;
        }

        if (fail)
        {
            FIXME("Unhandled register set %s, type class %s\n", debug_d3dxparameter_registerset(regset),
                    debug_d3dxparameter_class(type->Class));
        }

        /* offset in bytes => offsetdiff * sizeof(DWORD) */
        if (offset) *offset += offsetdiff * 4;
    }

    constant->desc.RegisterCount = max(0, min(max_index - index, size));
    constant->desc.Bytes = 4 * constant->desc.Elements * type->Rows * type->Columns;

    return D3D_OK;

error:
    if (constant->constants)
    {
        for (i = 0; i < count; ++i)
        {
            free_constant(&constant->constants[i]);
        }
        HeapFree(GetProcessHeap(), 0, constant->constants);
        constant->constants = NULL;
    }

    return hr;
}