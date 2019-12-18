#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  va_list ;
typedef  char* longstring ;
typedef  int /*<<< orphan*/  command ;
struct TYPE_5__ {scalar_t__ ctrlSocketW; scalar_t__ firewallType; char* lastFTPCmdResultStr; int lastFTPCmdResultNum; int errNo; scalar_t__ ctrlTimeout; int /*<<< orphan*/  user; } ;
typedef  TYPE_1__* FTPCIPtr ;

/* Variables and functions */
 int /*<<< orphan*/  Error (TYPE_1__* const,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PrintF (TYPE_1__* const,char*,char*) ; 
 int /*<<< orphan*/  STRNCAT (char*,char*) ; 
 int SWrite (scalar_t__,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SZ (int) ; 
 scalar_t__ kClosedFileDescriptor ; 
 int /*<<< orphan*/  kDoPerror ; 
 int kErrNotConnected ; 
 int kErrSocketWriteFailed ; 
 scalar_t__ kFirewallNotInUse ; 
 int kNoErr ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vsnprintf (char*,int,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vsprintf (char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
SendCommand(const FTPCIPtr cip, const char *cmdspec, va_list ap)
{
	longstring command;
	int result;

	if (cip->ctrlSocketW != kClosedFileDescriptor) {
#ifdef HAVE_VSNPRINTF
		(void) vsnprintf(command, sizeof(command) - 1, cmdspec, ap);
		command[sizeof(command) - 1] = '\0';
#else
		(void) vsprintf(command, cmdspec, ap);
#endif
		if ((strncmp(command, "PASS", SZ(4)) != 0) || ((strcmp(cip->user, "anonymous") == 0) && (cip->firewallType == kFirewallNotInUse)))
			PrintF(cip, "Cmd: %s\n", command);
		else
			PrintF(cip, "Cmd: %s\n", "PASS xxxxxxxx");
		(void) STRNCAT(command, "\r\n");	/* Use TELNET end-of-line. */
		cip->lastFTPCmdResultStr[0] = '\0';
		cip->lastFTPCmdResultNum = -1;

		result = SWrite(cip->ctrlSocketW, command, strlen(command), (int) cip->ctrlTimeout, 0);

		if (result < 0) {
			cip->errNo = kErrSocketWriteFailed;
			Error(cip, kDoPerror, "Could not write to control stream.\n");
			return (cip->errNo);
		}
		return (kNoErr);
	}
	return (kErrNotConnected);
}