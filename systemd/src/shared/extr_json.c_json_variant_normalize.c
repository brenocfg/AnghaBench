#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  JsonVariant ;

/* Variables and functions */
#define  JSON_VARIANT_ARRAY 135 
#define  JSON_VARIANT_BOOLEAN 134 
#define  JSON_VARIANT_INTEGER 133 
 int /*<<< orphan*/ * JSON_VARIANT_MAGIC_EMPTY_ARRAY ; 
 int /*<<< orphan*/ * JSON_VARIANT_MAGIC_EMPTY_OBJECT ; 
 int /*<<< orphan*/ * JSON_VARIANT_MAGIC_EMPTY_STRING ; 
 int /*<<< orphan*/ * JSON_VARIANT_MAGIC_FALSE ; 
 int /*<<< orphan*/ * JSON_VARIANT_MAGIC_NULL ; 
 int /*<<< orphan*/ * JSON_VARIANT_MAGIC_TRUE ; 
 int /*<<< orphan*/ * JSON_VARIANT_MAGIC_ZERO_INTEGER ; 
 int /*<<< orphan*/ * JSON_VARIANT_MAGIC_ZERO_REAL ; 
 int /*<<< orphan*/ * JSON_VARIANT_MAGIC_ZERO_UNSIGNED ; 
#define  JSON_VARIANT_NULL 132 
#define  JSON_VARIANT_OBJECT 131 
#define  JSON_VARIANT_REAL 130 
#define  JSON_VARIANT_STRING 129 
#define  JSON_VARIANT_UNSIGNED 128 
 int /*<<< orphan*/  isempty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_variant_boolean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_variant_dereference (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_variant_elements (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_variant_integer (int /*<<< orphan*/ *) ; 
 double json_variant_real (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_variant_string (int /*<<< orphan*/ *) ; 
 int json_variant_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_variant_unsigned (int /*<<< orphan*/ *) ; 

__attribute__((used)) static JsonVariant *json_variant_normalize(JsonVariant *v) {

        /* Converts json variants to their normalized form, i.e. fully dereferenced and wherever possible converted to
         * the "magic" version if there is one */

        if (!v)
                return NULL;

        v = json_variant_dereference(v);

        switch (json_variant_type(v)) {

        case JSON_VARIANT_BOOLEAN:
                return json_variant_boolean(v) ? JSON_VARIANT_MAGIC_TRUE : JSON_VARIANT_MAGIC_FALSE;

        case JSON_VARIANT_NULL:
                return JSON_VARIANT_MAGIC_NULL;

        case JSON_VARIANT_INTEGER:
                return json_variant_integer(v) == 0 ? JSON_VARIANT_MAGIC_ZERO_INTEGER : v;

        case JSON_VARIANT_UNSIGNED:
                return json_variant_unsigned(v) == 0 ? JSON_VARIANT_MAGIC_ZERO_UNSIGNED : v;

        case JSON_VARIANT_REAL:
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
                return json_variant_real(v) == 0.0 ? JSON_VARIANT_MAGIC_ZERO_REAL : v;
#pragma GCC diagnostic pop

        case JSON_VARIANT_STRING:
                return isempty(json_variant_string(v)) ? JSON_VARIANT_MAGIC_EMPTY_STRING : v;

        case JSON_VARIANT_ARRAY:
                return json_variant_elements(v) == 0 ? JSON_VARIANT_MAGIC_EMPTY_ARRAY : v;

        case JSON_VARIANT_OBJECT:
                return json_variant_elements(v) == 0 ? JSON_VARIANT_MAGIC_EMPTY_OBJECT : v;

        default:
                return v;
        }
}