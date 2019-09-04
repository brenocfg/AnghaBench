#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {unsigned int typestring_offset; } ;
typedef  TYPE_1__ type_t ;
typedef  int /*<<< orphan*/  attr_list_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_SWITCHIS ; 
 unsigned char FC_LONG ; 
 unsigned char FC_POINTER ; 
 scalar_t__ TYPE_UNION ; 
 int /*<<< orphan*/  error (char*,scalar_t__) ; 
 scalar_t__ is_attr (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_conformant_array (TYPE_1__ const*) ; 
 scalar_t__ is_embedded_complex (TYPE_1__ const*) ; 
 scalar_t__ is_ptr (TYPE_1__ const*) ; 
 int /*<<< orphan*/  print_file (int /*<<< orphan*/ *,int,char*,...) ; 
 int /*<<< orphan*/  string_of_type (unsigned char) ; 
 scalar_t__ type_get_type (TYPE_1__ const*) ; 
 int /*<<< orphan*/  write_base_type (int /*<<< orphan*/ *,TYPE_1__ const*,unsigned int*) ; 

__attribute__((used)) static void write_member_type(FILE *file, const type_t *cont,
                              int cont_is_complex, const attr_list_t *attrs,
                              const type_t *type, unsigned int *corroff,
                              unsigned int *tfsoff)
{
    if (is_embedded_complex(type) && !is_conformant_array(type))
    {
        unsigned int absoff;
        short reloff;

        if (type_get_type(type) == TYPE_UNION && is_attr(attrs, ATTR_SWITCHIS))
        {
            absoff = *corroff;
            *corroff += 8;
        }
        else
        {
            absoff = type->typestring_offset;
        }
        reloff = absoff - (*tfsoff + 2);

        print_file(file, 2, "0x4c,\t/* FC_EMBEDDED_COMPLEX */\n");
        /* padding is represented using FC_STRUCTPAD* types, so presumably
         * this is left over in the format for historical purposes in MIDL
         * or rpcrt4. */
        print_file(file, 2, "0x0,\n");
        print_file(file, 2, "NdrFcShort(0x%hx),\t/* Offset= %hd (%u) */\n",
                   reloff, reloff, absoff);
        *tfsoff += 4;
    }
    else if (is_ptr(type) || is_conformant_array(type))
    {
        unsigned char fc = cont_is_complex ? FC_POINTER : FC_LONG;
        print_file(file, 2, "0x%x,\t/* %s */\n", fc, string_of_type(fc));
        *tfsoff += 1;
    }
    else if (!write_base_type(file, type, tfsoff))
        error("Unsupported member type %d\n", type_get_type(type));
}