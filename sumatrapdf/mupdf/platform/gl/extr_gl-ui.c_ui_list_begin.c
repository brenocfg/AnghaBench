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
struct list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ui_tree_begin (struct list*,int,int,int,int /*<<< orphan*/ ) ; 

void ui_list_begin(struct list *list, int count, int req_w, int req_h)
{
	ui_tree_begin(list, count, req_w, req_h, 0);
}