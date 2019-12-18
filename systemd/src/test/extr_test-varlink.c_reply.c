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
typedef  int /*<<< orphan*/  VarlinkReplyFlags ;
typedef  int /*<<< orphan*/  Varlink ;
typedef  int /*<<< orphan*/  JsonVariant ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/ * json_variant_by_key (int /*<<< orphan*/ *,char*) ; 
 int json_variant_integer (int /*<<< orphan*/ *) ; 
 int n_done ; 
 int /*<<< orphan*/  sd_event_exit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  varlink_get_event (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int reply(Varlink *link, JsonVariant *parameters, const char *error_id, VarlinkReplyFlags flags, void *userdata) {
        JsonVariant *sum;

        sum = json_variant_by_key(parameters, "sum");

        assert_se(json_variant_integer(sum) == 7+22);

        if (++n_done == 2)
                sd_event_exit(varlink_get_event(link), EXIT_FAILURE);

        return 0;
}