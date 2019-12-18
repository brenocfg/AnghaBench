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
struct view {TYPE_1__* env; int /*<<< orphan*/  ref; } ;
struct reference {TYPE_2__* ref; } ;
struct line {struct reference* data; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; int /*<<< orphan*/  id; } ;
struct TYPE_3__ {int /*<<< orphan*/  ref; int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int /*<<< orphan*/  REFS_ALL_NAME ; 
 int /*<<< orphan*/  ref_update_env (TYPE_1__*,TYPE_2__*,int) ; 
 scalar_t__ refs_is_all (struct reference*) ; 
 int /*<<< orphan*/  string_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_copy_rev (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_ncopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
refs_select(struct view *view, struct line *line)
{
	struct reference *reference = line->data;

	if (refs_is_all(reference)) {
		string_copy(view->ref, REFS_ALL_NAME);
		return;
	}
	string_copy_rev(view->ref, reference->ref->id);
	string_copy_rev(view->env->head, reference->ref->id);
	string_ncopy(view->env->ref, reference->ref->name, strlen(reference->ref->name));
	ref_update_env(view->env, reference->ref, false);
}