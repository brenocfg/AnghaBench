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
 scalar_t__ JSON_VARIANT_ARRAY ; 
 int /*<<< orphan*/  JSON_VARIANT_INTEGER ; 
 scalar_t__ JSON_VARIANT_NULL ; 
 scalar_t__ JSON_VARIANT_OBJECT ; 
 scalar_t__ JSON_VARIANT_REAL ; 
 scalar_t__ JSON_VARIANT_STRING ; 
 scalar_t__ JSON_VARIANT_UNSIGNED ; 
 int /*<<< orphan*/  assert_se (int) ; 
 double fabsl (scalar_t__) ; 
 int /*<<< orphan*/ * json_variant_by_index (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * json_variant_by_key (int /*<<< orphan*/ *,char*) ; 
 int json_variant_elements (int /*<<< orphan*/ *) ; 
 scalar_t__ json_variant_has_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int json_variant_integer (int /*<<< orphan*/ *) ; 
 scalar_t__ json_variant_real (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_variant_string (int /*<<< orphan*/ *) ; 
 scalar_t__ json_variant_type (int /*<<< orphan*/ *) ; 
 int json_variant_unsigned (int /*<<< orphan*/ *) ; 
 scalar_t__ streq (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void test_2(JsonVariant *v) {
        JsonVariant *p, *q;

        /* 2 keys + 2 values */
        assert_se(json_variant_elements(v) == 4);

        /* has mutant */
        p = json_variant_by_key(v, "mutant");
        assert_se(p && json_variant_type(p) == JSON_VARIANT_ARRAY && json_variant_elements(p) == 4);

        /* mutant[0] == 1 */
        q = json_variant_by_index(p, 0);
        assert_se(q && json_variant_type(q) == JSON_VARIANT_UNSIGNED && json_variant_unsigned(q) == 1);
        assert_se(q && json_variant_has_type(q, JSON_VARIANT_INTEGER) && json_variant_integer(q) == 1);

        /* mutant[1] == null */
        q = json_variant_by_index(p, 1);
        assert_se(q && json_variant_type(q) == JSON_VARIANT_NULL);

        /* mutant[2] == "1" */
        q = json_variant_by_index(p, 2);
        assert_se(q && json_variant_type(q) == JSON_VARIANT_STRING && streq(json_variant_string(q), "1"));

        /* mutant[3] == JSON_VARIANT_OBJECT */
        q = json_variant_by_index(p, 3);
        assert_se(q && json_variant_type(q) == JSON_VARIANT_OBJECT && json_variant_elements(q) == 2);

        /* has 1 */
        p = json_variant_by_key(q, "1");
        assert_se(p && json_variant_type(p) == JSON_VARIANT_ARRAY && json_variant_elements(p) == 2);

        /* "1"[0] == 1 */
        q = json_variant_by_index(p, 0);
        assert_se(q && json_variant_type(q) == JSON_VARIANT_UNSIGNED && json_variant_unsigned(q) == 1);
        assert_se(q && json_variant_has_type(q, JSON_VARIANT_INTEGER) && json_variant_integer(q) == 1);

        /* "1"[1] == "1" */
        q = json_variant_by_index(p, 1);
        assert_se(q && json_variant_type(q) == JSON_VARIANT_STRING && streq(json_variant_string(q), "1"));

        /* has thisisaverylongproperty */
        p = json_variant_by_key(v, "thisisaverylongproperty");
        assert_se(p && json_variant_type(p) == JSON_VARIANT_REAL && fabsl(json_variant_real(p) - 1.27) < 0.001);
}