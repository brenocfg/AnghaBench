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
struct TYPE_4__ {int /*<<< orphan*/  rules; } ;
typedef  int /*<<< orphan*/  RoutingPolicyRule ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int routing_policy_rule_add_internal (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int routing_policy_rule_add(Manager *m, RoutingPolicyRule *rule, RoutingPolicyRule **ret) {
        return routing_policy_rule_add_internal(m, &m->rules, rule, ret);
}