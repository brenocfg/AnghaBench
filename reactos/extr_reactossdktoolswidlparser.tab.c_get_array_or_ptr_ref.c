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

/* Variables and functions */
 scalar_t__ is_array (int /*<<< orphan*/ *) ; 
 scalar_t__ is_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * type_array_get_element (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * type_pointer_get_ref (int /*<<< orphan*/ *) ; 

__attribute__((used)) static type_t *get_array_or_ptr_ref(type_t *type)
{
    if (is_ptr(type))
        return type_pointer_get_ref(type);
    else if (is_array(type))
        return type_array_get_element(type);
    return NULL;
}