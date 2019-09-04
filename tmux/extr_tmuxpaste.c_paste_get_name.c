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
struct paste_buffer {char* name; } ;

/* Variables and functions */
 struct paste_buffer* RB_FIND (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct paste_buffer*) ; 
 int /*<<< orphan*/  paste_by_name ; 
 int /*<<< orphan*/  paste_name_tree ; 

struct paste_buffer *
paste_get_name(const char *name)
{
	struct paste_buffer	pbfind;

	if (name == NULL || *name == '\0')
		return (NULL);

	pbfind.name = (char *)name;
	return (RB_FIND(paste_name_tree, &paste_by_name, &pbfind));
}