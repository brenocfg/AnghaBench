#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* type; } ;
typedef  TYPE_1__ var_t ;
struct TYPE_8__ {int /*<<< orphan*/  attrs; } ;
typedef  TYPE_2__ type_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_CONST ; 
 int FALSE ; 
 int TRUE ; 
 scalar_t__ is_attr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_ptr (TYPE_2__ const*) ; 
 TYPE_2__* type_pointer_get_ref (TYPE_2__ const*) ; 

int is_const_decl(const var_t *var)
{
  const type_t *t;
  /* strangely, MIDL accepts a const attribute on any pointer in the
  * declaration to mean that data isn't being instantiated. this appears
  * to be a bug, but there is no benefit to being incompatible with MIDL,
  * so we'll do the same thing */
  for (t = var->type; ; )
  {
    if (is_attr(t->attrs, ATTR_CONST))
      return TRUE;
    else if (is_ptr(t))
      t = type_pointer_get_ref(t);
    else break;
  }
  return FALSE;
}