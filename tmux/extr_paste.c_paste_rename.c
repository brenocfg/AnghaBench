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
struct paste_buffer {scalar_t__ automatic; void* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_INSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct paste_buffer*) ; 
 int /*<<< orphan*/  RB_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct paste_buffer*) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  paste_by_name ; 
 struct paste_buffer* paste_get_name (char const*) ; 
 int /*<<< orphan*/  paste_name_tree ; 
 int /*<<< orphan*/  paste_num_automatic ; 
 int /*<<< orphan*/  xasprintf (char**,char*,char const*) ; 
 void* xstrdup (char const*) ; 

int
paste_rename(const char *oldname, const char *newname, char **cause)
{
	struct paste_buffer	*pb, *pb_new;

	if (cause != NULL)
		*cause = NULL;

	if (oldname == NULL || *oldname == '\0') {
		if (cause != NULL)
			*cause = xstrdup("no buffer");
		return (-1);
	}
	if (newname == NULL || *newname == '\0') {
		if (cause != NULL)
			*cause = xstrdup("new name is empty");
		return (-1);
	}

	pb = paste_get_name(oldname);
	if (pb == NULL) {
		if (cause != NULL)
			xasprintf(cause, "no buffer %s", oldname);
		return (-1);
	}

	pb_new = paste_get_name(newname);
	if (pb_new != NULL) {
		if (cause != NULL)
			xasprintf(cause, "buffer %s already exists", newname);
		return (-1);
	}

	RB_REMOVE(paste_name_tree, &paste_by_name, pb);

	free(pb->name);
	pb->name = xstrdup(newname);

	if (pb->automatic)
		paste_num_automatic--;
	pb->automatic = 0;

	RB_INSERT(paste_name_tree, &paste_by_name, pb);

	return (0);
}