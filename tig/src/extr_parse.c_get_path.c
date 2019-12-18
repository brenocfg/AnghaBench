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
struct path_entry {char const* path; } ;

/* Variables and functions */
 struct path_entry* calloc (int,scalar_t__) ; 
 int /*<<< orphan*/  free (struct path_entry*) ; 
 int /*<<< orphan*/  path_cache ; 
 struct path_entry* string_map_get (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  string_map_put (int /*<<< orphan*/ *,char const*,struct path_entry*) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char const*,char const*,scalar_t__) ; 

const char *
get_path(const char *path)
{
	struct path_entry *entry = string_map_get(&path_cache, path);

	if (!entry) {
		entry = calloc(1, sizeof(*entry) + strlen(path));
		if (!entry || !string_map_put(&path_cache, path, entry)) {
			free(entry);
			return NULL;
		}
		strncpy(entry->path, path, strlen(path));
	}

	return entry->path;
}