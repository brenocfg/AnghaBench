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
typedef  int /*<<< orphan*/ **** JsonVariant ;
typedef  int /*<<< orphan*/  JsonDispatchFlags ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ******) ; 
 int /*<<< orphan*/ ******* json_variant_ref (int /*<<< orphan*/ *****) ; 
 int /*<<< orphan*/  json_variant_unref (int /*<<< orphan*/ *****) ; 

int json_dispatch_variant(const char *name, JsonVariant *variant, JsonDispatchFlags flags, void *userdata) {
        JsonVariant **p = userdata;

        assert(variant);
        assert(p);

        json_variant_unref(*p);
        *p = json_variant_ref(variant);

        return 0;
}