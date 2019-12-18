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
struct TYPE_6__ {scalar_t__ type; char const* string; struct TYPE_6__* reference; scalar_t__ is_reference; } ;
typedef  TYPE_1__ JsonVariant ;

/* Variables and functions */
 TYPE_1__* JSON_VARIANT_MAGIC_EMPTY_STRING ; 
 scalar_t__ JSON_VARIANT_STRING ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ json_variant_is_const_string (TYPE_1__*) ; 
 scalar_t__ json_variant_is_magic (TYPE_1__*) ; 
 int /*<<< orphan*/  log_debug (char*) ; 

const char *json_variant_string(JsonVariant *v) {
        if (!v)
                return NULL;
        if (v == JSON_VARIANT_MAGIC_EMPTY_STRING)
                return "";
        if (json_variant_is_magic(v))
                goto mismatch;
        if (json_variant_is_const_string(v)) {
                uintptr_t p = (uintptr_t) v;

                assert((p & 1) != 0);
                return (const char*) (p ^ 1U);
        }

        if (v->is_reference)
                return json_variant_string(v->reference);
        if (v->type != JSON_VARIANT_STRING)
                goto mismatch;

        return v->string;

mismatch:
        log_debug("Non-string JSON variant requested as string, returning NULL.");
        return NULL;
}