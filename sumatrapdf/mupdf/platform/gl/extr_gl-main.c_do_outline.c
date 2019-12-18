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
typedef  int /*<<< orphan*/  fz_outline ;

/* Variables and functions */
 int /*<<< orphan*/  BOTH ; 
 int /*<<< orphan*/  L ; 
 int /*<<< orphan*/  NW ; 
 int /*<<< orphan*/  R ; 
 int /*<<< orphan*/  count_outline (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  do_outline_imp (struct list*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outline_w ; 
 int /*<<< orphan*/  ui_layout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_splitter (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_tree_begin (struct list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ui_tree_end (struct list*) ; 

__attribute__((used)) static void do_outline(fz_outline *node)
{
	static struct list list;
	ui_layout(L, BOTH, NW, 0, 0);
	ui_tree_begin(&list, count_outline(node, 65535), outline_w, 0, 1);
	do_outline_imp(&list, 65535, node, 0);
	ui_tree_end(&list);
	ui_splitter(&outline_w, 150, 500, R);
}