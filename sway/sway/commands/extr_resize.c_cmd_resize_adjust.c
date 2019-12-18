#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct sway_container {int dummy; } ;
struct resize_amount {scalar_t__ unit; int amount; } ;
struct cmd_results {int dummy; } ;
struct TYPE_3__ {struct sway_container* container; } ;
struct TYPE_4__ {TYPE_1__ handler_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_INVALID ; 
 scalar_t__ RESIZE_UNIT_DEFAULT ; 
 scalar_t__ RESIZE_UNIT_INVALID ; 
 scalar_t__ RESIZE_UNIT_PPT ; 
 scalar_t__ RESIZE_UNIT_PX ; 
 scalar_t__ WLR_EDGE_NONE ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,char const*) ; 
 TYPE_2__* config ; 
 scalar_t__ container_is_floating (struct sway_container*) ; 
 int parse_resize_amount (int,char**,struct resize_amount*) ; 
 scalar_t__ parse_resize_axis (char*) ; 
 struct cmd_results* resize_adjust_floating (scalar_t__,struct resize_amount*) ; 
 struct cmd_results* resize_adjust_tiled (scalar_t__,struct resize_amount*) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static struct cmd_results *cmd_resize_adjust(int argc, char **argv,
		int multiplier) {
	const char usage[] = "Expected 'resize grow|shrink <direction> "
		"[<amount> px|ppt [or <amount> px|ppt]]'";
	uint32_t axis = parse_resize_axis(*argv);
	if (axis == WLR_EDGE_NONE) {
		return cmd_results_new(CMD_INVALID, usage);
	}
	--argc; ++argv;

	// First amount
	struct resize_amount first_amount;
	if (argc) {
		int num_consumed_args = parse_resize_amount(argc, argv, &first_amount);
		argc -= num_consumed_args;
		argv += num_consumed_args;
		if (first_amount.unit == RESIZE_UNIT_INVALID) {
			return cmd_results_new(CMD_INVALID, usage);
		}
	} else {
		first_amount.amount = 10;
		first_amount.unit = RESIZE_UNIT_DEFAULT;
	}

	// "or"
	if (argc) {
		if (strcmp(*argv, "or") != 0) {
			return cmd_results_new(CMD_INVALID, usage);
		}
		--argc; ++argv;
	}

	// Second amount
	struct resize_amount second_amount;
	if (argc) {
		int num_consumed_args = parse_resize_amount(argc, argv, &second_amount);
		if (argc > num_consumed_args) {
			return cmd_results_new(CMD_INVALID, usage);
		}
		if (second_amount.unit == RESIZE_UNIT_INVALID) {
			return cmd_results_new(CMD_INVALID, usage);
		}
	} else {
		second_amount.amount = 0;
		second_amount.unit = RESIZE_UNIT_INVALID;
	}

	first_amount.amount *= multiplier;
	second_amount.amount *= multiplier;

	struct sway_container *con = config->handler_context.container;
	if (container_is_floating(con)) {
		// Floating containers can only resize in px. Choose an amount which
		// uses px, with fallback to an amount that specified no unit.
		if (first_amount.unit == RESIZE_UNIT_PX) {
			return resize_adjust_floating(axis, &first_amount);
		} else if (second_amount.unit == RESIZE_UNIT_PX) {
			return resize_adjust_floating(axis, &second_amount);
		} else if (first_amount.unit == RESIZE_UNIT_DEFAULT) {
			return resize_adjust_floating(axis, &first_amount);
		} else if (second_amount.unit == RESIZE_UNIT_DEFAULT) {
			return resize_adjust_floating(axis, &second_amount);
		} else {
			return cmd_results_new(CMD_INVALID,
					"Floating containers cannot use ppt measurements");
		}
	}

	// For tiling, prefer ppt -> default -> px
	if (first_amount.unit == RESIZE_UNIT_PPT) {
		return resize_adjust_tiled(axis, &first_amount);
	} else if (second_amount.unit == RESIZE_UNIT_PPT) {
		return resize_adjust_tiled(axis, &second_amount);
	} else if (first_amount.unit == RESIZE_UNIT_DEFAULT) {
		return resize_adjust_tiled(axis, &first_amount);
	} else if (second_amount.unit == RESIZE_UNIT_DEFAULT) {
		return resize_adjust_tiled(axis, &second_amount);
	} else {
		return resize_adjust_tiled(axis, &first_amount);
	}
}