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
struct _stat {int dummy; } ;
struct Stat {int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  s ;
typedef  int /*<<< orphan*/  mode_t ;
typedef  int /*<<< orphan*/  LPSECURITY_ATTRIBUTES ;

/* Variables and functions */
 int /*<<< orphan*/  CreateDirectory (char const* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENAMETOOLONG ; 
 int /*<<< orphan*/  ENOTDIR ; 
 int /*<<< orphan*/  F_OK ; 
 int /*<<< orphan*/  IsLocalPathDelim (char const) ; 
 scalar_t__ IsUNCPrefixed (char const* const) ; 
 char LOCAL_PATH_DELIM ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ Stat (char const* const,struct Stat*) ; 
 char* StrFindLocalPathDelim (char const* const) ; 
 char* StrRFindLocalPathDelim (char*) ; 
 int _access (char const* const,int) ; 
 scalar_t__ _stat (char const* const,struct Stat*) ; 
 int access (char const* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ isalpha (char const) ; 
 int mkdir (char const* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (char*,char const* const,int) ; 

int
MkDirs(const char *const newdir, int mode1)
{
	char s[512];
	int rc;
	char *cp, *sl;
#if defined(WIN32) || defined(_WINDOWS)
	struct _stat st;
	char *share;
#else
	struct Stat st;
	mode_t mode = (mode_t) mode1;
#endif

#if defined(WIN32) || defined(_WINDOWS)
	if ((isalpha(newdir[0])) && (newdir[1] == ':')) {
		if (! IsLocalPathDelim(newdir[2])) {
			/* Special case "c:blah", and errout.
			 * "c:\blah" must be used or _access GPFs.
			 */
			errno = EINVAL;
			return (-1);
		} else if (newdir[3] == '\0') {
			/* Special case root directory, which cannot be made. */
			return (0);
		}
	} else if (IsUNCPrefixed(newdir)) {
		share = StrFindLocalPathDelim(newdir + 2);
		if ((share == NULL) || (StrFindLocalPathDelim(share + 1) == NULL))
			return (-1);
	}

	if (_access(newdir, 00) == 0) {
		if (_stat(newdir, &st) < 0)
			return (-1);
		if (! S_ISDIR(st.st_mode)) {
			errno = ENOTDIR;
			return (-1);
		}
		return 0;
	}
#else
	if (access(newdir, F_OK) == 0) {
		if (Stat(newdir, &st) < 0)
			return (-1);
		if (! S_ISDIR(st.st_mode)) {
			errno = ENOTDIR;
			return (-1);
		}
		return 0;
	}
#endif

	(void) strncpy(s, newdir, sizeof(s));
	if (s[sizeof(s) - 1] != '\0') {
#ifdef ENAMETOOLONG
		errno = ENAMETOOLONG;
#else
		errno = EINVAL;
		return (-1);
#endif
	}

	cp = StrRFindLocalPathDelim(s);
	if (cp == NULL) {
#if defined(WIN32) || defined(_WINDOWS)
		if (! CreateDirectory(newdir, (LPSECURITY_ATTRIBUTES) 0))
			return (-1);
		return (0);
#else
		rc = mkdir(newdir, mode);
		return (rc);
#endif
	} else if (cp[1] == '\0') {
		/* Remove trailing slashes from path. */
		--cp;
		while (cp > s) {
			if (! IsLocalPathDelim(*cp))
				break;
			--cp;
		}
		cp[1] = '\0';
		cp = StrRFindLocalPathDelim(s);
		if (cp == NULL) {
#if defined(WIN32) || defined(_WINDOWS)
			if (! CreateDirectory(s, (LPSECURITY_ATTRIBUTES) 0))
				return (-1);
#else
			rc = mkdir(s, mode);
			return (rc);
#endif
		}
	}

	/* Find the deepest directory in this
	 * path that already exists.  When
	 * we do, we want to have the 's'
	 * string as it was originally, but
	 * with 'cp' pointing to the first
	 * slash in the path that starts the
	 * part that does not exist.
	 */
	sl = NULL;
	for (;;) {
		*cp = '\0';
#if defined(WIN32) || defined(_WINDOWS)
		rc = _access(s, 00);
#else
		rc = access(s, F_OK);
#endif
		if (sl != NULL)
			*sl = LOCAL_PATH_DELIM;
		if (rc == 0) {
			*cp = LOCAL_PATH_DELIM;
			break;
		}
		sl = cp;
		cp = StrRFindLocalPathDelim(s);
		if (cp == NULL) {
			/* We do not have any more
			 * slashes, so none of the
			 * new directory's components
			 * existed before, so we will
			 * have to make everything
			 * starting at the first node.
			 */
			if (sl != NULL)
				*sl = LOCAL_PATH_DELIM;

			/* We refer to cp + 1 below,
			 * so this is why we can
			 * set "cp" to point to the
			 * byte before the array starts.
			 */
			cp = s - 1;
			break;
		}
	}

	for (;;) {
		/* Extend the path we have to
		 * include the next component
		 * to make.
		 */
		sl = StrFindLocalPathDelim(cp + 1);
		if (sl == s) {
			/* If the next slash is pointing
			 * to the start of the string, then
			 * the path is an absolute path and
			 * we don't need to make the root node,
			 * and besides the next mkdir would
			 * try an empty string.
			 */
			++cp;
			sl = StrFindLocalPathDelim(cp + 1);
		}
		if (sl != NULL) {
			*sl = '\0';
		}
#if defined(WIN32) || defined(_WINDOWS)
		if (! CreateDirectory(s, (LPSECURITY_ATTRIBUTES) 0))
			return (-1);
#else
		rc = mkdir(s, mode);
		if (rc < 0)
			return rc;
#endif
		if (sl == NULL)
			break;
		*sl = LOCAL_PATH_DELIM;
		cp = sl;
	}
	return (0);
}