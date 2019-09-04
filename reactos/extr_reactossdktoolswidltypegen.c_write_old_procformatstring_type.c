#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {unsigned short typestring_offset; TYPE_5__* type; int /*<<< orphan*/  attrs; } ;
typedef  TYPE_3__ var_t ;
struct TYPE_11__ {scalar_t__ ptr_tfsoff; } ;
struct TYPE_12__ {TYPE_1__ array; } ;
struct TYPE_14__ {unsigned short typestring_offset; TYPE_2__ details; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_IN ; 
 int /*<<< orphan*/  ATTR_OUT ; 
 unsigned char FC_BIND_PRIMITIVE ; 
 unsigned char FC_IGNORE ; 
 int TRUE ; 
 scalar_t__ TYPE_BASIC ; 
 scalar_t__ TYPE_ENUM ; 
 unsigned char get_basic_fc_signed (TYPE_5__*) ; 
 unsigned char get_enum_fc (TYPE_5__*) ; 
 unsigned int get_stack_size (TYPE_3__ const*,int /*<<< orphan*/ *) ; 
 scalar_t__ is_array (TYPE_5__*) ; 
 int is_attr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int pointer_size ; 
 int /*<<< orphan*/  print_file (int /*<<< orphan*/ *,int,char*,...) ; 
 unsigned short string_of_type (unsigned char) ; 
 scalar_t__ type_array_is_decl_as_ptr (TYPE_5__*) ; 
 scalar_t__ type_get_type (TYPE_5__*) ; 

__attribute__((used)) static unsigned int write_old_procformatstring_type(FILE *file, int indent, const var_t *var,
                                                    int is_return, int is_interpreted)
{
    unsigned int size;

    int is_in = is_attr(var->attrs, ATTR_IN);
    int is_out = is_attr(var->attrs, ATTR_OUT);

    if (!is_in && !is_out) is_in = TRUE;

    if (type_get_type(var->type) == TYPE_BASIC ||
        type_get_type(var->type) == TYPE_ENUM)
    {
        unsigned char fc;

        if (is_return)
            print_file(file, indent, "0x53,    /* FC_RETURN_PARAM_BASETYPE */\n");
        else
            print_file(file, indent, "0x4e,    /* FC_IN_PARAM_BASETYPE */\n");

        if (type_get_type(var->type) == TYPE_ENUM)
        {
            fc = get_enum_fc(var->type);
        }
        else
        {
            fc = get_basic_fc_signed(var->type);

            if (fc == FC_BIND_PRIMITIVE)
                fc = FC_IGNORE;
        }

        print_file(file, indent, "0x%02x,    /* %s */\n",
                   fc, string_of_type(fc));
        size = 2; /* includes param type prefix */
    }
    else
    {
        unsigned short offset = var->typestring_offset;

        if (!is_interpreted && is_array(var->type) &&
            type_array_is_decl_as_ptr(var->type) &&
            var->type->details.array.ptr_tfsoff)
            offset = var->type->typestring_offset;

        if (is_return)
            print_file(file, indent, "0x52,    /* FC_RETURN_PARAM */\n");
        else if (is_in && is_out)
            print_file(file, indent, "0x50,    /* FC_IN_OUT_PARAM */\n");
        else if (is_out)
            print_file(file, indent, "0x51,    /* FC_OUT_PARAM */\n");
        else
            print_file(file, indent, "0x4d,    /* FC_IN_PARAM */\n");

        size = get_stack_size( var, NULL );
        print_file(file, indent, "0x%02x,\n", size / pointer_size );
        print_file(file, indent, "NdrFcShort(0x%x),	/* type offset = %u */\n", offset, offset);
        size = 4; /* includes param type prefix */
    }
    return size;
}