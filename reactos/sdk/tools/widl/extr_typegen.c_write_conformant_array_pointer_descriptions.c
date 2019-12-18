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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FC_FIXED_OFFSET ; 
 int /*<<< orphan*/  FC_VARIABLE_REPEAT ; 
 unsigned int USHRT_MAX ; 
 int /*<<< orphan*/  error (char*,unsigned int) ; 
 scalar_t__ is_conformant_array (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_file (int /*<<< orphan*/ *,int,char*,unsigned short,...) ; 
 int /*<<< orphan*/  type_array_get_element (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  type_array_has_variance (int /*<<< orphan*/ *) ; 
 unsigned int type_memsize (int /*<<< orphan*/ ) ; 
 int write_pointer_description_offsets (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,unsigned int*,unsigned int*,unsigned int*) ; 

__attribute__((used)) static int write_conformant_array_pointer_descriptions(
    FILE *file, const attr_list_t *attrs, type_t *type,
    unsigned int offset_in_memory, unsigned int *typestring_offset)
{
    int pointer_count = 0;

    if (is_conformant_array(type) && !type_array_has_variance(type))
    {
        unsigned int temp = 0;
        /* unfortunately, this needs to be done in two passes to avoid
         * writing out redundant FC_VARIABLE_REPEAT descriptions */
        pointer_count = write_pointer_description_offsets(
            NULL, attrs, type_array_get_element(type), NULL, NULL, &temp);
        if (pointer_count > 0)
        {
            unsigned int increment_size;
            unsigned int offset_of_array_pointer_mem = offset_in_memory;
            unsigned int offset_of_array_pointer_buf = offset_in_memory;

            increment_size = type_memsize(type_array_get_element(type));

            if (increment_size > USHRT_MAX)
                error("array size of %u bytes is too large\n", increment_size);

            print_file(file, 2, "0x%02x, /* FC_VARIABLE_REPEAT */\n", FC_VARIABLE_REPEAT);
            print_file(file, 2, "0x%02x, /* FC_FIXED_OFFSET */\n", FC_FIXED_OFFSET);
            print_file(file, 2, "NdrFcShort(0x%hx),\t/* Increment = %d */\n", (unsigned short)increment_size, increment_size);
            print_file(file, 2, "NdrFcShort(0x%hx),\t/* Offset to array = %d */\n", (unsigned short)offset_in_memory, offset_in_memory);
            print_file(file, 2, "NdrFcShort(0x%hx),\t/* Number of pointers = %d */\n", (unsigned short)pointer_count, pointer_count);
            *typestring_offset += 8;

            pointer_count = write_pointer_description_offsets(
                file, attrs, type_array_get_element(type),
                &offset_of_array_pointer_mem, &offset_of_array_pointer_buf,
                typestring_offset);
        }
    }

    return pointer_count;
}