#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ intmax_t ;
struct TYPE_8__ {long double real; int /*<<< orphan*/  unsig; scalar_t__ integer; } ;
struct TYPE_9__ {int type; TYPE_1__ value; struct TYPE_9__* reference; scalar_t__ is_reference; } ;
typedef  TYPE_2__ JsonVariant ;

/* Variables and functions */
 int /*<<< orphan*/  INTMAX_MAX ; 
#define  JSON_VARIANT_INTEGER 130 
 TYPE_2__* JSON_VARIANT_MAGIC_ZERO_INTEGER ; 
 TYPE_2__* JSON_VARIANT_MAGIC_ZERO_REAL ; 
 TYPE_2__* JSON_VARIANT_MAGIC_ZERO_UNSIGNED ; 
#define  JSON_VARIANT_REAL 129 
#define  JSON_VARIANT_UNSIGNED 128 
 int /*<<< orphan*/  json_variant_is_regular (TYPE_2__*) ; 
 int /*<<< orphan*/  log_debug (char*,...) ; 

intmax_t json_variant_integer(JsonVariant *v) {
        if (!v)
                goto mismatch;
        if (v == JSON_VARIANT_MAGIC_ZERO_INTEGER ||
            v == JSON_VARIANT_MAGIC_ZERO_UNSIGNED ||
            v == JSON_VARIANT_MAGIC_ZERO_REAL)
                return 0;
        if (!json_variant_is_regular(v))
                goto mismatch;
        if (v->is_reference)
                return json_variant_integer(v->reference);

        switch (v->type) {

        case JSON_VARIANT_INTEGER:
                return v->value.integer;

        case JSON_VARIANT_UNSIGNED:
                if (v->value.unsig <= INTMAX_MAX)
                        return (intmax_t) v->value.unsig;

                log_debug("Unsigned integer %ju requested as signed integer and out of range, returning 0.", v->value.unsig);
                return 0;

        case JSON_VARIANT_REAL: {
                intmax_t converted;

                converted = (intmax_t) v->value.real;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
                if ((long double) converted == v->value.real)
#pragma GCC diagnostic pop
                        return converted;

                log_debug("Real %Lg requested as integer, and cannot be converted losslessly, returning 0.", v->value.real);
                return 0;
        }

        default:
                break;
        }

mismatch:
        log_debug("Non-integer JSON variant requested as integer, returning 0.");
        return 0;
}