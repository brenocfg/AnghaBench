#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  typestring_offset; } ;
typedef  TYPE_1__ type_t ;
typedef  int /*<<< orphan*/  attr_list_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ TYPE_BASIC ; 
 int /*<<< orphan*/  TYPE_CONTEXT_CONTAINER ; 
 scalar_t__ TYPE_ENUM ; 
 int /*<<< orphan*/  is_embedded_complex (TYPE_1__*) ; 
 scalar_t__ is_ptr (TYPE_1__*) ; 
 scalar_t__ is_string_type (int /*<<< orphan*/  const*,TYPE_1__*) ; 
 scalar_t__ processed (TYPE_1__*) ; 
 TYPE_1__* type_array_get_element (TYPE_1__ const*) ; 
 scalar_t__ type_get_type (TYPE_1__*) ; 
 TYPE_1__* type_pointer_get_ref (TYPE_1__*) ; 
 int /*<<< orphan*/  write_member_type (int /*<<< orphan*/ *,TYPE_1__ const*,int,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  write_nonsimple_pointer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 scalar_t__ write_simple_pointer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_string_tfs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int*) ; 

__attribute__((used)) static void write_array_element_type(FILE *file, const attr_list_t *attrs, const type_t *type,
                                     int cont_is_complex, unsigned int *tfsoff)
{
    type_t *elem = type_array_get_element(type);

    if (!is_embedded_complex(elem) && is_ptr(elem))
    {
        type_t *ref = type_pointer_get_ref(elem);

        if (processed(ref))
        {
            write_nonsimple_pointer(file, NULL, elem, TYPE_CONTEXT_CONTAINER,
                                    ref->typestring_offset, tfsoff);
            return;
        }
        if (cont_is_complex && is_string_type(attrs, elem))
        {
            write_string_tfs(file, NULL, elem, TYPE_CONTEXT_CONTAINER, NULL, tfsoff);
            return;
        }
        if (!is_string_type(NULL, elem) &&
            (type_get_type(ref) == TYPE_BASIC || type_get_type(ref) == TYPE_ENUM))
        {
            *tfsoff += write_simple_pointer(file, NULL, elem, TYPE_CONTEXT_CONTAINER);
            return;
        }
    }
    write_member_type(file, type, cont_is_complex, NULL, elem, NULL, tfsoff);
}