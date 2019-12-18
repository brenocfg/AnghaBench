#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned int line; unsigned int column; TYPE_1__* source; } ;
struct TYPE_6__ {char* name; } ;
typedef  TYPE_2__ JsonVariant ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  assert_return (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ json_variant_is_regular (TYPE_2__*) ; 

int json_variant_get_source(JsonVariant *v, const char **ret_source, unsigned *ret_line, unsigned *ret_column) {
        assert_return(v, -EINVAL);

        if (ret_source)
                *ret_source = json_variant_is_regular(v) && v->source ? v->source->name : NULL;

        if (ret_line)
                *ret_line = json_variant_is_regular(v) ? v->line : 0;

        if (ret_column)
                *ret_column = json_variant_is_regular(v) ? v->column : 0;

        return 0;
}