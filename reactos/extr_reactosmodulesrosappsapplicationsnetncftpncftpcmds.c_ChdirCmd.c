#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {void* errNo; } ;
struct TYPE_14__ {scalar_t__* noglobargv; } ;
struct TYPE_13__ {TYPE_1__* first; } ;
struct TYPE_12__ {char* line; } ;
typedef  TYPE_1__* LinePtr ;
typedef  TYPE_2__ LineList ;
typedef  int /*<<< orphan*/  CommandPtr ;
typedef  TYPE_3__* ArgvInfoPtr ;

/* Variables and functions */
 int /*<<< orphan*/  ARGSUSED (int /*<<< orphan*/ ) ; 
 int Chdirs (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  DisposeLineListContents (TYPE_2__*) ; 
 int /*<<< orphan*/  FTPPerror (TYPE_4__*,int,int /*<<< orphan*/ ,char const*,char const*) ; 
 int FTPRemoteGlob (TYPE_4__*,TYPE_2__*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InitLineList (TYPE_2__*) ; 
 int /*<<< orphan*/  PrintCmdUsage (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  STRNCPY (char*,int /*<<< orphan*/ ) ; 
 char* StrDup (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_4__ gConn ; 
 char* gPrevRemoteCWD ; 
 int /*<<< orphan*/  gRemoteCWD ; 
 char* gStartDir ; 
 int /*<<< orphan*/  gUnusedArg ; 
 int /*<<< orphan*/  kErrCWDFailed ; 
 int /*<<< orphan*/  kErrGlobFailed ; 
 void* kErrMallocFailed ; 
 int /*<<< orphan*/  kGlobNo ; 
 int /*<<< orphan*/  kGlobYes ; 
 int kNoErr ; 
 scalar_t__ strcmp (char*,char*) ; 

void
ChdirCmd(const int argc, const char **const argv, const CommandPtr cmdp, const ArgvInfoPtr aip)
{
	int result;
	LineList ll;
	LinePtr lp;

	ARGSUSED(gUnusedArg);

	if (argc <= 1) {
		if (gStartDir[0] != '\0') {
			(void) STRNCPY(gPrevRemoteCWD, gRemoteCWD);
			result = Chdirs(&gConn, gStartDir);
			if (result != kNoErr) {
				/* State is incoherent if this happens! */
				FTPPerror(&gConn, result, kErrCWDFailed, "Could not chdir to", gStartDir);
			}
		} else {
			PrintCmdUsage(cmdp);
		}
	} else {
		InitLineList(&ll);
		result = FTPRemoteGlob(&gConn, &ll, argv[1], (aip->noglobargv[1] != 0) ? kGlobNo: kGlobYes);
		if (result < 0) {
			FTPPerror(&gConn, result, kErrGlobFailed, argv[0], argv[1]);
		} else {
			lp = ll.first;
			if ((lp != NULL) && (lp->line != NULL)) {
				if ((strcmp(lp->line, "-") == 0) && (gPrevRemoteCWD[0] != '\0')) {
					free(lp->line);
					lp->line = StrDup(gPrevRemoteCWD);
					if (lp->line == NULL) {
						result = kErrMallocFailed;
						gConn.errNo = kErrMallocFailed;
					} else {
						(void) STRNCPY(gPrevRemoteCWD, gRemoteCWD);
						result = Chdirs(&gConn, lp->line);
					}
				} else {
					(void) STRNCPY(gPrevRemoteCWD, gRemoteCWD);
					result = Chdirs(&gConn, lp->line);
				}
				if (result != kNoErr)
					FTPPerror(&gConn, result, kErrCWDFailed, "Could not chdir to", lp->line);
			}
		}
		DisposeLineListContents(&ll);
	}
}