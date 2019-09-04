#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  type_t ;
typedef  int /*<<< orphan*/  attr_list_t ;
struct TYPE_2__ {int /*<<< orphan*/ * type; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ FC_CPSTRUCT ; 
 scalar_t__ TYPE_STRUCT ; 
 int /*<<< orphan*/  current_structure ; 
 TYPE_1__* find_array_or_string_in_struct (int /*<<< orphan*/ *) ; 
 scalar_t__ get_struct_fc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_array (int /*<<< orphan*/ *) ; 
 scalar_t__ is_conformant_array (int /*<<< orphan*/ *) ; 
 scalar_t__ type_array_is_decl_as_ptr (int /*<<< orphan*/ *) ; 
 scalar_t__ type_get_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  type_memsize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_conformant_array_pointer_descriptions (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  write_fixed_array_pointer_descriptions (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  write_no_repeat_pointer_descriptions (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  write_varying_array_pointer_descriptions (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int*,unsigned int*,unsigned int*) ; 

__attribute__((used)) static void write_pointer_description(FILE *file, const attr_list_t *attrs, type_t *type,
                                      unsigned int *typestring_offset)
{
    unsigned int offset_in_buffer;
    unsigned int offset_in_memory;

    /* pass 1: search for single instance of a pointer (i.e. don't descend
     * into arrays) */
    if (!is_array(type))
    {
        offset_in_memory = 0;
        offset_in_buffer = 0;
        write_no_repeat_pointer_descriptions(
            file, NULL, type,
            &offset_in_memory, &offset_in_buffer, typestring_offset);
    }

    /* pass 2: search for pointers in fixed arrays */
    offset_in_memory = 0;
    offset_in_buffer = 0;
    write_fixed_array_pointer_descriptions(
        file, NULL, type,
        &offset_in_memory, &offset_in_buffer, typestring_offset);

    /* pass 3: search for pointers in conformant only arrays (but don't descend
     * into conformant varying or varying arrays) */
    if (is_conformant_array(type) &&
        (type_array_is_decl_as_ptr(type) || !current_structure))
        write_conformant_array_pointer_descriptions(
            file, attrs, type, 0, typestring_offset);
    else if (type_get_type(type) == TYPE_STRUCT &&
             get_struct_fc(type) == FC_CPSTRUCT)
    {
        type_t *carray = find_array_or_string_in_struct(type)->type;
        write_conformant_array_pointer_descriptions( file, NULL, carray,
                                                     type_memsize(type), typestring_offset);
    }

    /* pass 4: search for pointers in varying arrays */
    offset_in_memory = 0;
    offset_in_buffer = 0;
    write_varying_array_pointer_descriptions(
            file, NULL, type,
            &offset_in_memory, &offset_in_buffer, typestring_offset);
}