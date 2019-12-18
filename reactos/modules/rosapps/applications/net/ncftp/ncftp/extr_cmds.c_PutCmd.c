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
typedef  int /*<<< orphan*/  ConfirmResumeUploadProc ;
typedef  int /*<<< orphan*/  CommandPtr ;
typedef  TYPE_1__* ArgvInfoPtr ;

/* Variables and functions */
 int /*<<< orphan*/  ARGSUSED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FTPPerror (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*,char const*) ; 
 int FTPPutFiles3 (int /*<<< orphan*/ *,char*,char const*,int,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int FTPPutOneFile3 (int /*<<< orphan*/ *,char const*,char const*,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FlushLsCache () ; 
 int Getopt (int const,char const** const,char*) ; 
 int /*<<< orphan*/  GetoptReset () ; 
 int /*<<< orphan*/  NcFTPConfirmResumeUploadProc ; 
 int /*<<< orphan*/  NcSignal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NoConfirmResumeUploadProc ; 
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
 int kTypeAscii ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin ; 

void
PutCmd(const int argc, const char **const argv, const CommandPtr cmdp, const ArgvInfoPtr aip)
{
	int opt;
	int renameMode = 0;
	int recurseFlag = kRecursiveNo;
	int appendFlag = kAppendNo;
	const char *dstdir = NULL;
	int rc;
	int i;
	int doGlob;
	int xtype = gBm.xferType;
	int nD = 0;
	int deleteFlag = kDeleteNo;
	int resumeFlag = kResumeYes;
	char pattern[256];
	vsigproc_t osigint;
	ConfirmResumeUploadProc confirmProc;

	confirmProc = NcFTPConfirmResumeUploadProc;
	gResumeAnswerAll = kConfirmResumeProcNotUsed;	/* Ask at least once each time */
	ARGSUSED(gUnusedArg);
	GetoptReset();
	while ((opt = Getopt(argc, argv, "AafZzrRD")) >= 0) switch (opt) {
		case 'a':
			xtype = kTypeAscii;
			break;
		case 'A':
			/* Append to remote files, instead of truncating
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
			confirmProc = NoConfirmResumeUploadProc;
			break;
		case 'z':
			/* Special flag that lets you specify the
			 * destination file.  Normally a "put" will
			 * write the file by the same name as the
			 * local file's basename.
			 */
			renameMode = 1;
			break;
		case 'r':
		case 'R':
			recurseFlag = kRecursiveYes;
			/* If the item is a directory, get the
			 * directory and all its contents.
			 */
			recurseFlag = kRecursiveYes;
			break;
		case 'D':
			/* You can delete the local file after
			 * you uploaded it successfully by using
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
		if (gOptInd > (argc - 2)) {
			PrintCmdUsage(cmdp);
			(void) fprintf(stderr, "\nFor put with rename, try \"put -z local-path-name remote-path-name\".\n");
			return;
		}
		osigint = NcSignal(SIGINT, XferCanceller);
		rc = FTPPutOneFile3(&gConn, argv[gOptInd], argv[gOptInd + 1], xtype, (-1), appendFlag, NULL, NULL, resumeFlag, deleteFlag, confirmProc, 0);
		if (rc < 0)
			FTPPerror(&gConn, rc, kErrCouldNotStartDataTransfer, "put", argv[gOptInd + 1]);
	} else {
		osigint = NcSignal(SIGINT, XferCanceller);
		for (i=gOptInd; i<argc; i++) {
			doGlob = (aip->noglobargv[i] != 0) ? kGlobNo: kGlobYes;
			STRNCPY(pattern, argv[i]);
			StrRemoveTrailingSlashes(pattern);
			rc = FTPPutFiles3(&gConn, pattern, dstdir, recurseFlag, doGlob, xtype, appendFlag, NULL, NULL, resumeFlag, deleteFlag, confirmProc, 0);
			if (rc < 0)
				FTPPerror(&gConn, rc, kErrCouldNotStartDataTransfer, "put", argv[i]);
		}
	}

	/* Really should just flush only the modified directories... */
	FlushLsCache();

	(void) NcSignal(SIGINT, osigint);
	(void) fflush(stdin);
}