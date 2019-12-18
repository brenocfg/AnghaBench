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
struct line {int dummy; } ;
struct grep_line {scalar_t__ lineno; int /*<<< orphan*/ * file; } ;
struct TYPE_2__ {scalar_t__ lineno; int /*<<< orphan*/  file; scalar_t__* ref; } ;

/* Variables and functions */
 struct grep_line* grep_get_line (struct line*) ; 
 int /*<<< orphan*/  string_ncopy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
grep_select(struct view *view, struct line *line)
{
	struct grep_line *grep = grep_get_line(line);

	if (!*grep->file)
		return;
	view->env->ref[0] = 0;
	string_ncopy(view->env->file, grep->file, strlen(grep->file));
	string_ncopy(view->ref, grep->file, strlen(grep->file));
	view->env->lineno = grep->lineno + 1;
}