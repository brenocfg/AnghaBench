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
struct session_group {int /*<<< orphan*/  sessions; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_INSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct session_group*) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 struct session_group* session_group_find (char const*) ; 
 int /*<<< orphan*/  session_groups ; 
 struct session_group* xcalloc (int,int) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

struct session_group *
session_group_new(const char *name)
{
	struct session_group	*sg;

	if ((sg = session_group_find(name)) != NULL)
		return (sg);

	sg = xcalloc(1, sizeof *sg);
	sg->name = xstrdup(name);
	TAILQ_INIT(&sg->sessions);

	RB_INSERT(session_groups, &session_groups, sg);
	return (sg);
}