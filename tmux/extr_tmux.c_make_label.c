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
typedef  scalar_t__ uid_t ;
struct stat {int st_mode; scalar_t__ st_uid; } ;

/* Variables and functions */
 scalar_t__ EACCES ; 
 scalar_t__ EEXIST ; 
 scalar_t__ ENOTDIR ; 
 scalar_t__ ERANGE ; 
 int PATH_MAX ; 
 int S_IRWXO ; 
 int /*<<< orphan*/  S_IRWXU ; 
 int /*<<< orphan*/  S_ISDIR (int) ; 
 int /*<<< orphan*/  _PATH_TMP ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 scalar_t__ getuid () ; 
 scalar_t__ lstat (char*,struct stat*) ; 
 scalar_t__ mkdir (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * realpath (char*,char*) ; 
 char const* strerror (scalar_t__) ; 
 int strlcpy (char*,char*,int) ; 
 int /*<<< orphan*/  xasprintf (char**,char*,char*,...) ; 

__attribute__((used)) static char *
make_label(const char *label, char **cause)
{
	char		*base, resolved[PATH_MAX], *path, *s;
	struct stat	 sb;
	uid_t		 uid;

	*cause = NULL;

	if (label == NULL)
		label = "default";
	uid = getuid();

	if ((s = getenv("TMUX_TMPDIR")) != NULL && *s != '\0')
		xasprintf(&base, "%s/tmux-%ld", s, (long)uid);
	else
		xasprintf(&base, "%s/tmux-%ld", _PATH_TMP, (long)uid);
	if (realpath(base, resolved) == NULL &&
	    strlcpy(resolved, base, sizeof resolved) >= sizeof resolved) {
		errno = ERANGE;
		free(base);
		goto fail;
	}
	free(base);

	if (mkdir(resolved, S_IRWXU) != 0 && errno != EEXIST)
		goto fail;
	if (lstat(resolved, &sb) != 0)
		goto fail;
	if (!S_ISDIR(sb.st_mode)) {
		errno = ENOTDIR;
		goto fail;
	}
	if (sb.st_uid != uid || (sb.st_mode & S_IRWXO) != 0) {
		errno = EACCES;
		goto fail;
	}
	xasprintf(&path, "%s/%s", resolved, label);
	return (path);

fail:
	xasprintf(cause, "error creating %s (%s)", resolved, strerror(errno));
	return (NULL);
}