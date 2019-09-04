#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct cmd_results {int dummy; } ;
struct TYPE_6__ {TYPE_2__* current_bar; } ;
struct TYPE_4__ {int /*<<< orphan*/  separator; } ;
struct TYPE_5__ {TYPE_1__ colors; } ;

/* Variables and functions */
 TYPE_3__* config ; 
 struct cmd_results* parse_single_color (int /*<<< orphan*/ *,char*,int,char**) ; 

struct cmd_results *bar_colors_cmd_separator(int argc, char **argv) {
	return parse_single_color(&(config->current_bar->colors.separator),
			"separator", argc, argv);
}