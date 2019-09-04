#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int type_type; int ignore; int typelib_idx; int /*<<< orphan*/  loc_info; void* is_alias; void* checked; void* tfswrite; void* user_types_registered; void* written; void* defined; scalar_t__ ptrdesc; scalar_t__ typestring_offset; int /*<<< orphan*/  details; int /*<<< orphan*/ * orig; int /*<<< orphan*/ * c_name; int /*<<< orphan*/ * attrs; int /*<<< orphan*/ * namespace; int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ type_t ;
typedef  enum type_type { ____Placeholder_type_type } type_type ;

/* Variables and functions */
 void* FALSE ; 
 TYPE_1__* alloc_type () ; 
 int /*<<< orphan*/  init_loc_info (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ parse_only ; 

type_t *make_type(enum type_type type)
{
    type_t *t = alloc_type();
    t->name = NULL;
    t->namespace = NULL;
    t->type_type = type;
    t->attrs = NULL;
    t->c_name = NULL;
    t->orig = NULL;
    memset(&t->details, 0, sizeof(t->details));
    t->typestring_offset = 0;
    t->ptrdesc = 0;
    t->ignore = (parse_only != 0);
    t->defined = FALSE;
    t->written = FALSE;
    t->user_types_registered = FALSE;
    t->tfswrite = FALSE;
    t->checked = FALSE;
    t->is_alias = FALSE;
    t->typelib_idx = -1;
    init_loc_info(&t->loc_info);
    return t;
}