#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {unsigned int length; TYPE_1__* values; } ;
struct TYPE_9__ {TYPE_2__ object; } ;
struct TYPE_10__ {scalar_t__ type; TYPE_3__ u; } ;
typedef  TYPE_4__ json_value ;
struct TYPE_7__ {TYPE_4__ const* value; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ json_object ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static inline
const json_value * json_getbyname(const json_value *object, const char *psz_name)
{
    if (object->type != json_object) return NULL;
    for (unsigned int i=0; i < object->u.object.length; i++)
        if (strcmp(object->u.object.values[i].name, psz_name) == 0)
            return object->u.object.values[i].value;
    return NULL;
}