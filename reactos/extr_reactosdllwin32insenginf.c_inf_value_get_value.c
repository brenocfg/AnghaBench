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
struct inf_value {int /*<<< orphan*/  value; TYPE_1__* section; } ;
struct TYPE_2__ {int /*<<< orphan*/  file; } ;

/* Variables and functions */
 char* expand_variables (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

char *inf_value_get_value(struct inf_value *value)
{
    return expand_variables(value->section->file, value->value);
}