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
typedef  int time_t ;
struct tm {int tm_isdst; scalar_t__ tm_mon; int tm_year; int tm_hour; void* tm_min; void* tm_mday; } ;
typedef  long longest_int ;

/* Variables and functions */
 char* SCANF_LONG_LONG ; 
 int /*<<< orphan*/  Strncat (char*,char*,size_t) ; 
 int /*<<< orphan*/  Strncpy (char*,char const* const,size_t) ; 
 void* atoi (char*) ; 
 scalar_t__ isdigit (char) ; 
 scalar_t__ ispunct (int) ; 
 int /*<<< orphan*/  isspace (char) ; 
 int /*<<< orphan*/  memmove (char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  memset (struct tm*,int /*<<< orphan*/ ,int) ; 
 int mktime (struct tm*) ; 
 int /*<<< orphan*/  sscanf (char*,char*,long*) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ strtoq (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
UnDosLine(	char *const line,
		const char *const curdir,
		size_t curdirlen,
		char *fname,
		size_t fnamesize,
		int *ftype,
		longest_int *fsize,
		time_t *ftime)
{
	char *cp;
	int hour, year;
	char *filestart;
	char *sizestart;
	struct tm ftm;

	/*
	 *
0123456789012345678901234567890123456789012345678901234567890123456789
04-27-99  10:32PM               270158 Game booklet.pdf
03-11-99  10:03PM       <DIR>          Get A3d Banner

We also try to parse the format from CMD.EXE, which is similar:

03/22/2001  06:23p              62,325 cls.pdf

	 *
	 */
	cp = line;
	if (
		isdigit((int) cp[0])
		&& isdigit((int) cp[1])
		&& ispunct((int) cp[2])
		&& isdigit((int) cp[3])
		&& isdigit((int) cp[4])
		&& ispunct((int) cp[5])
		&& isdigit((int) cp[6])
		&& isdigit((int) cp[7])
	) {
		(void) memset(&ftm, 0, sizeof(struct tm));
		ftm.tm_isdst = -1;
		cp[2] = '\0';
		ftm.tm_mon = atoi(cp + 0);
		if (ftm.tm_mon > 0)
			ftm.tm_mon -= 1;
		cp[5] = '\0';
		ftm.tm_mday = atoi(cp + 3);
		if ((isdigit((int) cp[8])) && (isdigit((int) cp[9]))) {
			/* Four-digit year */
			cp[10] = '\0';
			year = atoi(cp + 6);
			if (year > 1900)
				year -= 1900;
			ftm.tm_year = year;	/* years since 1900 */
			cp += 11;
		} else {
			/* Two-digit year */
			cp[8] = '\0';
			year = atoi(cp + 6);
			if (year < 98)
				year += 100;
			ftm.tm_year = year;	/* years since 1900 */
			cp += 9;
		}

		for (;;) {
			if (*cp == '\0')
				return (-1);
			if (isdigit(*cp))
				break;
			cp++;
		}

		cp[2] = '\0';
		hour = atoi(cp);
		if (((cp[5] == 'P') || (cp[5] == 'p')) && (hour < 12))
			hour += 12;
		else if (((cp[5] == 'A') || (cp[5] == 'a')) && (hour == 12))
			hour -= 12;
		ftm.tm_hour = hour;
		cp[5] = '\0';
		ftm.tm_min = atoi(cp + 3);
		*ftime = mktime(&ftm);
		if (*ftype == (time_t) -1)
			return (-1);

		cp += 6;
		*ftype = '-';
		for (;;) {
			if (*cp == '\0')
				return (-1);
			if ((*cp == '<') && (cp[1] == 'D')) {
				/* found <DIR> */
				*ftype = 'd';
				cp += 5;
				break;	/* size field will end up being empty string */
			} else if ((*cp == '<') && (cp[1] == 'J')) {
				/* found <JUNCTION>
				 *
				 * Will we ever really see this?
				 * IIS from Win2000sp1 sends <DIR>
				 * for FTP, but CMD.EXE prints
				 * <JUNCTION>.
				 */
				*ftype = 'd';
				cp += 10;
				break;
			} else if (isdigit(*cp)) {
				break;
			} else {
				cp++;
			}
		}

		sizestart = cp;
		for (;;) {
			if (*cp == '\0')
				return (-1);
#ifdef HAVE_MEMMOVE
			if (*cp == ',') {
				/* Yuck -- US Locale dependency */
				memmove(cp, cp + 1, strlen(cp + 1) + 1);
			}
#endif
			if (!isdigit(*cp)) {
				*cp++ = '\0';
				break;
			}
			cp++;
		}

		if (fsize != NULL) {
#if defined(HAVE_LONG_LONG) && defined(SCANF_LONG_LONG)
			if (*ftype == 'd')
				*fsize = 0;
			else
				(void) sscanf(sizestart, SCANF_LONG_LONG, fsize);
#elif defined(HAVE_LONG_LONG) && defined(HAVE_STRTOQ)
			if (*ftype == 'd')
				*fsize = 0;
			else
				*fsize = (longest_int) strtoq(sizestart, NULL, 0);
#else
			*fsize = (longest_int) 0;
			if (*ftype != 'd') {
				long fsize2 = 0L;

				(void) sscanf(sizestart, "%ld", &fsize2);
				*fsize = (longest_int) fsize2;
			}
#endif
		}

		for (;;) {
			if (*cp == '\0')
				return (-1);
			if (!isspace(*cp)) {
				break;
			}
			cp++;
		}

		filestart = cp;
		if (curdirlen == 0) {
			(void) Strncpy(fname, filestart, fnamesize);
		} else {
			(void) Strncpy(fname, curdir, fnamesize);
			(void) Strncat(fname, filestart, fnamesize);
		}

		return (0);
	}
	return (-1);
}