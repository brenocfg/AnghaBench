#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  type_t ;
struct expression_type {int /*<<< orphan*/  const* type; } ;
struct expr_loc {int dummy; } ;
typedef  int /*<<< orphan*/  expr_t ;

/* Variables and functions */
 struct expression_type resolve_expression (struct expr_loc const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

const type_t *expr_resolve_type(const struct expr_loc *expr_loc, const type_t *cont_type, const expr_t *expr)
{
    struct expression_type expr_type;
    expr_type = resolve_expression(expr_loc, cont_type, expr);
    return expr_type.type;
}