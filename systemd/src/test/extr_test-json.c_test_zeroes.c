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
 int /*<<< orphan*/ * IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JSON_VARIANT_INTEGER ; 
 int /*<<< orphan*/  JSON_VARIANT_REAL ; 
 int /*<<< orphan*/  JSON_VARIANT_UNSIGNED ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/ * json_variant_by_index (int /*<<< orphan*/ *,size_t) ; 
 size_t json_variant_elements (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_variant_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ json_variant_integer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_variant_is_integer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_variant_is_negative (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_variant_is_number (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_variant_is_real (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_variant_is_unsigned (int /*<<< orphan*/ *) ; 
 long double json_variant_real (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_variant_type (int /*<<< orphan*/ *) ; 
 unsigned int json_variant_unsigned (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_zeroes(JsonVariant *v) {
        size_t i;

        /* Make sure zero is how we expect it. */

        assert_se(json_variant_elements(v) == 13);

        for (i = 0; i < json_variant_elements(v); i++) {
                JsonVariant *w;
                size_t j;

                assert_se(w = json_variant_by_index(v, i));

                assert_se(json_variant_integer(w) == 0);
                assert_se(json_variant_unsigned(w) == 0U);

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
                assert_se(json_variant_real(w) == 0.0L);
#pragma GCC diagnostic pop

                assert_se(json_variant_is_integer(w));
                assert_se(json_variant_is_unsigned(w));
                assert_se(json_variant_is_real(w));
                assert_se(json_variant_is_number(w));

                assert_se(!json_variant_is_negative(w));

                assert_se(IN_SET(json_variant_type(w), JSON_VARIANT_INTEGER, JSON_VARIANT_UNSIGNED, JSON_VARIANT_REAL));

                for (j = 0; j < json_variant_elements(v); j++) {
                        JsonVariant *q;

                        assert_se(q = json_variant_by_index(v, j));

                        assert_se(json_variant_equal(w, q));
                }
        }
}