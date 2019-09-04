#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ serverType; int errNo; void* hasBUFSIZE; void* hasSBUFSZ; void* hasSBUFSIZ; void* hasSTORBUFSIZE; void* hasRBUFSIZ; void* hasRBUFSZ; void* hasRETRBUFSIZE; int /*<<< orphan*/  ietfCompatLevel; void* hasCLNT; void* hasMLSD; void* hasMLST; void* hasUTIME; void* hasREST; void* hasMDTM; void* hasSIZE; void* hasPASV; void* hasFEAT; void* NLSTfileParamWorks; int /*<<< orphan*/  magic; } ;
struct TYPE_16__ {char* line; struct TYPE_16__* next; } ;
struct TYPE_14__ {TYPE_3__* first; } ;
struct TYPE_15__ {int printMode; TYPE_1__ msg; } ;
typedef  TYPE_2__* ResponsePtr ;
typedef  TYPE_3__* LinePtr ;
typedef  TYPE_4__* FTPCIPtr ;

/* Variables and functions */
 int /*<<< orphan*/  DoneWithResponse (TYPE_4__* const,TYPE_2__*) ; 
 int /*<<< orphan*/  FTPExamineMlstFeatures (TYPE_4__* const,char*) ; 
 scalar_t__ ISTRNCMP (char*,char*,int) ; 
 TYPE_2__* InitResponse () ; 
 int RCmd (TYPE_4__* const,TYPE_2__*,char*) ; 
 int /*<<< orphan*/  ReInitResponse (TYPE_4__* const,TYPE_2__*) ; 
 int /*<<< orphan*/  atoi (char*) ; 
 int /*<<< orphan*/  isupper (char) ; 
 void* kCommandAvailable ; 
 void* kCommandNotAvailable ; 
 int kErrBadMagic ; 
 int kErrBadParameter ; 
 int kErrMallocFailed ; 
 int /*<<< orphan*/  kLibraryMagic ; 
 int kNoErr ; 
 int kResponseNoPrint ; 
 int kResponseNoSave ; 
 scalar_t__ kServerTypeNcFTPd ; 
 scalar_t__ kServerTypeNetWareFTP ; 
 scalar_t__ kServerTypeWuFTPd ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strstr (char*,char*) ; 

int
FTPQueryFeatures(const FTPCIPtr cip)
{
	ResponsePtr rp;
	int result;
	LinePtr lp;
	char *cp, *p;

	if (cip == NULL)
		return (kErrBadParameter);
	if (strcmp(cip->magic, kLibraryMagic))
		return (kErrBadMagic);

	if (cip->serverType == kServerTypeNetWareFTP) {
		/* NetWare 5.00 server freaks out when
		 * you give it a command it doesn't
		 * recognize, so cheat here and return.
		 */
		cip->hasPASV = kCommandAvailable;
		cip->hasSIZE = kCommandNotAvailable;
		cip->hasMDTM = kCommandNotAvailable;
		cip->hasREST = kCommandNotAvailable;
		cip->NLSTfileParamWorks = kCommandAvailable;
		cip->hasUTIME = kCommandNotAvailable;
		cip->hasCLNT = kCommandNotAvailable;
		cip->hasMLST = kCommandNotAvailable;
		cip->hasMLSD = kCommandNotAvailable;
		return (kNoErr);
	}

	rp = InitResponse();
	if (rp == NULL) {
		cip->errNo = kErrMallocFailed;
		result = cip->errNo;
	} else {
		rp->printMode = (kResponseNoPrint|kResponseNoSave);
		result = RCmd(cip, rp, "FEAT");
		if (result < kNoErr) {
			DoneWithResponse(cip, rp);
			return (result);
		} else if (result != 2) {
			/* We cheat here and pre-populate some
			 * fields when the server is wu-ftpd.
			 * This server is very common and we
			 * know it has always had these.
			 */
			 if (cip->serverType == kServerTypeWuFTPd) {
				cip->hasPASV = kCommandAvailable;
				cip->hasSIZE = kCommandAvailable;
				cip->hasMDTM = kCommandAvailable;
				cip->hasREST = kCommandAvailable;
				cip->NLSTfileParamWorks = kCommandAvailable;
			} else if (cip->serverType == kServerTypeNcFTPd) {
				cip->hasPASV = kCommandAvailable;
				cip->hasSIZE = kCommandAvailable;
				cip->hasMDTM = kCommandAvailable;
				cip->hasREST = kCommandAvailable;
				cip->NLSTfileParamWorks = kCommandAvailable;
			}

			/* Newer commands are only shown in FEAT,
			 * so we don't have to do the "try it,
			 * then save that it didn't work" thing.
			 */
			cip->hasMLST = kCommandNotAvailable;
			cip->hasMLSD = kCommandNotAvailable;
		} else {
			cip->hasFEAT = kCommandAvailable;

			for (lp = rp->msg.first; lp != NULL; lp = lp->next) {
				/* If first character was not a space it is
				 * either:
				 *
				 * (a) The header line in the response;
				 * (b) The trailer line in the response;
				 * (c) A protocol violation.
				 */
				cp = lp->line;
				if (*cp++ != ' ')
					continue;
				if (ISTRNCMP(cp, "PASV", 4) == 0) {
					cip->hasPASV = kCommandAvailable;
				} else if (ISTRNCMP(cp, "SIZE", 4) == 0) {
					cip->hasSIZE = kCommandAvailable;
				} else if (ISTRNCMP(cp, "MDTM", 4) == 0) {
					cip->hasMDTM = kCommandAvailable;
				} else if (ISTRNCMP(cp, "REST", 4) == 0) {
					cip->hasREST = kCommandAvailable;
				} else if (ISTRNCMP(cp, "UTIME", 5) == 0) {
					cip->hasUTIME = kCommandAvailable;
				} else if (ISTRNCMP(cp, "MLST", 4) == 0) {
					cip->hasMLST = kCommandAvailable;
					cip->hasMLSD = kCommandAvailable;
					FTPExamineMlstFeatures(cip, cp + 5);
				} else if (ISTRNCMP(cp, "CLNT", 4) == 0) {
					cip->hasCLNT = kCommandAvailable;
				} else if (ISTRNCMP(cp, "Compliance Level: ", 18) == 0) {
					/* Probably only NcFTPd will ever implement this.
					 * But we use it internally to differentiate
					 * between different NcFTPd implementations of
					 * IETF extensions.
					 */
					cip->ietfCompatLevel = atoi(cp + 18);
				}
			}
		}

		ReInitResponse(cip, rp);
		result = RCmd(cip, rp, "HELP SITE");
		if (result == 2) {
			for (lp = rp->msg.first; lp != NULL; lp = lp->next) {
				cp = lp->line;
				if (strstr(cp, "RETRBUFSIZE") != NULL)
					cip->hasRETRBUFSIZE = kCommandAvailable;
				if (strstr(cp, "RBUFSZ") != NULL)
					cip->hasRBUFSZ = kCommandAvailable;
				/* See if RBUFSIZ matches (but not STORBUFSIZE) */
				if (
					((p = strstr(cp, "RBUFSIZ")) != NULL) &&
					(
					 	(p == cp) ||
						((p > cp) && (!isupper(p[-1])))
					)
				)
					cip->hasRBUFSIZ = kCommandAvailable;
				if (strstr(cp, "STORBUFSIZE") != NULL)
					cip->hasSTORBUFSIZE = kCommandAvailable;
				if (strstr(cp, "SBUFSIZ") != NULL)
					cip->hasSBUFSIZ = kCommandAvailable;
				if (strstr(cp, "SBUFSZ") != NULL)
					cip->hasSBUFSZ = kCommandAvailable;
				if (strstr(cp, "BUFSIZE") != NULL)
					cip->hasBUFSIZE = kCommandAvailable;
			}
		}
		DoneWithResponse(cip, rp);
	}

	return (kNoErr);
}