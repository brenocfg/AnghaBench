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
typedef  char* string ;
typedef  int /*<<< orphan*/  hdir ;

/* Variables and functions */
 int /*<<< orphan*/  GetHomeDir (char*,int) ; 
 scalar_t__ IsLocalPathDelim (char) ; 
 char* LOCAL_PATH_DELIM_STR ; 
 int /*<<< orphan*/  STRNCPY (char*,char*) ; 
 char* StrFindLocalPathDelim (char*) ; 
 int /*<<< orphan*/  Strncat (char*,char*,size_t) ; 
 int /*<<< orphan*/  Strncpy (char*,char*,size_t) ; 
 struct passwd* getpwnam (char*) ; 
 scalar_t__ isalnum (int) ; 

__attribute__((used)) static void
ExpandTilde(char *pattern, size_t siz)
{
	string pat;
	char *cp, *rest, *firstent;
#if defined(WIN32) || defined(_WINDOWS)
#else
	struct passwd *pw;
#endif
	string hdir;

	if ((pattern[0] == '~') &&
	(isalnum((int) pattern[1]) || IsLocalPathDelim(pattern[1]) || (pattern[1] == '\0'))) {
		(void) STRNCPY(pat, pattern);
		if ((cp = StrFindLocalPathDelim(pat)) != NULL) {
			*cp = 0;
			rest = cp + 1;	/* Remember stuff after the ~/ part. */
		} else {
			rest = NULL;	/* Was just a ~ or ~username.  */
		}
		if (pat[1] == '\0') {
			/* Was just a ~ or ~/rest type.  */
			GetHomeDir(hdir, sizeof(hdir));
			firstent = hdir;
		} else {
#if defined(WIN32) || defined(_WINDOWS)
			return;
#else
			/* Was just a ~username or ~username/rest type.  */
			pw = getpwnam(pat + 1);
			if (pw != NULL)
				firstent = pw->pw_dir;
			else
				return;		/* Bad user -- leave it alone. */
#endif
		}

		(void) Strncpy(pattern, firstent, siz);
		if (rest != NULL) {
			(void) Strncat(pattern, LOCAL_PATH_DELIM_STR, siz);
			(void) Strncat(pattern, rest, siz);
		}
	}
}