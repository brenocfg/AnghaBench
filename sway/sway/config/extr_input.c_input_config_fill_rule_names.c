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
struct xkb_rule_names {int /*<<< orphan*/  variant; int /*<<< orphan*/  rules; int /*<<< orphan*/  options; int /*<<< orphan*/  model; int /*<<< orphan*/  layout; } ;
struct input_config {int /*<<< orphan*/  xkb_variant; int /*<<< orphan*/  xkb_rules; int /*<<< orphan*/  xkb_options; int /*<<< orphan*/  xkb_model; int /*<<< orphan*/  xkb_layout; } ;

/* Variables and functions */

void input_config_fill_rule_names(struct input_config *ic,
		struct xkb_rule_names *rules) {
	rules->layout = ic->xkb_layout;
	rules->model = ic->xkb_model;
	rules->options = ic->xkb_options;
	rules->rules = ic->xkb_rules;
	rules->variant = ic->xkb_variant;
}