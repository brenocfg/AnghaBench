#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dirent {char* d_name; } ;
struct Stat {int /*<<< orphan*/  st_mode; scalar_t__ st_size; int /*<<< orphan*/  st_mtime; } ;
typedef  int /*<<< orphan*/  mode_t ;
typedef  void* longest_int ;
struct TYPE_3__ {char type; int /*<<< orphan*/ * rlinkto; int /*<<< orphan*/ * plug; void* size; int /*<<< orphan*/  mdtm; void* lname; int /*<<< orphan*/ * rname; void* relname; } ;
typedef  int /*<<< orphan*/  FileInfoListPtr ;
typedef  TYPE_1__ FileInfo ;
typedef  int /*<<< orphan*/  FTPCIPtr ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  AddFileInfo (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  Error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ Lstat (char*,struct Stat*) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 void* StrDup (char*) ; 
 int /*<<< orphan*/ * calloc (int,int) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kDoPerror ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 scalar_t__ readlink (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static void
Traverse(FTPCIPtr cip, char *fullpath, struct Stat *st, char *relpath, FileInfoListPtr filp)
{
	char *dname;
	struct dirent *dirp;
	mode_t m;
	DIR *dp;
	char *cp;
	char *c2;
	FileInfo fi;

	if (relpath[0] != '\0') {
		fi.relname = StrDup(relpath);
		fi.rname = NULL;
		fi.lname = StrDup(fullpath);
		fi.rlinkto = NULL;
		fi.plug = NULL;
		fi.mdtm = st->st_mtime;
		fi.size = (longest_int) st->st_size;
		fi.type = 'd';
		(void) AddFileInfo(filp, &fi);
	}

	/* Handle directory entry first. */
	cp = fullpath + strlen(fullpath);
	*cp++ = '/';
	*cp = '\0';

	c2 = relpath + strlen(relpath);
	*c2++ = '/';
	*c2 = '\0';

	if ((dp = opendir(fullpath)) == NULL) {
		cp[-1] = '\0';
		c2[-1] = '\0';
		Error(cip, kDoPerror, "could not opendir %s.\n", fullpath);
		return;
	}

	while ((dirp = readdir(dp)) != NULL) {
		dname = dirp->d_name;
		if ((dname[0] == '.') && ((dname[1] == '\0') || ((dname[1] == '.') && (dname[2] == '\0'))))
			continue;	/* skip "." and ".." directories. */

		(void) strcpy(cp, dirp->d_name);	/* append name after slash */
		(void) strcpy(c2, dirp->d_name);
		if (Lstat(fullpath, st) < 0) {
			Error(cip, kDoPerror, "could not stat %s.\n", fullpath);
			continue;
		}

		fi.relname = StrDup(relpath + (((relpath[0] == '/') || (relpath[0] == '\\')) ? 1 : 0));
		fi.rname = NULL;
		fi.lname = StrDup(fullpath);
		fi.mdtm = st->st_mtime;
		fi.size = (longest_int) st->st_size;
		fi.rlinkto = NULL;
		fi.plug = NULL;

		m = st->st_mode;
		if (S_ISREG(m) != 0) {
			/* file */
			fi.type = '-';
			(void) AddFileInfo(filp, &fi);
		} else if (S_ISDIR(m)) {
			Traverse(cip, fullpath, st, relpath, filp);
#ifdef S_ISLNK
		} else if (S_ISLNK(m)) {
			fi.type = 'l';
			fi.rlinkto = calloc(128, 1);
			if (fi.rlinkto != NULL) {
				if (readlink(fullpath, fi.rlinkto, 127) < 0) {
					free(fi.rlinkto);
				} else {
					(void) AddFileInfo(filp, &fi);
				}
			}
#endif	/* S_ISLNK */
		}
	}
	cp[-1] = '\0';
	c2[-1] = '\0';

	(void) closedir(dp);
}