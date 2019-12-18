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
typedef  int /*<<< orphan*/  type_t ;
struct TYPE_4__ {scalar_t__ type; } ;
typedef  TYPE_1__ expr_t ;

/* Variables and functions */
 scalar_t__ EXPR_VOID ; 
 int /*<<< orphan*/  error (char*,char const*) ; 
 scalar_t__ is_array (int /*<<< orphan*/  const*) ; 
 TYPE_1__* type_array_get_conformance (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * type_array_get_element (int /*<<< orphan*/  const*) ; 
 scalar_t__ type_array_has_conformance (int /*<<< orphan*/  const*) ; 

expr_t *get_size_is_expr(const type_t *t, const char *name)
{
    expr_t *x = NULL;

    for ( ; is_array(t); t = type_array_get_element(t))
        if (type_array_has_conformance(t) &&
            type_array_get_conformance(t)->type != EXPR_VOID)
        {
            if (!x)
                x = type_array_get_conformance(t);
            else
                error("%s: multidimensional conformant"
                      " arrays not supported at the top level\n",
                      name);
        }

    return x;
}