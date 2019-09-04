#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ type_t ;
typedef  enum type_context { ____Placeholder_type_context } type_context ;
typedef  int /*<<< orphan*/  attr_list_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_IN ; 
 int /*<<< orphan*/  ATTR_OUT ; 
 unsigned char FC_ALLOCED_ON_STACK ; 
 unsigned char FC_ENUM16 ; 
 unsigned char FC_RP ; 
 unsigned char FC_SIMPLE_POINTER ; 
 scalar_t__ MODE_Oif ; 
 int TYPE_CONTEXT_TOPLEVELPARAM ; 
 scalar_t__ TYPE_ENUM ; 
 int /*<<< orphan*/  current_func ; 
 int /*<<< orphan*/  current_iface ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 unsigned char get_basic_fc (TYPE_1__ const*) ; 
 unsigned char get_enum_fc (TYPE_1__ const*) ; 
 unsigned char get_pointer_fc_context (TYPE_1__ const*,int /*<<< orphan*/  const*,int) ; 
 scalar_t__ get_stub_mode () ; 
 int is_attr (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_interpreted_func (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_string_type (int /*<<< orphan*/  const*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  print_file (int /*<<< orphan*/ *,int,char*,...) ; 
 int /*<<< orphan*/  string_of_type (unsigned char) ; 
 scalar_t__ type_get_type (TYPE_1__ const*) ; 
 TYPE_1__* type_pointer_get_ref (TYPE_1__ const*) ; 

__attribute__((used)) static unsigned int write_simple_pointer(FILE *file, const attr_list_t *attrs,
                                         const type_t *type, enum type_context context)
{
    unsigned char fc;
    unsigned char pointer_fc;
    const type_t *ref;
    int in_attr = is_attr(attrs, ATTR_IN);
    int out_attr = is_attr(attrs, ATTR_OUT);
    unsigned char flags = FC_SIMPLE_POINTER;

    /* for historical reasons, write_simple_pointer also handled string types,
     * but no longer does. catch bad uses of the function with this check */
    if (is_string_type(attrs, type))
        error("write_simple_pointer: can't handle type %s which is a string type\n", type->name);

    pointer_fc = get_pointer_fc_context(type, attrs, context);

    ref = type_pointer_get_ref(type);
    if (type_get_type(ref) == TYPE_ENUM)
        fc = get_enum_fc(ref);
    else
        fc = get_basic_fc(ref);

    if (!is_interpreted_func(current_iface, current_func))
    {
        if (out_attr && !in_attr && pointer_fc == FC_RP)
            flags |= FC_ALLOCED_ON_STACK;
    }
    else if (get_stub_mode() == MODE_Oif)
    {
        if (context == TYPE_CONTEXT_TOPLEVELPARAM && fc == FC_ENUM16 && pointer_fc == FC_RP)
            flags |= FC_ALLOCED_ON_STACK;
    }

    print_file(file, 2, "0x%02x, 0x%x,\t/* %s %s[simple_pointer] */\n",
               pointer_fc, flags, string_of_type(pointer_fc),
               flags & FC_ALLOCED_ON_STACK ? "[allocated_on_stack] " : "");
    print_file(file, 2, "0x%02x,\t/* %s */\n", fc, string_of_type(fc));
    print_file(file, 2, "0x5c,\t/* FC_PAD */\n");
    return 4;
}