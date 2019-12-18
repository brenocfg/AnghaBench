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
 int EINVAL ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  json_variant_is_object (int /*<<< orphan*/ *) ; 
 int json_variant_new_object (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int varlink_sanitize_parameters(JsonVariant **v) {
        assert(v);

        /* Varlink always wants a parameters list, hence make one if the caller doesn't want any */
        if (!*v)
                return json_variant_new_object(v, NULL, 0);
        else if (!json_variant_is_object(*v))
                return -EINVAL;

        return 0;
}