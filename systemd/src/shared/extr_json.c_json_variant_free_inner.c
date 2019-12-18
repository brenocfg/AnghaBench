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
struct TYPE_5__ {size_t n_elements; int /*<<< orphan*/  type; int /*<<< orphan*/  reference; scalar_t__ is_reference; int /*<<< orphan*/  source; } ;
typedef  TYPE_1__ JsonVariant ;

/* Variables and functions */
 scalar_t__ IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JSON_VARIANT_ARRAY ; 
 int /*<<< orphan*/  JSON_VARIANT_OBJECT ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  json_source_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_variant_is_regular (TYPE_1__*) ; 
 int /*<<< orphan*/  json_variant_unref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void json_variant_free_inner(JsonVariant *v) {
        assert(v);

        if (!json_variant_is_regular(v))
                return;

        json_source_unref(v->source);

        if (v->is_reference) {
                json_variant_unref(v->reference);
                return;
        }

        if (IN_SET(v->type, JSON_VARIANT_ARRAY, JSON_VARIANT_OBJECT)) {
                size_t i;

                for (i = 0; i < v->n_elements; i++)
                        json_variant_free_inner(v + 1 + i);
        }
}