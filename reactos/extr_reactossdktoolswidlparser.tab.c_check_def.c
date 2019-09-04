#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  line_number; int /*<<< orphan*/  input_name; } ;
struct TYPE_5__ {TYPE_1__ loc_info; int /*<<< orphan*/  name; scalar_t__ defined; } ;
typedef  TYPE_2__ type_t ;

/* Variables and functions */
 int /*<<< orphan*/  error_loc (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void check_def(const type_t *t)
{
    if (t->defined)
        error_loc("%s: redefinition error; original definition was at %s:%d\n",
                  t->name, t->loc_info.input_name, t->loc_info.line_number);
}