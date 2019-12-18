#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* longest_int ;
typedef  int /*<<< orphan*/  line ;
struct TYPE_4__ {int mode; long fsize; char ftype; char* fname; int /*<<< orphan*/  perm; void* gid; void* uid; int /*<<< orphan*/  group; int /*<<< orphan*/  owner; int /*<<< orphan*/  ftime; } ;
typedef  TYPE_1__* MLstItemPtr ;
typedef  int /*<<< orphan*/  MLstItem ;

/* Variables and functions */
 scalar_t__ ISTREQ (char*,char*) ; 
 scalar_t__ ISTRNEQ (char*,char*,int) ; 
 char* SCANF_LONG_LONG ; 
 int /*<<< orphan*/  STRNCPY (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  UnMDTMDate (char*) ; 
 void* atoi (char*) ; 
 int /*<<< orphan*/  isspace (char) ; 
 int /*<<< orphan*/  kModTimeUnknown ; 
 long kSizeUnknown ; 
 int /*<<< orphan*/  memcpy (char*,char const* const,size_t) ; 
 int /*<<< orphan*/  memset (TYPE_1__* const,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sscanf (char*,char*,long*) ; 
 size_t strlen (char const* const) ; 
 scalar_t__ strtoq (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
UnMlsT(const char *const line0, const MLstItemPtr mlip)
{
	char *cp, *val, *fact;
	int ec;
	size_t len;
	char line[1024];

	memset(mlip, 0, sizeof(MLstItem));
	mlip->mode = -1;
	mlip->fsize = kSizeUnknown;
	mlip->ftype = '-';
	mlip->ftime = kModTimeUnknown;

	len = strlen(line0);
	if (len > (sizeof(line) - 1))
		return (-1);	/* Line too long, sorry. */
	/* This should be re-coded so does not need to make a
	 * copy of the buffer; it could be done in place.
	 */
	memcpy(line, line0, len + 1);

	/* Skip leading whitespace. */
	for (cp = line; *cp != '\0'; cp++) {
		if (! isspace(*cp))
			break;
	}

	while (*cp != '\0') {
		for (fact = cp; ; cp++) {
			if ((*cp == '\0') || (*cp == ' ')) {
				/* protocol violation */
				return (-1);
			}
			if (*cp == '=') {
				/* End of fact name. */
				*cp++ = '\0';
				break;
			}
		}
		for (val = cp; ; cp++) {
			if (*cp == '\0') {
				/* protocol violation */
				return (-1);
			}
			if (*cp == ' ') {
				ec = ' ';
				*cp++ = '\0';
				break;
			} else if (*cp == ';') {
				if (cp[1] == ' ') {
					ec = ' ';
					*cp++ = '\0';
					*cp++ = '\0';
				} else {
					ec = ';';
					*cp++ = '\0';
				}
				break;
			}
		}
		if (ISTRNEQ(fact, "OS.", 3))
			fact += 3;
		if (ISTREQ(fact, "type")) {
			if (ISTREQ(val, "file")) {
				mlip->ftype = '-';
			} else if (ISTREQ(val, "dir")) {
				mlip->ftype = 'd';
			} else if (ISTREQ(val, "cdir")) {
				/* not supported: current directory */
				return (-2);
			} else if (ISTREQ(val, "pdir")) {
				/* not supported: parent directory */
				return (-2);
			} else {
				/* ? */
				return (-1);
			}
		} else if (ISTREQ(fact, "UNIX.mode")) {
			if (val[0] == '0')
				sscanf(val, "%o", &mlip->mode);
			else
				sscanf(val, "%i", &mlip->mode);
			if (mlip->mode != (-1))
				mlip->mode &= 00777;
		} else if (ISTREQ(fact, "perm")) {
			STRNCPY(mlip->perm, val);
		} else if (ISTREQ(fact, "size")) {
#if defined(HAVE_LONG_LONG) && defined(SCANF_LONG_LONG)
			(void) sscanf(val, SCANF_LONG_LONG, &mlip->fsize);
#elif defined(HAVE_LONG_LONG) && defined(HAVE_STRTOQ)
			mlip->fsize = (longest_int) strtoq(val, NULL, 0);
#else
			{
				long fsize2 = 0L;

				(void) sscanf(val, "%ld", &fsize2);
				mlip->fsize = (longest_int) fsize2;
			}
#endif
		} else if (ISTREQ(fact, "modify")) {
			mlip->ftime = UnMDTMDate(val);
		} else if (ISTREQ(fact, "UNIX.owner")) {
			STRNCPY(mlip->owner, val);
		} else if (ISTREQ(fact, "UNIX.group")) {
			STRNCPY(mlip->group, val);
		} else if (ISTREQ(fact, "UNIX.uid")) {
			mlip->uid = atoi(val);
		} else if (ISTREQ(fact, "UNIX.gid")) {
			mlip->gid = atoi(val);
		} else if (ISTREQ(fact, "perm")) {
			STRNCPY(mlip->perm, val);
		}

		/* End of facts? */
		if (ec == ' ')
			break;
	}

	len = strlen(cp);
	if (len > (sizeof(mlip->fname) - 1)) {
		/* Filename too long */
		return (-1);
	}
	memcpy(mlip->fname, cp, len);

	/* also set linkto here if used */

	return (0);
}