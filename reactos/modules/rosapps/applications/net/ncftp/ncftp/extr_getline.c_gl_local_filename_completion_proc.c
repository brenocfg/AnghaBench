#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ffd ;
struct TYPE_5__ {char* cFileName; int dwFileAttributes; } ;
typedef  TYPE_1__ WIN32_FIND_DATA ;
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_NO_MORE_FILES ; 
 int FILE_ATTRIBUTE_DIRECTORY ; 
 int /*<<< orphan*/  FindClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * FindFirstFile (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  FindNextFile (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/ * INVALID_HANDLE_VALUE ; 
 scalar_t__ IsLocalPathDelim (char) ; 
 char LOCAL_PATH_DELIM ; 
 char* LOCAL_PATH_DELIM_STR ; 
 char* _StrRFindLocalPathDelim (char const*) ; 
 scalar_t__ _strnicmp (char const*,char const*,size_t) ; 
 int /*<<< orphan*/  free (char*) ; 
 char gl_completion_exact_match_extra_char ; 
 char* gl_home_dir ; 
 char** gl_matchlist ; 
 int /*<<< orphan*/  gl_set_home_dir (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  memmove (char*,char*,size_t) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ realloc (char*,size_t) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int strlen (char const*) ; 

char *
gl_local_filename_completion_proc(const char *start, int idx)
{
	static HANDLE searchHandle = NULL;
	static int filepfxoffset;
	static size_t filepfxlen;

	WIN32_FIND_DATA ffd;
	DWORD dwErr;
	char *cp, *c2, ch;
	const char *filepfx;
	const char *dirtoopen, *name;
	char *dirtoopen1, *dirtoopen2;
	size_t len, len2;

	if (idx == 0) {
		if (searchHandle != NULL) {
			/* shouldn't get here! */
			FindClose(searchHandle);
			searchHandle = NULL;
		}
	}


	if (searchHandle == NULL) {
		dirtoopen1 = NULL;
		dirtoopen2 = NULL;
		cp = _StrRFindLocalPathDelim(start);
		if (cp == start) {
			dirtoopen = LOCAL_PATH_DELIM_STR;	/* root dir */
			filepfxoffset = 1;
		} else if (cp == NULL) {
			dirtoopen = ".";
			filepfxoffset = 0;
		} else {
			len = strlen(start) + 1;
			dirtoopen1 = (char *) malloc(len);
			if (dirtoopen1 == NULL)
				return NULL;
			memcpy(dirtoopen1, start, len);
			len = (cp - start);
			dirtoopen1[len] = '\0';
			dirtoopen = dirtoopen1;
			filepfxoffset = (int) ((cp + 1) - start);
		}

		if (strcmp(dirtoopen, "~") == 0) {
			if (gl_home_dir == NULL)
				gl_set_home_dir(NULL);
			if (gl_home_dir == NULL)
				return (NULL);
			dirtoopen = gl_home_dir;
		}

		len = strlen(dirtoopen);
		dirtoopen2 = (char *) malloc(len + 8);
		if (dirtoopen2 == NULL) {
			if (dirtoopen1 != NULL)
				free(dirtoopen1);
			return NULL;
		}

		memcpy(dirtoopen2, dirtoopen, len + 1);
		if (dirtoopen2[len - 1] == LOCAL_PATH_DELIM)
			memcpy(dirtoopen2 + len, "*.*", (size_t) 4);
		else
			memcpy(dirtoopen2 + len, "\\*.*", (size_t) 5);

		/* "Open" the directory. */
		memset(&ffd, 0, sizeof(ffd));
		searchHandle = FindFirstFile(dirtoopen2, &ffd);

		free(dirtoopen2);
		if (dirtoopen1 != NULL)
			free(dirtoopen1);

		if (searchHandle == INVALID_HANDLE_VALUE) {
			return NULL;
		}

		filepfx = start + filepfxoffset;
		filepfxlen = strlen(filepfx);
	} else {
		/* assumes "start" is same for each iteration. */
		filepfx = start + filepfxoffset;
		goto next;
	}

	for (;;) {

		name = ffd.cFileName;
		if ((name[0] == '.') && ((name[1] == '\0') || ((name[1] == '.') && (name[2] == '\0'))))
			goto next;	/* Skip . and .. */

		if ((filepfxlen == 0) || (_strnicmp(name, filepfx, filepfxlen) == 0)) {
			/* match */
			len = strlen(name);
			cp = (char *) malloc(filepfxoffset + len + 4 /* spare */ + 1 /* NUL */);
			*cp = '\0';
			if (filepfxoffset > 0)
				memcpy(cp, start, filepfxoffset);
			memcpy(cp + filepfxoffset, name, len + 1);
			if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				/* Embed file type with name. */
				c2 = cp + filepfxoffset + len + 1;
				*c2++ = '\0';
				*c2++ = 'd';
				*c2 = '\0';
			} else {
				c2 = cp + filepfxoffset + len + 1;
				*c2++ = '\0';
				*c2++ = '-';
				*c2 = '\0';
			}
			return (cp);
		}

next:
		if (!FindNextFile(searchHandle, &ffd)) {
			dwErr = GetLastError();
			if (dwErr != ERROR_NO_MORE_FILES) {
				FindClose(searchHandle);
				searchHandle = NULL;
				return NULL;
			}

			/* no more items */
			FindClose(searchHandle);
			searchHandle = NULL;

			if (idx == 1) {
				/* There was exactly one match.
				 * In this special case, we
				 * want to append a \ instead
				 * of a space.
				 */
				cp = gl_matchlist[0];
				ch = (char) cp[strlen(cp) + 2];
				if (ch == (char) 'd')
					gl_completion_exact_match_extra_char = LOCAL_PATH_DELIM;

				if ((cp[0] == '~') && ((cp[1] == '\0') || (IsLocalPathDelim(cp[1])))) {
					len = strlen(cp + 1) + /* NUL */ 1;
					len2 = strlen(gl_home_dir);
					if (IsLocalPathDelim(gl_home_dir[len2 - 1]))
						len2--;
					cp = (char *) realloc(gl_matchlist[0], len + len2 + 4);
					if (cp == NULL) {
						cp = gl_matchlist[0];
					} else {
						memmove(cp + len2, cp + 1, len);
						memcpy(cp, gl_home_dir, len2);
						c2 = cp + len + len2;
						*c2++ = '\0';
						*c2++ = ch;
						*c2 = '\0';
						gl_matchlist[0] = cp;
					}
				}
			}
			break;
		}
	}
	return (NULL);
}