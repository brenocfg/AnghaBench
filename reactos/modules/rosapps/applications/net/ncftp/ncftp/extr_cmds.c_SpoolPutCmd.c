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
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  ldir ;
struct TYPE_16__ {int xferType; } ;
struct TYPE_15__ {int /*<<< orphan*/  dataPortMode; int /*<<< orphan*/  pass; int /*<<< orphan*/  user; int /*<<< orphan*/  port; int /*<<< orphan*/  ip; int /*<<< orphan*/  host; } ;
struct TYPE_14__ {scalar_t__* noglobargv; } ;
struct TYPE_13__ {TYPE_1__* first; } ;
struct TYPE_12__ {char* line; struct TYPE_12__* next; } ;
typedef  TYPE_1__* LinePtr ;
typedef  TYPE_2__ LineList ;
typedef  int /*<<< orphan*/  CommandPtr ;
typedef  TYPE_3__* ArgvInfoPtr ;

/* Variables and functions */
 int /*<<< orphan*/  ARGSUSED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DisposeLineListContents (TYPE_2__*) ; 
 int /*<<< orphan*/ * FTPGetLocalCWD (char*,int) ; 
 int FTPLocalGlob (TYPE_4__*,TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FTPPerror (TYPE_4__*,int,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  GetStartSpoolDate (int /*<<< orphan*/ ) ; 
 int Getopt (int const,char const** const,char*) ; 
 int /*<<< orphan*/  GetoptReset () ; 
 int /*<<< orphan*/  InitLineList (TYPE_2__*) ; 
 int /*<<< orphan*/  PrintCmdUsage (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  STRNCPY (char*,char const*) ; 
 scalar_t__ SpoolCheck () ; 
 int SpoolX (char*,char const*,int /*<<< orphan*/ ,char const*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrRemoveTrailingSlashes (char*) ; 
 int /*<<< orphan*/  Trace (int,char*,char const*,...) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 TYPE_5__ gBm ; 
 TYPE_4__ gConn ; 
 int /*<<< orphan*/  gOptArg ; 
 int const gOptInd ; 
 int /*<<< orphan*/  gRemoteCWD ; 
 scalar_t__ gSavePasswords ; 
 int /*<<< orphan*/  gUnusedArg ; 
 int kDeleteNo ; 
 int kDeleteYes ; 
 int /*<<< orphan*/  kErrGlobFailed ; 
 int /*<<< orphan*/  kGlobNo ; 
 int /*<<< orphan*/  kGlobYes ; 
 int kRecursiveNo ; 
 int kRecursiveYes ; 
 int kTypeAscii ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 char* strrchr (char*,char) ; 

void
SpoolPutCmd(const int argc, const char **const argv, const CommandPtr cmdp, const ArgvInfoPtr aip)
{
	int opt;
	int renameMode = 0;
	int recurseFlag = kRecursiveNo;
	int rc;
	int i;
	int xtype = gBm.xferType;
	int nD = 0;
	int deleteFlag = kDeleteNo;
	time_t when = 0;
	char ldir[256];
	char pattern[256];
	LineList ll;
	LinePtr lp;
	char *rname;

	ARGSUSED(gUnusedArg);

	if ((gSavePasswords <= 0) && ((strcmp(gConn.user, "anonymous") != 0) && (strcmp(gConn.user, "ftp") != 0))) {
		(void) printf("Sorry, spooling isn't allowed when you're not logged in anonymously, because\nthe spool files would need to save your password.\n\nYou can override this by doing a \"set save-passwords yes\" if you're willing\nto live with the consequences.\n");
		return;
	} else if (SpoolCheck() < 0) {
		return;
	}

	GetoptReset();
	while ((opt = Getopt(argc, argv, "@:azrRD")) >= 0) switch (opt) {
		case '@':
			when = GetStartSpoolDate(gOptArg);
			if ((when == (time_t) -1) || (when == (time_t) 0)) {
				(void) fprintf(stderr, "Bad date.  It must be expressed as one of the following:\n\tYYYYMMDDHHMMSS\t\n\t\"now + N hours|min|sec|days\"\n\tHH:MM\n\nNote:  Do not forget to quote the entire argument for the offset option.\nExample:  bgget -@ \"now + 15 min\" ...\n");
				return;
			}
			break;
		case 'a':
			xtype = kTypeAscii;
			break;
		case 'z':
			/* Special flag that lets you specify the
			 * destination file.  Normally a "get" will
			 * write the file by the same name as the
			 * remote file's basename.
			 */
			renameMode = 1;
			break;
		case 'r':
		case 'R':
			/* If the item is a directory, get the
			 * directory and all its contents.
			 */
			recurseFlag = kRecursiveYes;
			break;
		case 'D':
			/* You can delete the remote file after
			 * you downloaded it successfully by using
			 * the -DD option.  It requires two -D's
			 * to minimize the odds of accidentally
			 * using a single -D.
			 */
			nD++;
			break;
		default:
			PrintCmdUsage(cmdp);
			return;
	}

	if (nD >= 2)
		deleteFlag = kDeleteYes;

	if (FTPGetLocalCWD(ldir, sizeof(ldir)) == NULL) {
		perror("could not get current local directory");
		return;
	}

	if (renameMode != 0) {
		if (gOptInd > argc - 2) {
			PrintCmdUsage(cmdp);
			return;
		}
		rc = SpoolX(
			"put",
			argv[gOptInd + 1],
			gRemoteCWD,
			argv[gOptInd + 0],
			ldir,
			gConn.host,
			gConn.ip,
			gConn.port,
			gConn.user,
			gConn.pass,
			xtype,
			recurseFlag,
			deleteFlag,
			gConn.dataPortMode,
			NULL,
			NULL,
			NULL,
			when
		);
		if (rc == 0) {
			Trace(-1, "  + Spooled: put %s as %s\n", argv[gOptInd], argv[gOptInd]);
		}
	} else {
		for (i=gOptInd; i<argc; i++) {
			STRNCPY(pattern, argv[i]);
			StrRemoveTrailingSlashes(pattern);
			InitLineList(&ll);
			rc = FTPLocalGlob(&gConn, &ll, pattern, (aip->noglobargv[i] != 0) ? kGlobNo: kGlobYes);
			if (rc < 0) {
				FTPPerror(&gConn, rc, kErrGlobFailed, "local glob", pattern);
			} else {
				for (lp = ll.first; lp != NULL; lp = lp->next) {
					if (lp->line != NULL) {
						rname = strrchr(lp->line, '/');
						if (rname == NULL)
							rname = lp->line;
						else
							rname++;
						rc = SpoolX(
							"put",
							rname,
							gRemoteCWD,
							lp->line,
							ldir,
							gConn.host,
							gConn.ip,
							gConn.port,
							gConn.user,
							gConn.pass,
							xtype,
							recurseFlag,
							deleteFlag,
							gConn.dataPortMode,
							NULL,
							NULL,
							NULL,
							when
						);
						if (rc == 0) {
							Trace(-1, "  + Spooled: put %s\n", lp->line);
						}
					}
				}
			}
			DisposeLineListContents(&ll);
		}
	}
}