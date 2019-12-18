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
struct environ_entry {int /*<<< orphan*/ * value; int /*<<< orphan*/  name; } ;
struct environ {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_INSERT (int /*<<< orphan*/ ,struct environ*,struct environ_entry*) ; 
 int /*<<< orphan*/  environ ; 
 struct environ_entry* environ_find (struct environ*,char const*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 struct environ_entry* xmalloc (int) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

void
environ_clear(struct environ *env, const char *name)
{
	struct environ_entry	*envent;

	if ((envent = environ_find(env, name)) != NULL) {
		free(envent->value);
		envent->value = NULL;
	} else {
		envent = xmalloc(sizeof *envent);
		envent->name = xstrdup(name);
		envent->value = NULL;
		RB_INSERT(environ, env, envent);
	}
}