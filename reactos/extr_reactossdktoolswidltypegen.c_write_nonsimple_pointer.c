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
typedef  enum type_context { ____Placeholder_type_context } type_context ;
typedef  int /*<<< orphan*/  attr_list_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_IN ; 
 int /*<<< orphan*/  ATTR_OUT ; 
 unsigned char FC_ALLOCED_ON_STACK ; 
 unsigned char FC_POINTER_DEREF ; 
 int FC_RP ; 
 scalar_t__ MODE_Oif ; 
 int /*<<< orphan*/  TDT_ALL_TYPES ; 
#define  TGT_CTXT_HANDLE 132 
#define  TGT_CTXT_HANDLE_POINTER 131 
#define  TGT_IFACE_POINTER 130 
#define  TGT_POINTER 129 
#define  TGT_STRING 128 
 int TYPE_CONTEXT_TOPLEVELPARAM ; 
 int /*<<< orphan*/  current_func ; 
 int /*<<< orphan*/  current_iface ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 int get_pointer_fc_context (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 
 scalar_t__ get_stub_mode () ; 
 int is_attr (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_declptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_interpreted_func (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_ptr (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  is_user_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_file (int /*<<< orphan*/ *,int,char*,short,short,unsigned int) ; 
 unsigned int string_of_type (int) ; 
 int /*<<< orphan*/ * type_pointer_get_ref (int /*<<< orphan*/  const*) ; 
 int typegen_detect_type (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int write_nonsimple_pointer(FILE *file, const attr_list_t *attrs,
                                            const type_t *type,
                                            enum type_context context,
                                            unsigned int offset,
                                            unsigned int *typeformat_offset)
{
    unsigned int start_offset = *typeformat_offset;
    short reloff = offset - (*typeformat_offset + 2);
    int in_attr, out_attr;
    int pointer_type;
    unsigned char flags = 0;

    pointer_type = get_pointer_fc_context(type, attrs, context);

    in_attr = is_attr(attrs, ATTR_IN);
    out_attr = is_attr(attrs, ATTR_OUT);
    if (!in_attr && !out_attr) in_attr = 1;

    if (!is_interpreted_func(current_iface, current_func))
    {
        if (out_attr && !in_attr && pointer_type == FC_RP)
            flags |= FC_ALLOCED_ON_STACK;
    }
    else if (get_stub_mode() == MODE_Oif)
    {
        if (context == TYPE_CONTEXT_TOPLEVELPARAM && is_ptr(type) && pointer_type == FC_RP)
        {
            switch (typegen_detect_type(type_pointer_get_ref(type), NULL, TDT_ALL_TYPES))
            {
            case TGT_STRING:
            case TGT_POINTER:
            case TGT_CTXT_HANDLE:
            case TGT_CTXT_HANDLE_POINTER:
                flags |= FC_ALLOCED_ON_STACK;
                break;
            case TGT_IFACE_POINTER:
                if (in_attr && out_attr)
                    flags |= FC_ALLOCED_ON_STACK;
                break;
            default:
                break;
            }
        }
    }

    if (is_ptr(type))
    {
        type_t *ref = type_pointer_get_ref(type);
        if(is_declptr(ref) && !is_user_type(ref))
            flags |= FC_POINTER_DEREF;
    }

    print_file(file, 2, "0x%x, 0x%x,\t\t/* %s",
               pointer_type,
               flags,
               string_of_type(pointer_type));
    if (file)
    {
        if (flags & FC_ALLOCED_ON_STACK)
            fprintf(file, " [allocated_on_stack]");
        if (flags & FC_POINTER_DEREF)
            fprintf(file, " [pointer_deref]");
        fprintf(file, " */\n");
    }

    print_file(file, 2, "NdrFcShort(0x%hx),\t/* Offset= %hd (%u) */\n", reloff, reloff, offset);
    *typeformat_offset += 4;

    return start_offset;
}