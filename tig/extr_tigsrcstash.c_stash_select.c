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
struct view {TYPE_1__* env; int /*<<< orphan*/  ref; } ;
struct line {scalar_t__ lineno; } ;
struct TYPE_2__ {int /*<<< orphan*/  stash; } ;

/* Variables and functions */
 int /*<<< orphan*/  main_select (struct view*,struct line*) ; 
 int /*<<< orphan*/  string_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_format (int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static void
stash_select(struct view *view, struct line *line)
{
	main_select(view, line);
	string_format(view->env->stash, "stash@{%d}", line->lineno - 1);
	string_copy(view->ref, view->env->stash);
}