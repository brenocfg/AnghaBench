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
struct criteria {struct criteria* raw; struct criteria* cmdlist; struct criteria* workspace; int /*<<< orphan*/  con_mark; int /*<<< orphan*/  app_id; int /*<<< orphan*/  shell; int /*<<< orphan*/  title; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct criteria*) ; 
 int /*<<< orphan*/  pcre_free (int /*<<< orphan*/ ) ; 

void criteria_destroy(struct criteria *criteria) {
	pcre_free(criteria->title);
	pcre_free(criteria->shell);
	pcre_free(criteria->app_id);
#if HAVE_XWAYLAND
	pcre_free(criteria->class);
	pcre_free(criteria->instance);
	pcre_free(criteria->window_role);
#endif
	pcre_free(criteria->con_mark);
	free(criteria->workspace);
	free(criteria->cmdlist);
	free(criteria->raw);
	free(criteria);
}