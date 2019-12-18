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
typedef  char wchar_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 char* calloc (size_t,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char*) ; 
 size_t mbstowcs (char*,char*,size_t) ; 
 char* strdup (char const*) ; 
 size_t strlen (char*) ; 
 size_t wcstombs (char*,char*,size_t) ; 

__attribute__((used)) static char *
simplify(const char *str)
{
	int i;
	size_t mbPathlen;	/* length of multi-byte path */
	size_t wcPathlen;	/* length of wide-character path */
	wchar_t *wptr;		/* scratch pointer */
	wchar_t *wcPath;	/* wide-character version of the path */
	char *mbPath;		/* The copy fo the path to be returned */

	/*
	 *  bail out if there is nothing there.
	 */

	if (!str) {
		errno = ENOENT;
		return (NULL);
	}

	/*
	 *  Get a copy of the argument.
	 */

	if ((mbPath = strdup(str)) == NULL) {
		return (NULL);
	}

	/*
	 *  convert the multi-byte version of the path to a
	 *  wide-character rendering, for doing our figuring.
	 */

	mbPathlen = strlen(mbPath);

	if ((wcPath = calloc(mbPathlen+1, sizeof (wchar_t))) == NULL) {
		free(mbPath);
		return (NULL);
	}

	if ((wcPathlen = mbstowcs(wcPath, mbPath, mbPathlen)) == (size_t)-1) {
		free(mbPath);
		free(wcPath);
		return (NULL);
	}

	/*
	 *  remove duplicate slashes first ("//../" -> "/")
	 */

	for (wptr = wcPath, i = 0; i < wcPathlen; i++) {
		*wptr++ = wcPath[i];

		if (wcPath[i] == '/') {
			i++;

			while (wcPath[i] == '/') {
				i++;
			}

			i--;
		}
	}

	*wptr = '\0';

	/*
	 *  now convert back to the multi-byte format.
	 */

	if (wcstombs(mbPath, wcPath, mbPathlen) == (size_t)-1) {
		free(mbPath);
		free(wcPath);
		return (NULL);
	}

	free(wcPath);
	return (mbPath);
}