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
 scalar_t__ JSON_VARIANT_STRING ; 
 scalar_t__ JSON_VARIANT_UNSIGNED ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/ * json_variant_by_index (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/ * json_variant_by_key (int /*<<< orphan*/ *,char*) ; 
 int json_variant_elements (int /*<<< orphan*/ *) ; 
 scalar_t__ json_variant_has_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int json_variant_integer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_variant_string (int /*<<< orphan*/ *) ; 
 scalar_t__ json_variant_type (int /*<<< orphan*/ *) ; 
 unsigned int json_variant_unsigned (int /*<<< orphan*/ *) ; 
 int streq (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void test_1(JsonVariant *v) {
        JsonVariant *p, *q;
        unsigned i;

        /* 3 keys + 3 values */
        assert_se(json_variant_elements(v) == 6);

        /* has k */
        p = json_variant_by_key(v, "k");
        assert_se(p && json_variant_type(p) == JSON_VARIANT_STRING);

        /* k equals v */
        assert_se(streq(json_variant_string(p), "v"));

        /* has foo */
        p = json_variant_by_key(v, "foo");
        assert_se(p && json_variant_type(p) == JSON_VARIANT_ARRAY && json_variant_elements(p) == 3);

        /* check  foo[0] = 1, foo[1] = 2, foo[2] = 3 */
        for (i = 0; i < 3; ++i) {
                q = json_variant_by_index(p, i);
                assert_se(q && json_variant_type(q) == JSON_VARIANT_UNSIGNED && json_variant_unsigned(q) == (i+1));
                assert_se(q && json_variant_has_type(q, JSON_VARIANT_INTEGER) && json_variant_integer(q) == (i+1));
        }

        /* has bar */
        p = json_variant_by_key(v, "bar");
        assert_se(p && json_variant_type(p) == JSON_VARIANT_OBJECT && json_variant_elements(p) == 2);

        /* zap is null */
        q = json_variant_by_key(p, "zap");
        assert_se(q && json_variant_type(q) == JSON_VARIANT_NULL);
}