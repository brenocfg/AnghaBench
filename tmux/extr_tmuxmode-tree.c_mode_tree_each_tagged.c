#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
struct mode_tree_item {int /*<<< orphan*/  itemdata; scalar_t__ tagged; } ;
struct mode_tree_data {size_t line_size; size_t current; int /*<<< orphan*/  modedata; TYPE_1__* line_list; } ;
struct client {int dummy; } ;
typedef  int /*<<< orphan*/  (* mode_tree_each_cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct client*,int /*<<< orphan*/ ) ;
typedef  int /*<<< orphan*/  key_code ;
struct TYPE_2__ {struct mode_tree_item* item; } ;

/* Variables and functions */

void
mode_tree_each_tagged(struct mode_tree_data *mtd, mode_tree_each_cb cb,
    struct client *c, key_code key, int current)
{
	struct mode_tree_item	*mti;
	u_int			 i;
	int			 fired;

	fired = 0;
	for (i = 0; i < mtd->line_size; i++) {
		mti = mtd->line_list[i].item;
		if (mti->tagged) {
			fired = 1;
			cb(mtd->modedata, mti->itemdata, c, key);
		}
	}
	if (!fired && current) {
		mti = mtd->line_list[mtd->current].item;
		cb(mtd->modedata, mti->itemdata, c, key);
	}
}