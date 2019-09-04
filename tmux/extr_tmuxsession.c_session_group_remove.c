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
struct session_group {int /*<<< orphan*/  sessions; } ;
struct session {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct session_group*) ; 
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct session*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct session_group*) ; 
 int /*<<< orphan*/  gentry ; 
 struct session_group* session_group_contains (struct session*) ; 
 int /*<<< orphan*/  session_groups ; 

__attribute__((used)) static void
session_group_remove(struct session *s)
{
	struct session_group	*sg;

	if ((sg = session_group_contains(s)) == NULL)
		return;
	TAILQ_REMOVE(&sg->sessions, s, gentry);
	if (TAILQ_EMPTY(&sg->sessions)) {
		RB_REMOVE(session_groups, &session_groups, sg);
		free(sg);
	}
}