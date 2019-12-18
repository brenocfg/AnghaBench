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
struct TYPE_6__ {size_t n_elements; struct TYPE_6__* reference; scalar_t__ is_reference; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ JsonVariant ;

/* Variables and functions */
 int /*<<< orphan*/  IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JSON_VARIANT_ARRAY ; 
 TYPE_1__* JSON_VARIANT_MAGIC_EMPTY_ARRAY ; 
 TYPE_1__* JSON_VARIANT_MAGIC_EMPTY_OBJECT ; 
 int /*<<< orphan*/  JSON_VARIANT_OBJECT ; 
 int /*<<< orphan*/  json_variant_is_regular (TYPE_1__*) ; 
 int /*<<< orphan*/  log_debug (char*) ; 

size_t json_variant_elements(JsonVariant *v) {
        if (!v)
                return 0;
        if (v == JSON_VARIANT_MAGIC_EMPTY_ARRAY ||
            v == JSON_VARIANT_MAGIC_EMPTY_OBJECT)
                return 0;
        if (!json_variant_is_regular(v))
                goto mismatch;
        if (!IN_SET(v->type, JSON_VARIANT_ARRAY, JSON_VARIANT_OBJECT))
                goto mismatch;
        if (v->is_reference)
                return json_variant_elements(v->reference);

        return v->n_elements;

mismatch:
        log_debug("Number of elements in non-array/non-object JSON variant requested, returning 0.");
        return 0;
}