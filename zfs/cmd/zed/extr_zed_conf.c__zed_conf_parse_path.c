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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  ENAMETOOLONG ; 
 int /*<<< orphan*/  ENOMEM ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  getcwd (char*,int) ; 
 char* strdup (char const*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int strlcat (char*,char const*,int) ; 
 int /*<<< orphan*/  zed_log_die (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_zed_conf_parse_path(char **resultp, const char *path)
{
	char buf[PATH_MAX];

	assert(resultp != NULL);
	assert(path != NULL);

	if (*resultp)
		free(*resultp);

	if (path[0] == '/') {
		*resultp = strdup(path);
	} else if (!getcwd(buf, sizeof (buf))) {
		zed_log_die("Failed to get current working dir: %s",
		    strerror(errno));
	} else if (strlcat(buf, "/", sizeof (buf)) >= sizeof (buf)) {
		zed_log_die("Failed to copy path: %s", strerror(ENAMETOOLONG));
	} else if (strlcat(buf, path, sizeof (buf)) >= sizeof (buf)) {
		zed_log_die("Failed to copy path: %s", strerror(ENAMETOOLONG));
	} else {
		*resultp = strdup(buf);
	}
	if (!*resultp)
		zed_log_die("Failed to copy path: %s", strerror(ENOMEM));
}