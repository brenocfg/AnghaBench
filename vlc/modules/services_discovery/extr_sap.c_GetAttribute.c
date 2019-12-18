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
struct TYPE_3__ {char const* value; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ attribute_t ;

/* Variables and functions */
 scalar_t__ strcasecmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static const char *GetAttribute (attribute_t **tab, unsigned n,
                                 const char *name)
{
    for (unsigned i = 0; i < n; i++)
        if (strcasecmp (tab[i]->name, name) == 0)
            return tab[i]->value;
    return NULL;
}