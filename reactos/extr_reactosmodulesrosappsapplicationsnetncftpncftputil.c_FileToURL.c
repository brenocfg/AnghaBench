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

/* Variables and functions */
 int /*<<< orphan*/  PathCat (char*,size_t,char const* const,char const* const) ; 
 int /*<<< orphan*/  Strncat (char*,char const* const,size_t) ; 
 int /*<<< orphan*/  Strncpy (char*,char*,size_t) ; 
 int /*<<< orphan*/  memmove (char*,char*,size_t) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 
 scalar_t__ strcmp (char const* const,char*) ; 
 size_t strlen (char const* const) ; 
 scalar_t__ strncmp (char*,char const* const,size_t) ; 

char *
FileToURL(char *url, size_t urlsize, const char *const fn, const char *const rcwd, const char *const startdir, const char *const user, const char *const pass, const char *const hname, const unsigned int port)
{
	size_t ulen, dsize;
	char *dst, pbuf[32];
	int isUser;

	/* //<user>:<password>@<host>:<port>/<url-path> */
	/* Note that if an absolute path is given,
	 * you need to escape the first entry, i.e. /pub -> %2Fpub
	 */
	(void) Strncpy(url, "ftp://", urlsize);
	isUser = 0;
	if ((user != NULL) && (user[0] != '\0') && (strcmp(user, "anonymous") != 0) && (strcmp(user, "ftp") != 0)) {
		isUser = 1;
		(void) Strncat(url, user, urlsize);
		if ((pass != NULL) && (pass[0] != '\0')) {
			(void) Strncat(url, ":", urlsize);
			(void) Strncat(url, "PASSWORD", urlsize);
		}
		(void) Strncat(url, "@", urlsize);
	}
	(void) Strncat(url, hname, urlsize);
	if ((port != 21) && (port != 0)) {
		(void) sprintf(pbuf, ":%u", (unsigned int) port);
		(void) Strncat(url, pbuf, urlsize);
	}

	ulen = strlen(url);
	dst = url + ulen;
	dsize = urlsize - ulen;
	PathCat(dst, dsize, rcwd, fn);
	if ((startdir != NULL) && (startdir[0] != '\0') && (startdir[1] /* i.e. not "/" */ != '\0')) {
		if (strncmp(dst, startdir, strlen(startdir)) == 0) {
			/* Form relative URL. */
			memmove(dst, dst + strlen(startdir), strlen(dst) - strlen(startdir) + 1);
		} else if (isUser != 0) {
			/* Absolute URL, but different from start dir.
			 * Make sure to use %2f as first slash so that
			 * the translation uses "/pub" instead of "pub"
			 * since the / characters are just delimiters.
			 */
			dst[dsize - 1] = '\0';
			dst[dsize - 2] = '\0';
			dst[dsize - 3] = '\0';
			dst[dsize - 4] = '\0';
			memmove(dst + 4, dst + 1, strlen(dst + 1));
			dst[0] = '/';
			dst[1] = '%';
			dst[2] = '2';
			dst[3] = 'F';
		}
	}

	return (url);
}