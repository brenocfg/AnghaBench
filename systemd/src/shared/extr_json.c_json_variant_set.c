#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  boolean; int /*<<< orphan*/  real; int /*<<< orphan*/  unsig; int /*<<< orphan*/  integer; } ;
struct TYPE_16__ {int type; int is_reference; int /*<<< orphan*/  reference; int /*<<< orphan*/  string; TYPE_1__ value; } ;
typedef  TYPE_2__ JsonVariant ;

/* Variables and functions */
 int /*<<< orphan*/  INLINE_STRING_MAX ; 
#define  JSON_VARIANT_ARRAY 135 
#define  JSON_VARIANT_BOOLEAN 134 
#define  JSON_VARIANT_INTEGER 133 
#define  JSON_VARIANT_NULL 132 
#define  JSON_VARIANT_OBJECT 131 
#define  JSON_VARIANT_REAL 130 
#define  JSON_VARIANT_STRING 129 
#define  JSON_VARIANT_UNSIGNED 128 
 int /*<<< orphan*/  _fallthrough_ ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  assert_not_reached (char*) ; 
 int /*<<< orphan*/  assert_se (char const*) ; 
 int /*<<< orphan*/  json_variant_boolean (TYPE_2__*) ; 
 int /*<<< orphan*/  json_variant_conservative_normalize (TYPE_2__*) ; 
 TYPE_2__* json_variant_dereference (TYPE_2__*) ; 
 int /*<<< orphan*/  json_variant_integer (TYPE_2__*) ; 
 int /*<<< orphan*/  json_variant_real (TYPE_2__*) ; 
 int /*<<< orphan*/  json_variant_ref (int /*<<< orphan*/ ) ; 
 char* json_variant_string (TYPE_2__*) ; 
 int json_variant_type (TYPE_2__*) ; 
 int /*<<< orphan*/  json_variant_unsigned (TYPE_2__*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strnlen (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void json_variant_set(JsonVariant *a, JsonVariant *b) {
        assert(a);

        b = json_variant_dereference(b);
        if (!b) {
                a->type = JSON_VARIANT_NULL;
                return;
        }

        a->type = json_variant_type(b);
        switch (a->type) {

        case JSON_VARIANT_INTEGER:
                a->value.integer = json_variant_integer(b);
                break;

        case JSON_VARIANT_UNSIGNED:
                a->value.unsig = json_variant_unsigned(b);
                break;

        case JSON_VARIANT_REAL:
                a->value.real = json_variant_real(b);
                break;

        case JSON_VARIANT_BOOLEAN:
                a->value.boolean = json_variant_boolean(b);
                break;

        case JSON_VARIANT_STRING: {
                const char *s;

                assert_se(s = json_variant_string(b));

                /* Short strings we can store inline */
                if (strnlen(s, INLINE_STRING_MAX+1) <= INLINE_STRING_MAX) {
                        strcpy(a->string, s);
                        break;
                }

                /* For longer strings, use a reference… */
                _fallthrough_;
        }

        case JSON_VARIANT_ARRAY:
        case JSON_VARIANT_OBJECT:
                a->is_reference = true;
                a->reference = json_variant_ref(json_variant_conservative_normalize(b));
                break;

        case JSON_VARIANT_NULL:
                break;

        default:
                assert_not_reached("Unexpected variant type");
        }
}