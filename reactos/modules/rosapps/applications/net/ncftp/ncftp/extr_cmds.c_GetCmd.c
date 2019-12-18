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
typedef  int /*<<< orphan*/  vsigproc_t ;
struct TYPE_5__ {int xferType; } ;
struct TYPE_4__ {scalar_t__* noglobargv; } ;
typedef  int /*<<< orphan*/  ConfirmResumeDownloadProc ;
typedef  int /*<<< orphan*/  CommandPtr ;
typedef  TYPE_1__* ArgvInfoPtr ;

/* Variables and functions */
 int /*<<< orphan*/  ARGSUSED (int /*<<< orphan*/ ) ; 
 int FTPGetFiles3 (int /*<<< orphan*/ *,char*,char const*,int,int,int,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int FTPGetOneFile3 (int /*<<< orphan*/ *,char const*,char const*,int,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FTPPerror (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  FlushLsCache () ; 
 int Getopt (int const,char const** const,char*) ; 
 int /*<<< orphan*/  GetoptReset () ; 
 int /*<<< orphan*/  NcFTPConfirmResumeDownloadProc ; 
 int /*<<< orphan*/  NcSignal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NoConfirmResumeDownloadProc ; 
 int /*<<< orphan*/  PrintCmdUsage (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  STRNCPY (char*,char const*) ; 
 int /*<<< orphan*/  StrRemoveTrailingSlashes (char*) ; 
 int /*<<< orphan*/  XferCanceller ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__ gBm ; 
 int /*<<< orphan*/  gConn ; 
 int const gOptInd ; 
 int /*<<< orphan*/  gResumeAnswerAll ; 
 int /*<<< orphan*/  gUnusedArg ; 
 int kAppendNo ; 
 int kAppendYes ; 
 int /*<<< orphan*/  kConfirmResumeProcNotUsed ; 
 int kDeleteNo ; 
 int kDeleteYes ; 
 int /*<<< orphan*/  kErrCouldNotStartDataTransfer ; 
 int kGlobNo ; 
 int kGlobYes ; 
 int kRecursiveNo ; 
 int kRecursiveYes ; 
 int kResumeNo ; 
 int kResumeYes ; 
 int kTarNo ; 
 int kTarYes ; 
 int kTypeAscii ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin ; 

void
GetCmd(const int argc, const char **const argv, const CommandPtr cmdp, const ArgvInfoPtr aip)
{
	int opt;
	int renameMode = 0;
	int recurseFlag = kRecursiveNo;
	int appendFlag = kAppendNo;
	int resumeFlag = kResumeYes;
	int tarflag = kTarYes;
	const char *dstdir = NULL;
	int rc;
	int i;
	int doGlob;
	int xtype = gBm.xferType;
	int nD = 0;
	int deleteFlag = kDeleteNo;
	char pattern[256];
	vsigproc_t osigint;
	ConfirmResumeDownloadProc confirmProc;

	confirmProc = NcFTPConfirmResumeDownloadProc;
	gResumeAnswerAll = kConfirmResumeProcNotUsed;	/* Ask at least once each time */
	ARGSUSED(gUnusedArg);
	GetoptReset();
	while ((opt = Getopt(argc, argv, "aAzfrRTD")) >= 0) switch (opt) {
		case 'a':
			xtype = kTypeAscii;
			break;
		case 'A':
			/* Append to local files, instead of truncating
			 * them first.
			 */
			appendFlag = kAppendYes;
			break;
		case 'f':
		case 'Z':
			/* Do not try to resume a download, even if it
			 * appeared that some of the file was transferred
			 * already.
			 */
			resumeFlag = kResumeNo;
			confirmProc = NoConfirmResumeDownloadProc;
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
		case 'T':
			/* If they said "-R", they may want to
			 * turn off TAR mode if they are trying
			 * to resume the whole directory.
			 * The disadvantage to TAR mode is that
			 * it always downloads the whole thing,
			 * which is why there is a flag to
			 * disable this.
			 */
			tarflag = kTarNo;
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

	if (renameMode != 0) {
		if (gOptInd > argc - 2) {
			PrintCmdUsage(cmdp);
			(void) fprintf(stderr, "\nFor get with rename, try \"get -z remote-path-name local-path-name\".\n");
			return;
		}
		osigint = NcSignal(SIGINT, XferCanceller);
		rc = FTPGetOneFile3(&gConn, argv[gOptInd], argv[gOptInd + 1], xtype, (-1), resumeFlag, appendFlag, deleteFlag, NoConfirmResumeDownloadProc, 0);
		if (rc < 0)
			FTPPerror(&gConn, rc, kErrCouldNotStartDataTransfer, "get", argv[gOptInd]);
	} else {
		osigint = NcSignal(SIGINT, XferCanceller);
		for (i=gOptInd; i<argc; i++) {
			doGlob = (aip->noglobargv[i] != 0) ? kGlobNo: kGlobYes;
			STRNCPY(pattern, argv[i]);
			StrRemoveTrailingSlashes(pattern);
			rc = FTPGetFiles3(&gConn, pattern, dstdir, recurseFlag, doGlob, xtype, resumeFlag, appendFlag, deleteFlag, tarflag, confirmProc, 0);
			if (rc < 0)
				FTPPerror(&gConn, rc, kErrCouldNotStartDataTransfer, "get", argv[i]);
		}
	}
	(void) NcSignal(SIGINT, osigint);
	(void) fflush(stdin);

	if (deleteFlag == kDeleteYes) {
		/* Directory is now out of date */
		FlushLsCache();
	}
}