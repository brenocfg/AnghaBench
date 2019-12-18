#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  source; int /*<<< orphan*/  column; int /*<<< orphan*/  line; } ;
typedef  TYPE_1__ JsonVariant ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  json_source_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_variant_is_regular (TYPE_1__*) ; 

__attribute__((used)) static void json_variant_copy_source(JsonVariant *v, JsonVariant *from) {
        assert(v);
        assert(from);

        if (!json_variant_is_regular(from))
                return;

        v->line = from->line;
        v->column = from->column;
        v->source = json_source_ref(from->source);
}