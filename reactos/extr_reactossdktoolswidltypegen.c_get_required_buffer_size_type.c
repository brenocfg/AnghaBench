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
typedef  int /*<<< orphan*/  type_t ;
typedef  int /*<<< orphan*/  attr_list_t ;

/* Variables and functions */
 int FALSE ; 
#define  FC_BIND_PRIMITIVE 154 
#define  FC_BYTE 153 
#define  FC_CHAR 152 
#define  FC_DOUBLE 151 
#define  FC_ENUM16 150 
#define  FC_ENUM32 149 
#define  FC_ERROR_STATUS_T 148 
#define  FC_FLOAT 147 
#define  FC_HYPER 146 
#define  FC_IGNORE 145 
#define  FC_INT3264 144 
#define  FC_LGFARRAY 143 
#define  FC_LONG 142 
 int /*<<< orphan*/  FC_RP ; 
#define  FC_SHORT 141 
#define  FC_SMALL 140 
#define  FC_SMFARRAY 139 
 int /*<<< orphan*/  FC_STRUCT ; 
#define  FC_UINT3264 138 
#define  FC_ULONG 137 
#define  FC_USHORT 136 
#define  FC_USMALL 135 
#define  FC_WCHAR 134 
 int /*<<< orphan*/  TDT_IGNORE_RANGES ; 
#define  TGT_ARRAY 133 
#define  TGT_BASIC 132 
#define  TGT_ENUM 131 
#define  TGT_POINTER 130 
#define  TGT_STRUCT 129 
#define  TGT_USER_TYPE 128 
 int /*<<< orphan*/  assert (unsigned int) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 unsigned int fields_memsize (int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  get_array_fc (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  get_basic_fc (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  get_enum_fc (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  get_pointer_fc (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  get_struct_fc (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * get_user_type (int /*<<< orphan*/  const*,char const**) ; 
 int /*<<< orphan*/  is_string_type (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 unsigned int pointer_size ; 
 unsigned int type_array_get_dim (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * type_array_get_element (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * type_pointer_get_ref (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  type_struct_get_fields (int /*<<< orphan*/  const*) ; 
 int typegen_detect_type (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int get_required_buffer_size_type(
    const type_t *type, const char *name, const attr_list_t *attrs, int toplevel_param, unsigned int *alignment)
{
    *alignment = 0;
    switch (typegen_detect_type(type, NULL, TDT_IGNORE_RANGES))
    {
    case TGT_USER_TYPE:
    {
        const char *uname = NULL;
        const type_t *utype = get_user_type(type, &uname);
        return get_required_buffer_size_type(utype, uname, NULL, FALSE, alignment);
    }
    case TGT_BASIC:
        switch (get_basic_fc(type))
        {
        case FC_BYTE:
        case FC_CHAR:
        case FC_USMALL:
        case FC_SMALL:
            *alignment = 4;
            return 1;

        case FC_WCHAR:
        case FC_USHORT:
        case FC_SHORT:
            *alignment = 4;
            return 2;

        case FC_ULONG:
        case FC_LONG:
        case FC_FLOAT:
        case FC_ERROR_STATUS_T:
            *alignment = 4;
            return 4;

        case FC_HYPER:
        case FC_DOUBLE:
            *alignment = 8;
            return 8;

        case FC_INT3264:
        case FC_UINT3264:
            assert( pointer_size );
            *alignment = pointer_size;
            return pointer_size;

        case FC_IGNORE:
        case FC_BIND_PRIMITIVE:
            return 0;

        default:
            error("get_required_buffer_size: unknown basic type 0x%02x\n",
                  get_basic_fc(type));
            return 0;
        }
        break;

    case TGT_ENUM:
        switch (get_enum_fc(type))
        {
        case FC_ENUM32:
            *alignment = 4;
            return 4;
        case FC_ENUM16:
            *alignment = 4;
            return 2;
        }
        break;

    case TGT_STRUCT:
        if (get_struct_fc(type) == FC_STRUCT)
        {
            if (!type_struct_get_fields(type)) return 0;
            return fields_memsize(type_struct_get_fields(type), alignment);
        }
        break;

    case TGT_POINTER:
        {
            unsigned int size, align;
            const type_t *ref = type_pointer_get_ref(type);
            if (is_string_type( attrs, ref )) break;
            if (!(size = get_required_buffer_size_type( ref, name, NULL, FALSE, &align ))) break;
            if (get_pointer_fc(type, attrs, toplevel_param) != FC_RP)
            {
                size += 4 + align;
                align = 4;
            }
            *alignment = align;
            return size;
        }

    case TGT_ARRAY:
        if (get_pointer_fc(type, attrs, toplevel_param) == FC_RP)
        {
            switch (get_array_fc(type))
            {
            case FC_SMFARRAY:
            case FC_LGFARRAY:
                return type_array_get_dim(type) *
                    get_required_buffer_size_type(type_array_get_element(type), name,
                                                  NULL, FALSE, alignment);
            }
        }
        break;

    default:
        break;
    }
    return 0;
}