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
typedef  int /*<<< orphan*/  wdir ;
struct passwd {char* pw_dir; } ;

/* Variables and functions */
 int GetWindowsDirectory (char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 scalar_t__ getlogin () ; 
 struct passwd* getpwnam (char*) ; 
 struct passwd* getpwuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getuid () ; 
 char* gl_home_dir ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

void
gl_set_home_dir(const char *homedir)
{
	size_t len;
#ifdef __windows__
	const char *homedrive, *homepath;
	char wdir[64];
#else
	struct passwd *pw;
	char *cp;
#endif

	if (gl_home_dir != NULL) {
		free(gl_home_dir);
		gl_home_dir = NULL;
	}

	if (homedir == NULL) {
#ifdef __windows__
		homedrive = getenv("HOMEDRIVE");
		homepath = getenv("HOMEPATH");
		if ((homedrive != NULL) && (homepath != NULL)) {
			len = strlen(homedrive) + strlen(homepath) + 1;
			gl_home_dir = (char *) malloc(len);
			if (gl_home_dir != NULL) {
				strcpy(gl_home_dir, homedrive);
				strcat(gl_home_dir, homepath);
				return;
			}
		}

		wdir[0] = '\0';
		if (GetWindowsDirectory(wdir, sizeof(wdir) - 1) < 1)
			(void) strncpy(wdir, ".", sizeof(wdir));
		else if (wdir[1] == ':') {
			wdir[2] = '\\';
			wdir[3] = '\0';
		}
		homedir = wdir;
#else
		cp = (char *) getlogin();
		if (cp == NULL) {
			cp = (char *) getenv("LOGNAME");
			if (cp == NULL)
				cp = (char *) getenv("USER");
		}
		pw = NULL;
		if (cp != NULL)
			pw = getpwnam(cp);
		if (pw == NULL)
			pw = getpwuid(getuid());
		if (pw == NULL)
			return;	/* hell with it */
		homedir = pw->pw_dir;
#endif
	}

	len = strlen(homedir) + /* NUL */ 1;
	gl_home_dir = (char *) malloc(len);
	if (gl_home_dir != NULL) {
		memcpy(gl_home_dir, homedir, len);
	}
}