#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  type_t ;
struct expr_loc {char* attr; TYPE_1__* v; } ;
struct TYPE_2__ {int /*<<< orphan*/  loc_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  error_loc_info (int /*<<< orphan*/ *,char*,char*,char*) ; 
 int /*<<< orphan*/  is_integer_type (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void check_integer_type(const struct expr_loc *expr_loc,
                               const type_t *cont_type, const type_t *type)
{
    if (!cont_type || !is_integer_type(type))
        error_loc_info(&expr_loc->v->loc_info, "integer type required in expression%s%s\n",
                       expr_loc->attr ? " for attribute " : "",
                       expr_loc->attr ? expr_loc->attr : "");
}