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
typedef  int /*<<< orphan*/  path ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 char* gl_home_dir ; 
 int /*<<< orphan*/  gl_set_home_dir (int /*<<< orphan*/ *) ; 
 int gl_vi_preferred ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/ * strstr (char*,char*) ; 

__attribute__((used)) static void
gl_check_inputrc_for_vi(void)
{
	FILE *fp;
	char path[256];

	/* If the user has a ~/.inputrc file,
	 * check it to see if it has a line like
	 * "set editing-mode vi".  If it does,
	 * we know that the user wants vi
	 * emulation rather than emacs.  If the
	 * file doesn't exist, it's no big
	 * deal since we can also check the
	 * $EDITOR environment variable.
	 */
	gl_set_home_dir(NULL);
	if (gl_home_dir == NULL)
		return;

#ifdef HAVE_SNPRINTF
	snprintf(path, sizeof(path), "%s/%s", gl_home_dir, ".inputrc");
#else
	if (sizeof(path) >= (strlen(gl_home_dir) + strlen("/.inputrc")))
		return;

	sprintf(path, "%s%s", gl_home_dir, "/.inputrc");
#endif

	fp = fopen(
		path,
#if defined(__windows__) || defined(MSDOS)
		"rt"
#else
		"r"
#endif
	);

	if (fp == NULL)
		return;

	while (fgets(path, sizeof(path) - 1, fp) != NULL) {
		if ((strstr(path, "editing-mode") != NULL) && (strstr(path, "vi") != NULL)) {
			gl_vi_preferred = 1;
			break;
		}
	}

	(void) fclose(fp);
}