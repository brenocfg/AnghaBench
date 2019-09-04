#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
struct TYPE_23__ {unsigned int ptr_tfsoff; } ;
struct TYPE_24__ {TYPE_1__ array; } ;
struct TYPE_25__ {unsigned int typestring_offset; int /*<<< orphan*/  name; TYPE_2__ details; } ;
typedef  TYPE_3__ type_t ;
typedef  int /*<<< orphan*/  expr_list_t ;
typedef  enum type_context { ____Placeholder_type_context } type_context ;
typedef  int /*<<< orphan*/  attr_list_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_RANGE ; 
 int FC_RP ; 
 int /*<<< orphan*/  TDT_ALL_TYPES ; 
#define  TGT_ARRAY 140 
#define  TGT_BASIC 139 
#define  TGT_CTXT_HANDLE 138 
#define  TGT_CTXT_HANDLE_POINTER 137 
#define  TGT_ENUM 136 
#define  TGT_IFACE_POINTER 135 
#define  TGT_INVALID 134 
#define  TGT_POINTER 133 
#define  TGT_RANGE 132 
#define  TGT_STRING 131 
#define  TGT_STRUCT 130 
#define  TGT_UNION 129 
#define  TGT_USER_TYPE 128 
 int TYPE_CONTEXT_CONTAINER ; 
 int TYPE_CONTEXT_CONTAINER_NO_POINTERS ; 
 int TYPE_CONTEXT_PARAM ; 
 int TYPE_CONTEXT_TOPLEVELPARAM ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * get_aliaschain_attrp (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_attrp (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int get_pointer_fc (TYPE_3__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  is_conformant_array (TYPE_3__*) ; 
 int /*<<< orphan*/  is_string_type (int /*<<< orphan*/  const*,TYPE_3__*) ; 
 int /*<<< orphan*/  print_file (int /*<<< orphan*/ *,int,char*,short,...) ; 
 int /*<<< orphan*/  string_of_type (int) ; 
 int /*<<< orphan*/  type_array_is_decl_as_ptr (TYPE_3__*) ; 
 TYPE_3__* type_pointer_get_ref (TYPE_3__*) ; 
 int typegen_detect_type (TYPE_3__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_tfsoff (TYPE_3__*,unsigned int,int /*<<< orphan*/ *) ; 
 unsigned int write_array_tfs (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,TYPE_3__*,char const*,unsigned int*) ; 
 unsigned int write_contexthandle_tfs (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,TYPE_3__*,int,unsigned int*) ; 
 unsigned int write_ip_tfs (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,TYPE_3__*,unsigned int*) ; 
 unsigned int write_pointer_tfs (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,TYPE_3__*,unsigned int,int,unsigned int*) ; 
 unsigned int write_range_tfs (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,TYPE_3__*,int /*<<< orphan*/ *,unsigned int*) ; 
 unsigned int write_string_tfs (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,TYPE_3__*,int,char const*,unsigned int*) ; 
 unsigned int write_struct_tfs (int /*<<< orphan*/ *,TYPE_3__*,char const*,unsigned int*) ; 
 unsigned int write_union_tfs (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,TYPE_3__*,unsigned int*) ; 
 unsigned int write_user_tfs (int /*<<< orphan*/ *,TYPE_3__*,unsigned int*) ; 

__attribute__((used)) static unsigned int write_type_tfs(FILE *file, int indent,
                                   const attr_list_t *attrs, type_t *type,
                                   const char *name,
                                   enum type_context context,
                                   unsigned int *typeformat_offset)
{
    unsigned int offset;

    switch (typegen_detect_type(type, attrs, TDT_ALL_TYPES))
    {
    case TGT_CTXT_HANDLE:
    case TGT_CTXT_HANDLE_POINTER:
        return write_contexthandle_tfs(file, attrs, type,
                                       context == TYPE_CONTEXT_TOPLEVELPARAM, typeformat_offset);
    case TGT_USER_TYPE:
        return write_user_tfs(file, type, typeformat_offset);
    case TGT_STRING:
        return write_string_tfs(file, attrs, type, context, name, typeformat_offset);
    case TGT_ARRAY:
    {
        unsigned int off;
        /* conformant and pointer arrays are handled specially */
        if ((context != TYPE_CONTEXT_CONTAINER &&
             context != TYPE_CONTEXT_CONTAINER_NO_POINTERS) ||
            !is_conformant_array(type) || type_array_is_decl_as_ptr(type))
            off = write_array_tfs(file, attrs, type, name, typeformat_offset);
        else
            off = 0;
        if (context != TYPE_CONTEXT_CONTAINER &&
            context != TYPE_CONTEXT_CONTAINER_NO_POINTERS)
        {
            int ptr_type;
            ptr_type = get_pointer_fc(type, attrs,
                                      context == TYPE_CONTEXT_TOPLEVELPARAM);
            if (ptr_type != FC_RP || type_array_is_decl_as_ptr(type))
            {
                unsigned int absoff = type->typestring_offset;
                short reloff = absoff - (*typeformat_offset + 2);
                off = *typeformat_offset;
                print_file(file, 0, "/* %d */\n", off);
                print_file(file, 2, "0x%x, 0x0,\t/* %s */\n", ptr_type,
                           string_of_type(ptr_type));
                print_file(file, 2, "NdrFcShort(0x%hx),\t/* Offset= %hd (%u) */\n",
                           reloff, reloff, absoff);
                if (ptr_type != FC_RP) update_tfsoff( type, off, file );
                *typeformat_offset += 4;
            }
            type->details.array.ptr_tfsoff = off;
        }
        return off;
    }
    case TGT_STRUCT:
        return write_struct_tfs(file, type, name, typeformat_offset);
    case TGT_UNION:
        return write_union_tfs(file, attrs, type, typeformat_offset);
    case TGT_ENUM:
    case TGT_BASIC:
        /* nothing to do */
        return 0;
    case TGT_RANGE:
    {
        expr_list_t *range_list = get_attrp(attrs, ATTR_RANGE);
        if (!range_list)
            range_list = get_aliaschain_attrp(type, ATTR_RANGE);
        return write_range_tfs(file, attrs, type, range_list, typeformat_offset);
    }
    case TGT_IFACE_POINTER:
        return write_ip_tfs(file, attrs, type, typeformat_offset);
    case TGT_POINTER:
    {
        enum type_context ref_context;
        type_t *ref = type_pointer_get_ref(type);

        if (context == TYPE_CONTEXT_TOPLEVELPARAM)
            ref_context = TYPE_CONTEXT_PARAM;
        else if (context == TYPE_CONTEXT_CONTAINER_NO_POINTERS)
            ref_context = TYPE_CONTEXT_CONTAINER;
        else
            ref_context = context;

        if (is_string_type(attrs, ref))
        {
            if (context != TYPE_CONTEXT_CONTAINER_NO_POINTERS)
                write_pointer_tfs(file, attrs, type, *typeformat_offset + 4, context, typeformat_offset);

            offset = write_type_tfs(file, indent, attrs, ref, name, ref_context, typeformat_offset);
            if (context == TYPE_CONTEXT_CONTAINER_NO_POINTERS)
                return 0;
            return offset;
        }

        offset = write_type_tfs( file, indent, attrs, type_pointer_get_ref(type), name,
                                 ref_context, typeformat_offset);
        if (context == TYPE_CONTEXT_CONTAINER_NO_POINTERS)
            return 0;
        return write_pointer_tfs(file, attrs, type, offset, context, typeformat_offset);
    }
    case TGT_INVALID:
        break;
    }
    error("invalid type %s for var %s\n", type->name, name);
    return 0;
}