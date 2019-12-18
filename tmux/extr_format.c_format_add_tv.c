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
struct timeval {int /*<<< orphan*/  tv_sec; } ;
struct format_tree {int /*<<< orphan*/  tree; } ;
struct format_entry {struct format_entry* value; int /*<<< orphan*/  t; int /*<<< orphan*/ * cb; struct format_entry* key; } ;

/* Variables and functions */
 struct format_entry* RB_INSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct format_entry*) ; 
 int /*<<< orphan*/  format_entry_tree ; 
 int /*<<< orphan*/  free (struct format_entry*) ; 
 struct format_entry* xmalloc (int) ; 
 struct format_entry* xstrdup (char const*) ; 

__attribute__((used)) static void
format_add_tv(struct format_tree *ft, const char *key, struct timeval *tv)
{
	struct format_entry	*fe;
	struct format_entry	*fe_now;

	fe = xmalloc(sizeof *fe);
	fe->key = xstrdup(key);

	fe_now = RB_INSERT(format_entry_tree, &ft->tree, fe);
	if (fe_now != NULL) {
		free(fe->key);
		free(fe);
		free(fe_now->value);
		fe = fe_now;
	}

	fe->cb = NULL;
	fe->t = tv->tv_sec;

	fe->value = NULL;
}