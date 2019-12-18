#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ i_shortcuts; int /*<<< orphan*/ * pp_shortcuts; } ;
typedef  TYPE_1__ module_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_list_free (TYPE_1__**) ; 
 TYPE_1__** module_list_get (size_t*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ unlikely (int) ; 

module_t *module_find (const char *name)
{
    size_t count;
    module_t **list = module_list_get (&count);

    assert (name != NULL);

    for (size_t i = 0; i < count; i++)
    {
        module_t *module = list[i];

        if (unlikely(module->i_shortcuts == 0))
            continue;
        if (!strcmp (module->pp_shortcuts[0], name))
        {
            module_list_free (list);
            return module;
        }
    }
    module_list_free (list);
    return NULL;
}