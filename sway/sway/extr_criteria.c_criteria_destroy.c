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
struct criteria {struct criteria* raw; struct criteria* cmdlist; struct criteria* workspace; int /*<<< orphan*/  con_mark; int /*<<< orphan*/  window_role; int /*<<< orphan*/  instance; int /*<<< orphan*/  class; int /*<<< orphan*/  app_id; int /*<<< orphan*/  shell; int /*<<< orphan*/  title; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct criteria*) ; 
 int /*<<< orphan*/  pattern_destroy (int /*<<< orphan*/ ) ; 

void criteria_destroy(struct criteria *criteria) {
	pattern_destroy(criteria->title);
	pattern_destroy(criteria->shell);
	pattern_destroy(criteria->app_id);
#if HAVE_XWAYLAND
	pattern_destroy(criteria->class);
	pattern_destroy(criteria->instance);
	pattern_destroy(criteria->window_role);
#endif
	pattern_destroy(criteria->con_mark);
	free(criteria->workspace);
	free(criteria->cmdlist);
	free(criteria->raw);
	free(criteria);
}