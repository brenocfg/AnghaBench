#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {struct TYPE_12__* oif; struct TYPE_12__* iif; scalar_t__ section; TYPE_2__* manager; TYPE_1__* network; } ;
struct TYPE_11__ {int /*<<< orphan*/  rules_foreign; int /*<<< orphan*/  rules; } ;
struct TYPE_10__ {scalar_t__ n_rules; int /*<<< orphan*/  rules_by_section; int /*<<< orphan*/  rules; } ;
typedef  TYPE_3__ RoutingPolicyRule ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  hashmap_remove (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  network_config_section_free (scalar_t__) ; 
 int /*<<< orphan*/  rules ; 
 TYPE_3__* set_get (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  set_remove (int /*<<< orphan*/ ,TYPE_3__*) ; 

void routing_policy_rule_free(RoutingPolicyRule *rule) {

        if (!rule)
                return;

        if (rule->network) {
                LIST_REMOVE(rules, rule->network->rules, rule);
                assert(rule->network->n_rules > 0);
                rule->network->n_rules--;

                if (rule->section)
                        hashmap_remove(rule->network->rules_by_section, rule->section);
        }

        if (rule->manager) {
                if (set_get(rule->manager->rules, rule) == rule)
                        set_remove(rule->manager->rules, rule);
                if (set_get(rule->manager->rules_foreign, rule) == rule)
                        set_remove(rule->manager->rules_foreign, rule);
        }

        network_config_section_free(rule->section);
        free(rule->iif);
        free(rule->oif);
        free(rule);
}