#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  og ;
typedef  scalar_t__ longest_int ;
struct TYPE_16__ {size_t relnameLen; char type; int /*<<< orphan*/ * plug; scalar_t__ size; int /*<<< orphan*/  mdtm; int /*<<< orphan*/ * rlinkto; int /*<<< orphan*/ * lname; int /*<<< orphan*/ * rname; int /*<<< orphan*/ * relname; } ;
struct TYPE_15__ {size_t maxFileLen; size_t maxPlugLen; } ;
struct TYPE_14__ {TYPE_2__* first; } ;
struct TYPE_13__ {int /*<<< orphan*/  line; struct TYPE_13__* next; } ;
struct TYPE_12__ {char* fname; char* linkto; char ftype; int mode; char* perm; char* owner; char* group; scalar_t__ fsize; int /*<<< orphan*/  ftime; } ;
typedef  TYPE_1__ MLstItem ;
typedef  TYPE_2__* LinePtr ;
typedef  TYPE_3__* LineListPtr ;
typedef  TYPE_4__* FileInfoListPtr ;
typedef  TYPE_5__ FileInfo ;

/* Variables and functions */
 int /*<<< orphan*/  AddFileInfo (TYPE_4__*,TYPE_5__*) ; 
 int /*<<< orphan*/  InitFileInfoList (TYPE_4__*) ; 
 int /*<<< orphan*/  STRNCAT (char*,char*) ; 
 int /*<<< orphan*/ * StrDup (char*) ; 
 int UnMlsT (int /*<<< orphan*/ ,TYPE_1__*) ; 
 char** rwx ; 
 int /*<<< orphan*/  snprintf (char*,int,char*) ; 
 char* sprintf (char*,char*,char const*,char const*,...) ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 
 size_t strlen (char*) ; 

int
UnMlsD(FileInfoListPtr filp, LineListPtr llp)
{
	MLstItem mli;
	char plug[64];
	char og[32];
	int rc;
	LinePtr lp;
	FileInfo fi;
	int linesread = 0;
	int linesconverted = 0;
	int linesignored = 0;
	size_t maxFileLen = 0;
	size_t maxPlugLen = 0;
	size_t fileLen, plugLen;
	int m1, m2, m3;
	const char *cm1, *cm2, *cm3;

	InitFileInfoList(filp);
	for (lp = llp->first; lp != NULL; lp = lp->next) {
		linesread++;
		rc = UnMlsT(lp->line, &mli);
		if (rc == 0) {
			linesconverted++;
			fileLen = strlen(mli.fname);
			if (fileLen > maxFileLen)
				maxFileLen = fileLen;
			fi.relnameLen = fileLen;
			fi.relname = StrDup(mli.fname);
			fi.rname = NULL;
			fi.lname = NULL;
			fi.rlinkto = (mli.linkto[0] == '\0') ? NULL : StrDup(mli.linkto);
			fi.mdtm = mli.ftime;
			fi.size = (longest_int) mli.fsize;
			fi.type = mli.ftype;
			plug[0] = (char) mli.ftype;
			plug[1] = '\0';
			m1 = 0;
			m2 = 0;
			m3 = -1;
			if (mli.mode != (-1)) {
				m1 = (mli.mode & 00700) >> 6;
				m2 = (mli.mode & 00070) >> 3;
				m3 = (mli.mode & 00007);
			}
			if (mli.perm[0] != '\0') {
				m3 = 0;
				if (fi.type == 'd') {
					if (strchr(mli.perm, 'e') != NULL) {
						/* execute -> execute */
						m3 |= 00001;
					}
					if (strchr(mli.perm, 'c') != NULL) {
						/* create -> write */
						m3 |= 00002;
					}
					if (strchr(mli.perm, 'l') != NULL) {
						/* list -> read */
						m3 |= 00004;
					}
				} else {
					if (strchr(mli.perm, 'w') != NULL) {
						/* write -> write */
						m3 |= 00002;
					}
					if (strchr(mli.perm, 'r') != NULL) {
						/* read -> read */
						m3 |= 00004;
					}
				}
			}
			if (m3 != (-1)) {
				cm1 = rwx[m1];
				cm2 = rwx[m2];
				cm3 = rwx[m3];
				sprintf(plug + 1, "%s%s%s", cm1, cm2, cm3);
			}
			if (mli.owner[0] != '\0') {
				if (mli.group[0] != '\0') {
#ifdef HAVE_SNPRINTF
					snprintf(og, sizeof(og) - 1,
#else
					sprintf(og,
#endif	/* HAVE_SNPRINTF */
						"   %-8.8s %s",
						mli.owner, mli.group
					);
					STRNCAT(plug, og);
				} else {
					STRNCAT(plug, "   ");
					STRNCAT(plug, mli.owner);
				}
			}
			fi.plug = StrDup(plug);
			if (fi.plug != NULL) {
				plugLen = strlen(plug);
				if (plugLen > maxPlugLen)
					maxPlugLen = plugLen;
			}
			(void) AddFileInfo(filp, &fi);
		} else if (rc == (-2)) {
			linesignored++;
		}
	}

	filp->maxFileLen = maxFileLen;
	filp->maxPlugLen = maxPlugLen;
	if (linesread == 0)
		return (0);
	linesconverted += linesignored;
	return ((linesconverted > 0) ? linesconverted : (-1));
}