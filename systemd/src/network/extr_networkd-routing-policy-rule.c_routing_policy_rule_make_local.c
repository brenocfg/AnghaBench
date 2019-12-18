#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  rules; int /*<<< orphan*/  rules_foreign; } ;
typedef  int /*<<< orphan*/  RoutingPolicyRule ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  routing_policy_rule_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  routing_policy_rule_hash_ops ; 
 scalar_t__ set_contains (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int set_ensure_allocated (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int set_put (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int routing_policy_rule_make_local(Manager *m, RoutingPolicyRule *rule) {
        int r;

        assert(m);

        if (set_contains(m->rules_foreign, rule)) {
                set_remove(m->rules_foreign, rule);

                r = set_ensure_allocated(&m->rules, &routing_policy_rule_hash_ops);
                if (r < 0)
                        return r;

                r = set_put(m->rules, rule);
                if (r < 0)
                        return r;
                if (r == 0)
                        routing_policy_rule_free(rule);
        }

        return -ENOENT;
}