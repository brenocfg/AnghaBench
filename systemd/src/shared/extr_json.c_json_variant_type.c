#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  JsonVariantType ;
typedef  TYPE_1__ JsonVariant ;

/* Variables and functions */
 int /*<<< orphan*/  JSON_VARIANT_ARRAY ; 
 int /*<<< orphan*/  JSON_VARIANT_BOOLEAN ; 
 int /*<<< orphan*/  JSON_VARIANT_INTEGER ; 
 TYPE_1__* JSON_VARIANT_MAGIC_EMPTY_ARRAY ; 
 TYPE_1__* JSON_VARIANT_MAGIC_EMPTY_OBJECT ; 
 TYPE_1__* JSON_VARIANT_MAGIC_EMPTY_STRING ; 
 TYPE_1__* JSON_VARIANT_MAGIC_FALSE ; 
 TYPE_1__* JSON_VARIANT_MAGIC_NULL ; 
 TYPE_1__* JSON_VARIANT_MAGIC_TRUE ; 
 TYPE_1__* JSON_VARIANT_MAGIC_ZERO_INTEGER ; 
 TYPE_1__* JSON_VARIANT_MAGIC_ZERO_REAL ; 
 TYPE_1__* JSON_VARIANT_MAGIC_ZERO_UNSIGNED ; 
 int /*<<< orphan*/  JSON_VARIANT_NULL ; 
 int /*<<< orphan*/  JSON_VARIANT_OBJECT ; 
 int /*<<< orphan*/  JSON_VARIANT_REAL ; 
 int /*<<< orphan*/  JSON_VARIANT_STRING ; 
 int /*<<< orphan*/  JSON_VARIANT_UNSIGNED ; 
 int /*<<< orphan*/  _JSON_VARIANT_TYPE_INVALID ; 
 scalar_t__ json_variant_is_const_string (TYPE_1__*) ; 

JsonVariantType json_variant_type(JsonVariant *v) {

        if (!v)
                return _JSON_VARIANT_TYPE_INVALID;

        if (json_variant_is_const_string(v))
                return JSON_VARIANT_STRING;

        if (v == JSON_VARIANT_MAGIC_TRUE || v == JSON_VARIANT_MAGIC_FALSE)
                return JSON_VARIANT_BOOLEAN;

        if (v == JSON_VARIANT_MAGIC_NULL)
                return JSON_VARIANT_NULL;

        if (v == JSON_VARIANT_MAGIC_ZERO_INTEGER)
                return JSON_VARIANT_INTEGER;

        if (v == JSON_VARIANT_MAGIC_ZERO_UNSIGNED)
                return JSON_VARIANT_UNSIGNED;

        if (v == JSON_VARIANT_MAGIC_ZERO_REAL)
                return JSON_VARIANT_REAL;

        if (v == JSON_VARIANT_MAGIC_EMPTY_STRING)
                return JSON_VARIANT_STRING;

        if (v == JSON_VARIANT_MAGIC_EMPTY_ARRAY)
                return JSON_VARIANT_ARRAY;

        if (v == JSON_VARIANT_MAGIC_EMPTY_OBJECT)
                return JSON_VARIANT_OBJECT;

        return v->type;
}