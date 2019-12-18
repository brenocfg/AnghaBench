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
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct session*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gentry ; 
 int /*<<< orphan*/ * session_group_contains (struct session*) ; 

void
session_group_add(struct session_group *sg, struct session *s)
{
	if (session_group_contains(s) == NULL)
		TAILQ_INSERT_TAIL(&sg->sessions, s, gentry);
}