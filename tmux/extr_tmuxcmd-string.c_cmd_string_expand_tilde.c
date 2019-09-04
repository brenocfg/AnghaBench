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
struct passwd {char* pw_dir; } ;
struct environ_entry {char* value; } ;

/* Variables and functions */
 int EOF ; 
 int cmd_string_getc (char const*,size_t*) ; 
 int /*<<< orphan*/  cmd_string_ungetc (size_t*) ; 
 struct environ_entry* environ_find (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 struct passwd* getpwnam (char*) ; 
 struct passwd* getpwuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getuid () ; 
 int /*<<< orphan*/  global_environ ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  xasprintf (char**,char*,char*,...) ; 
 char* xmalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
cmd_string_expand_tilde(const char *s, size_t *p)
{
	struct passwd		*pw;
	struct environ_entry	*envent;
	char			*home, *path, *user, *cp;
	int			 last;

	home = NULL;

	last = cmd_string_getc(s, p);
	if (last == EOF || last == '/' || last == ' '|| last == '\t') {
		envent = environ_find(global_environ, "HOME");
		if (envent != NULL && *envent->value != '\0')
			home = envent->value;
		else if ((pw = getpwuid(getuid())) != NULL)
			home = pw->pw_dir;
	} else {
		cmd_string_ungetc(p);

		cp = user = xmalloc(strlen(s));
		for (;;) {
			last = cmd_string_getc(s, p);
			if (last == EOF ||
			    last == '/' ||
			    last == ' '||
			    last == '\t')
				break;
			*cp++ = last;
		}
		*cp = '\0';

		if ((pw = getpwnam(user)) != NULL)
			home = pw->pw_dir;
		free(user);
	}

	if (home == NULL)
		return (NULL);

	if (last != EOF)
		xasprintf(&path, "%s%c", home, last);
	else
		xasprintf(&path, "%s", home);
	return (path);
}