#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  loc_info; int /*<<< orphan*/  details; int /*<<< orphan*/  is_alias; struct TYPE_6__* orig; int /*<<< orphan*/ * attrs; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ type_t ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* duptype (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_loc_info (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

type_t *type_new_alias(type_t *t, const char *name)
{
    type_t *a = duptype(t, 0);

    a->name = xstrdup(name);
    a->attrs = NULL;
    a->orig = t;
    a->is_alias = TRUE;
    /* for pointer types */
    a->details = t->details;
    init_loc_info(&a->loc_info);

    return a;
}