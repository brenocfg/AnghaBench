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
struct TYPE_3__ {int graph; } ;
struct TYPE_4__ {TYPE_1__ commit_title; } ;
struct view_column {TYPE_2__ opt; } ;
struct view {int dummy; } ;
typedef  enum open_flags { ____Placeholder_open_flags } open_flags ;
typedef  enum graph_display { ____Placeholder_graph_display } graph_display ;

/* Variables and functions */
 scalar_t__ COMMIT_ORDER_REVERSE ; 
 int GRAPH_DISPLAY_NO ; 
 int /*<<< orphan*/  open_in_pager_mode (int) ; 
 scalar_t__ opt_commit_order ; 
 int /*<<< orphan*/  opt_log_follow ; 

__attribute__((used)) static enum graph_display
main_with_graph(struct view *view, struct view_column *column, enum open_flags flags)
{
	return column && opt_commit_order != COMMIT_ORDER_REVERSE && !open_in_pager_mode(flags) && !opt_log_follow
	       ? column->opt.commit_title.graph : GRAPH_DISPLAY_NO;
}