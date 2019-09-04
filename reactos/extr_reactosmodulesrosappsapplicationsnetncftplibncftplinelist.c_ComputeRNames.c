#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* first; } ;
struct TYPE_4__ {char* relname; char* lname; char* rname; struct TYPE_4__* next; } ;
typedef  TYPE_1__* FileInfoPtr ;
typedef  TYPE_2__* FileInfoListPtr ;

/* Variables and functions */
 int /*<<< orphan*/ * Dynscat (char**,char const*,char*,...) ; 
 int /*<<< orphan*/  LocalPathToTVFSPath (char*) ; 
 int /*<<< orphan*/  TVFSPathToLocalPath (char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 char* strrchr (char const*,char) ; 

int
ComputeRNames(FileInfoListPtr dst, const char *dstdir, int pflag, int nochop)
{
	FileInfoPtr lp, lp2;
	char *buf;
	char *cp;

	if (dstdir == NULL)
		dstdir = ".";

	for (lp = dst->first; lp != NULL; lp = lp2) {
		lp2 = lp->next;

		buf = NULL;
		if (nochop != 0) {
			if ((dstdir[0] != '\0') && (strcmp(dstdir, "."))) {
				if (Dynscat(&buf, dstdir, "/", lp->relname, 0) == NULL)
					goto memerr;

				if (pflag != 0) {
					/* Init lname to parent dir name of remote dir */
					cp = strrchr(dstdir, '/');
					if (cp == NULL)
						cp = strrchr(dstdir, '\\');
					if (cp != NULL) {
						if (Dynscat(&lp->lname, cp + 1, 0) == NULL)
							goto memerr;
						TVFSPathToLocalPath(lp->lname);
					}
				}
			} else {
				if (Dynscat(&buf, lp->relname, 0) == NULL)
					goto memerr;
			}
		} else {
			if ((dstdir[0] != '\0') && (strcmp(dstdir, "."))) {
				cp = strrchr(lp->relname, '/');
				if (cp == NULL)
					cp = strrchr(lp->relname, '\\');
				if (cp != NULL) {
					cp++;
				} else {
					cp = lp->relname;
				}
				if (Dynscat(&buf, dstdir, "/", cp, 0) == NULL)
					goto memerr;

				if (pflag != 0) {
					/* Init lname to parent dir name of remote dir */
					cp = strrchr(dstdir, '/');
					if (cp == NULL)
						cp = strrchr(dstdir, '\\');
					if (cp != NULL) {
						if (Dynscat(&lp->lname, cp + 1, 0) == NULL)
							goto memerr;
						TVFSPathToLocalPath(lp->lname);
					}
				}
			} else {
				cp = strrchr(lp->relname, '/');
				if (cp == NULL)
					cp = strrchr(lp->relname, '\\');
				if (cp != NULL) {
					cp++;
				} else {
					cp = lp->relname;
				}
				if (Dynscat(&buf, cp, 0) == NULL)
					goto memerr;
			}
		}
		lp->rname = buf;
		if (lp->rname == NULL) {
memerr:
			return (-1);
		}
		LocalPathToTVFSPath(lp->rname);
	}
	return (0);
}