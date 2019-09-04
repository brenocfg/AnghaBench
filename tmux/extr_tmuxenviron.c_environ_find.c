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
struct environ_entry {char* name; } ;
struct environ {int dummy; } ;

/* Variables and functions */
 struct environ_entry* RB_FIND (int /*<<< orphan*/ ,struct environ*,struct environ_entry*) ; 
 int /*<<< orphan*/  environ ; 

struct environ_entry *
environ_find(struct environ *env, const char *name)
{
	struct environ_entry	envent;

	envent.name = (char *) name;
	return (RB_FIND(environ, env, &envent));
}