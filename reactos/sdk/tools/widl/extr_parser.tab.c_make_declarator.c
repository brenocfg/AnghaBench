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
typedef  int /*<<< orphan*/  var_t ;
struct TYPE_4__ {int /*<<< orphan*/ * bits; int /*<<< orphan*/ * func_type; int /*<<< orphan*/ * type; int /*<<< orphan*/ * var; } ;
typedef  TYPE_1__ declarator_t ;

/* Variables and functions */
 int /*<<< orphan*/ * make_var (int /*<<< orphan*/ *) ; 
 TYPE_1__* xmalloc (int) ; 

__attribute__((used)) static declarator_t *make_declarator(var_t *var)
{
  declarator_t *d = xmalloc(sizeof(*d));
  d->var = var ? var : make_var(NULL);
  d->type = NULL;
  d->func_type = NULL;
  d->bits = NULL;
  return d;
}