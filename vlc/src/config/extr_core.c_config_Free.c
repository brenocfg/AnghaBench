#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_3__* psz; } ;
struct TYPE_6__ {TYPE_3__* psz; } ;
struct TYPE_8__ {struct TYPE_8__* list_text; TYPE_2__ list; scalar_t__ list_count; TYPE_1__ value; int /*<<< orphan*/  i_type; } ;
typedef  TYPE_3__ module_config_t ;

/* Variables and functions */
 scalar_t__ IsConfigStringType (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 

void config_Free (module_config_t *tab, size_t confsize)
{
    for (size_t j = 0; j < confsize; j++)
    {
        module_config_t *p_item = &tab[j];

        if (IsConfigStringType (p_item->i_type))
        {
            free (p_item->value.psz);
            if (p_item->list_count)
                free (p_item->list.psz);
        }

        free (p_item->list_text);
    }

    free (tab);
}