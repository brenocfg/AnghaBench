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
struct session {int dummy; } ;

/* Variables and functions */
 scalar_t__ RB_EMPTY (int /*<<< orphan*/ *) ; 
 struct session* RB_MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct session* RB_PREV (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct session*) ; 
 int /*<<< orphan*/  session_alive (struct session*) ; 
 int /*<<< orphan*/  sessions ; 

struct session *
session_previous_session(struct session *s)
{
	struct session *s2;

	if (RB_EMPTY(&sessions) || !session_alive(s))
		return (NULL);

	s2 = RB_PREV(sessions, &sessions, s);
	if (s2 == NULL)
		s2 = RB_MAX(sessions, &sessions);
	if (s2 == s)
		return (NULL);
	return (s2);
}