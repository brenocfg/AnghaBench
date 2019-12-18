#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char const* name; char const* c_name; } ;
typedef  TYPE_1__ type_t ;
typedef  enum name_type { ____Placeholder_name_type } name_type ;

/* Variables and functions */
#define  NAME_C 129 
#define  NAME_DEFAULT 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

const char *type_get_name(const type_t *type, enum name_type name_type)
{
    switch(name_type) {
    case NAME_DEFAULT:
        return type->name;
    case NAME_C:
        return type->c_name;
    }

    assert(0);
    return NULL;
}