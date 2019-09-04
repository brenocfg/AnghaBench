#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
struct tm {int tm_year; } ;
typedef  scalar_t__ longest_int ;
typedef  int /*<<< orphan*/  linkto ;
typedef  int /*<<< orphan*/  fname ;
struct TYPE_13__ {size_t relnameLen; int type; char* plug; scalar_t__ size; int /*<<< orphan*/  mdtm; int /*<<< orphan*/ * rlinkto; int /*<<< orphan*/ * lname; int /*<<< orphan*/ * rname; int /*<<< orphan*/ * relname; } ;
struct TYPE_12__ {size_t maxFileLen; size_t maxPlugLen; } ;
struct TYPE_11__ {TYPE_1__* first; } ;
struct TYPE_10__ {int /*<<< orphan*/  line; struct TYPE_10__* next; } ;
typedef  TYPE_1__* LinePtr ;
typedef  TYPE_2__* LineListPtr ;
typedef  TYPE_3__* FileInfoListPtr ;
typedef  TYPE_4__ FileInfo ;

/* Variables and functions */
 int /*<<< orphan*/  AddFileInfo (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  InitFileInfoList (TYPE_3__*) ; 
 char* STRNCPY (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * StrDup (char*) ; 
 int UnDosLine (char*,char*,size_t,char*,int,int*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int UnLslRLine (char*,char*,size_t,char*,int,char*,int,int*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  isspace (int) ; 
 int kServerTypeMicrosoftFTP ; 
 struct tm* localtime (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 size_t strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

int
UnLslR(FileInfoListPtr filp, LineListPtr llp, int serverType)
{
	char curdir[256];
	char line[256];
	int hadblankline = 0;
	int len;
	size_t curdirlen = 0;
	char fname[256];
	char linkto[256];
	char *cp;
	longest_int fsize;
	int ftype;
	time_t ftime, now;
	int thisyear;
	struct tm *nowtm;
	int rc;
	LinePtr lp;
	FileInfo fi;
	int linesread = 0;
	int linesconverted = 0;
	size_t maxFileLen = 0;
	size_t maxPlugLen = 0;
	size_t fileLen;
	int plugend;

	(void) time(&now);
	nowtm = localtime(&now);
	if (nowtm == NULL)
		thisyear = 1970;	/* should never happen */
	else
		thisyear = nowtm->tm_year + 1900;

	curdir[0] = '\0';

	InitFileInfoList(filp);
	for (lp = llp->first; lp != NULL; lp = lp->next) {
		len = (int) strlen(STRNCPY(line, lp->line));
		if ((line[0] == 't') && (strncmp(line, "total", 5) == 0)) {
			/* total XX line? */
			if (line[len - 1] != ':') {
				hadblankline = 0;
				continue;
			}
			/* else it was a subdir named total */
		} else {
			for (cp = line; ; cp++) {
				if ((*cp == '\0') || (!isspace((int) *cp)))
					break;
			}
			if (*cp == '\0') {
				/* Entire line was blank. */
				/* separator line between dirs */
				hadblankline = 1;
				continue;
			}
		}

		if ((hadblankline != 0) && (line[len - 1] == ':')) {
			/* newdir */
			hadblankline = 0;
			if ((line[0] == '.') && (line[1] == '/')) {
				line[len - 1] = '/';
				(void) memcpy(curdir, line + 2, (size_t) len + 1 - 2);
				curdirlen = (size_t) (len - 2);
			} else if ((line[0] == '.') && (line[1] == '\\')) {
				line[len - 1] = '\\';
				(void) memcpy(curdir, line + 2, (size_t) len + 1 - 2);
				curdirlen = (size_t) (len - 2);
			} else {
				line[len - 1] = '/';
				(void) memcpy(curdir, line, (size_t) len + 1);
				curdirlen = (size_t) len;
			}
			continue;
		}

		linesread++;
		rc = UnLslRLine(line, curdir, curdirlen, fname, sizeof(fname), linkto, sizeof(linkto), &ftype, &fsize, &ftime, now, thisyear, &plugend);
		if ((rc < 0) && (serverType == kServerTypeMicrosoftFTP)) {
			rc = UnDosLine(line, curdir, curdirlen, fname, sizeof(fname), &ftype, &fsize, &ftime);
			if (rc == 0) {
				*linkto = '\0';
				plugend = 0;
			}
		}
		if (rc == 0) {
			linesconverted++;
			fileLen = strlen(fname);
			if (fileLen > maxFileLen)
				maxFileLen = fileLen;
			fi.relnameLen = fileLen;
			fi.relname = StrDup(fname);
			fi.rname = NULL;
			fi.lname = NULL;
			fi.rlinkto = (linkto[0] == '\0') ? NULL : StrDup(linkto);
			fi.mdtm = ftime;
			fi.size = (longest_int) fsize;
			fi.type = ftype;
			if (plugend > 0) {
				fi.plug = (char *) malloc((size_t) plugend + 1);
				if (fi.plug != NULL) {
					(void) memcpy(fi.plug, line, (size_t) plugend);
					fi.plug[plugend] = '\0';
					if ((size_t) plugend > maxPlugLen)
						maxPlugLen = (size_t) plugend;
				}
			} else {
				fi.plug = (char *) malloc(32);
				if (fi.plug != NULL) {
					strcpy(fi.plug, "----------   1 ftpuser  ftpusers");
					fi.plug[0] = (char) ftype;
					if (30 > maxPlugLen)
						maxPlugLen = (size_t) 30;
				}
			}
			(void) AddFileInfo(filp, &fi);
		}

		hadblankline = 0;
	}

	filp->maxFileLen = maxFileLen;
	filp->maxPlugLen = maxPlugLen;
	if (linesread == 0)
		return (0);
	return ((linesconverted > 0) ? linesconverted : (-1));
}