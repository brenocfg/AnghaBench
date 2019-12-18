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
struct client {int dummy; } ;

/* Variables and functions */
 int PATH_MAX ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * realpath (char*,char*) ; 
 int /*<<< orphan*/  server_client_get_cwd (struct client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xasprintf (char**,char*,int /*<<< orphan*/ ,char const*) ; 
 char* xstrdup (char const*) ; 

char *
server_client_get_path(struct client *c, const char *file)
{
	char	*path, resolved[PATH_MAX];

	if (*file == '/')
		path = xstrdup(file);
	else
		xasprintf(&path, "%s/%s", server_client_get_cwd(c, NULL), file);
	if (realpath(path, resolved) == NULL)
		return (path);
	free(path);
	return (xstrdup(resolved));
}