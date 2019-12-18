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
typedef  scalar_t__ xmlChar ;

/* Variables and functions */
 size_t MAX_PATHS ; 
 scalar_t__ const PATH_SEPARATOR ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 size_t nbpaths ; 
 int /*<<< orphan*/ ** paths ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * xmlStrndup (scalar_t__ const*,int) ; 

__attribute__((used)) static
void parsePath(const xmlChar *path) {
    const xmlChar *cur;

    if (path == NULL)
	return;
    while (*path != 0) {
	if (nbpaths >= MAX_PATHS) {
	    fprintf(stderr, "MAX_PATHS reached: too many paths\n");
	    return;
	}
	cur = path;
	while ((*cur == ' ') || (*cur == PATH_SEPARATOR))
	    cur++;
	path = cur;
	while ((*cur != 0) && (*cur != ' ') && (*cur != PATH_SEPARATOR))
	    cur++;
	if (cur != path) {
	    paths[nbpaths] = xmlStrndup(path, cur - path);
	    if (paths[nbpaths] != NULL)
		nbpaths++;
	    path = cur;
	}
    }
}