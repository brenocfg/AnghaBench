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
struct session {char* name; } ;

/* Variables and functions */
 struct session* RB_FIND (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct session*) ; 
 int /*<<< orphan*/  sessions ; 

struct session *
session_find(const char *name)
{
	struct session	s;

	s.name = (char *) name;
	return (RB_FIND(sessions, &sessions, &s));
}