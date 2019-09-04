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
struct TYPE_5__ {char* name; int /*<<< orphan*/  loc_info; int /*<<< orphan*/  stgclass; int /*<<< orphan*/  eval; int /*<<< orphan*/  attrs; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ var_t ;
typedef  int /*<<< orphan*/  map_attrs_filter_t ;

/* Variables and functions */
 int /*<<< orphan*/  map_attrs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* xmalloc (int) ; 

__attribute__((used)) static var_t *copy_var(var_t *src, char *name, map_attrs_filter_t attr_filter)
{
  var_t *v = xmalloc(sizeof(var_t));
  v->name = name;
  v->type = src->type;
  v->attrs = map_attrs(src->attrs, attr_filter);
  v->eval = src->eval;
  v->stgclass = src->stgclass;
  v->loc_info = src->loc_info;
  return v;
}