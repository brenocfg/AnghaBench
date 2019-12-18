#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  line_number; int /*<<< orphan*/  input_name; } ;
struct TYPE_6__ {scalar_t__ type_type; char* name; TYPE_1__ loc_info; scalar_t__ defined; } ;
typedef  TYPE_2__ type_t ;

/* Variables and functions */
 scalar_t__ TYPE_COCLASS ; 
 int /*<<< orphan*/  error_loc (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* get_type (scalar_t__,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

type_t *type_new_coclass(char *name)
{
    type_t *type = get_type(TYPE_COCLASS, name, NULL, 0);
    if (type->type_type != TYPE_COCLASS || type->defined)
        error_loc("%s: redefinition error; original definition was at %s:%d\n",
                  type->name, type->loc_info.input_name, type->loc_info.line_number);
    type->name = name;
    return type;
}