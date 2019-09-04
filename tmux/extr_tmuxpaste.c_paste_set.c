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
struct paste_buffer {char* data; size_t size; int /*<<< orphan*/  created; scalar_t__ order; scalar_t__ automatic; void* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_INSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct paste_buffer*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  paste_add (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  paste_by_name ; 
 int /*<<< orphan*/  paste_by_time ; 
 int /*<<< orphan*/  paste_free (struct paste_buffer*) ; 
 struct paste_buffer* paste_get_name (char const*) ; 
 int /*<<< orphan*/  paste_name_tree ; 
 int /*<<< orphan*/  paste_next_order ; 
 int /*<<< orphan*/  paste_time_tree ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 struct paste_buffer* xmalloc (int) ; 
 void* xstrdup (char const*) ; 

int
paste_set(char *data, size_t size, const char *name, char **cause)
{
	struct paste_buffer	*pb, *old;

	if (cause != NULL)
		*cause = NULL;

	if (size == 0) {
		free(data);
		return (0);
	}
	if (name == NULL) {
		paste_add(NULL, data, size);
		return (0);
	}

	if (*name == '\0') {
		if (cause != NULL)
			*cause = xstrdup("empty buffer name");
		return (-1);
	}

	pb = xmalloc(sizeof *pb);

	pb->name = xstrdup(name);

	pb->data = data;
	pb->size = size;

	pb->automatic = 0;
	pb->order = paste_next_order++;

	pb->created = time(NULL);

	if ((old = paste_get_name(name)) != NULL)
		paste_free(old);

	RB_INSERT(paste_name_tree, &paste_by_name, pb);
	RB_INSERT(paste_time_tree, &paste_by_time, pb);

	return (0);
}