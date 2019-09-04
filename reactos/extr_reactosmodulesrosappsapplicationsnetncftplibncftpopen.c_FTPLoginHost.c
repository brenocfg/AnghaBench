#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_17__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cwd ;
struct TYPE_26__ {TYPE_1__* first; } ;
struct TYPE_25__ {scalar_t__ firewallType; char* magic; char* user; char* pass; int errNo; char* host; char* firewallUser; char* firewallPass; char* acct; int loggedIn; scalar_t__ doNotGetStartingWorkingDirectory; char curTransferType; scalar_t__ leavePass; int /*<<< orphan*/ * startingWorkingDirectory; int /*<<< orphan*/  (* onLoginMsgProc ) (TYPE_3__* const,TYPE_2__*) ;int /*<<< orphan*/  (* passphraseProc ) (TYPE_3__* const,TYPE_7__*,char*,int) ;TYPE_17__* lip; } ;
struct TYPE_24__ {int code; TYPE_7__ msg; } ;
struct TYPE_23__ {int /*<<< orphan*/  line; } ;
struct TYPE_22__ {char* defaultAnonPassword; } ;
typedef  TYPE_2__* ResponsePtr ;
typedef  TYPE_3__* FTPCIPtr ;

/* Variables and functions */
 int /*<<< orphan*/  DoneWithResponse (TYPE_3__* const,TYPE_2__*) ; 
 int /*<<< orphan*/  Error (TYPE_3__* const,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ FTPGetCWD (TYPE_3__* const,char*,int) ; 
 int /*<<< orphan*/  FTPInitializeAnonPassword (TYPE_17__*) ; 
 TYPE_2__* InitResponse () ; 
 int /*<<< orphan*/  NoGetPassphraseProc (TYPE_3__* const,TYPE_7__*,char*,int) ; 
 int /*<<< orphan*/  PrintF (TYPE_3__* const,char*,char*,char*) ; 
 int RCmd (TYPE_3__* const,TYPE_2__*,char*,char*,...) ; 
 int /*<<< orphan*/  ReInitResponse (TYPE_3__* const,TYPE_2__*) ; 
 int /*<<< orphan*/  STRNCPY (char*,char*) ; 
 int /*<<< orphan*/ * StrDup (char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kDontPerror ; 
 int kErrBadMagic ; 
 int kErrBadParameter ; 
 int kErrBadRemoteUser ; 
 int kErrBadRemoteUserOrPassword ; 
 int kErrHostDisconnectedDuringLogin ; 
 int kErrLoginFailed ; 
 void* kErrMallocFailed ; 
 scalar_t__ kFirewallFwuAtSiteFwpUserPass ; 
 scalar_t__ kFirewallLastType ; 
 scalar_t__ kFirewallLoginThenUserAtSite ; 
 scalar_t__ kFirewallNotInUse ; 
 scalar_t__ kFirewallOpenSite ; 
 scalar_t__ kFirewallSiteSite ; 
 scalar_t__ kFirewallUserAtSite ; 
 scalar_t__ kFirewallUserAtSiteFwuPassFwp ; 
 scalar_t__ kFirewallUserAtUserPassAtPass ; 
 char* kLibraryMagic ; 
 scalar_t__ kNoErr ; 
 int /*<<< orphan*/  memset (char*,char,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__* const,TYPE_7__*,char*,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__* const,TYPE_2__*) ; 

int
FTPLoginHost(const FTPCIPtr cip)
{
	ResponsePtr rp;
	int result = kErrLoginFailed;
	int anonLogin;
	int sentpass = 0;
	int fwloggedin;
	int firstTime;
	char cwd[512];

	if (cip == NULL)
		return (kErrBadParameter);
	if ((cip->firewallType < kFirewallNotInUse) || (cip->firewallType > kFirewallLastType))
		return (kErrBadParameter);

	if (strcmp(cip->magic, kLibraryMagic))
		return (kErrBadMagic);

	anonLogin = 0;
	if (cip->user[0] == '\0')
		(void) STRNCPY(cip->user, "anonymous");
	if ((strcmp(cip->user, "anonymous") == 0) || (strcmp(cip->user, "ftp") == 0)) {
		anonLogin = 1;
		/* Try to get the email address if you didn't specify
		 * a password when the user is anonymous.
		 */
		if (cip->pass[0] == '\0') {
			FTPInitializeAnonPassword(cip->lip);
			(void) STRNCPY(cip->pass, cip->lip->defaultAnonPassword);
		}
	}

	rp = InitResponse();
	if (rp == NULL) {
		result = kErrMallocFailed;
		cip->errNo = kErrMallocFailed;
		goto done2;
	}

	for (firstTime = 1, fwloggedin = 0; ; ) {
		/* Here's a mini finite-automaton for the login process.
		 *
		 * Originally, the FTP protocol was designed to be entirely
		 * implementable from a FA.  It could be done, but I don't think
		 * it's something an interactive process could be the most
		 * effective with.
		 */

		if (firstTime != 0) {
			rp->code = 220;
			firstTime = 0;
		} else if (result < 0) {
			goto done;
		}

		switch (rp->code) {
			case 220:	/* Welcome, ready for new user. */
				if ((cip->firewallType == kFirewallNotInUse) || (fwloggedin != 0)) {
					ReInitResponse(cip, rp);
					result = RCmd(cip, rp, "USER %s", cip->user);
				} else if (cip->firewallType == kFirewallUserAtSite) {
					ReInitResponse(cip, rp);
					result = RCmd(cip, rp, "USER %s@%s", cip->user, cip->host);
				} else if (cip->firewallType == kFirewallUserAtUserPassAtPass) {
					ReInitResponse(cip, rp);
					result = RCmd(cip, rp, "USER %s@%s@%s", cip->user, cip->firewallUser, cip->host);
				} else if (cip->firewallType == kFirewallUserAtSiteFwuPassFwp) {
					ReInitResponse(cip, rp);
					result = RCmd(cip, rp, "USER %s@%s %s", cip->user, cip->host, cip->firewallUser);
				} else if (cip->firewallType == kFirewallFwuAtSiteFwpUserPass) {
					/* only reached when !fwloggedin */
					ReInitResponse(cip, rp);
					result = RCmd(cip, rp, "USER %s@%s", cip->firewallUser, cip->host);
				} else if (cip->firewallType > kFirewallNotInUse) {
					ReInitResponse(cip, rp);
					result = RCmd(cip, rp, "USER %s", cip->firewallUser);
				} else {
					goto unknown;
				}
				break;

			case 230:	/* 230 User logged in, proceed. */
			case 231:	/* User name accepted. */
			case 202:	/* Command not implemented, superfluous at this site. */
				if ((cip->firewallType == kFirewallNotInUse) || (fwloggedin != 0))
					goto okay;

				/* Now logged in to the firewall. */
				fwloggedin++;

				if (cip->firewallType == kFirewallLoginThenUserAtSite) {
					ReInitResponse(cip, rp);
					result = RCmd(cip, rp, "USER %s@%s", cip->user, cip->host);
				} else if (cip->firewallType == kFirewallUserAtUserPassAtPass) {
					goto okay;
				} else if (cip->firewallType == kFirewallOpenSite) {
					ReInitResponse(cip, rp);
					result = RCmd(cip, rp, "OPEN %s", cip->host);
				} else if (cip->firewallType == kFirewallSiteSite) {
					ReInitResponse(cip, rp);
					result = RCmd(cip, rp, "SITE %s", cip->host);
				} else if (cip->firewallType == kFirewallFwuAtSiteFwpUserPass) {
					/* only reached when !fwloggedin */
					ReInitResponse(cip, rp);
					result = RCmd(cip, rp, "USER %s", cip->user);
				} else /* kFirewallUserAtSite */ {
					goto okay;
				}
				break;

			case 421:	/* 421 Service not available, closing control connection. */
				result = kErrHostDisconnectedDuringLogin;
				goto done;

			case 331:	/* 331 User name okay, need password. */
				if ((cip->firewallType == kFirewallNotInUse) || (fwloggedin != 0)) {
					if ((cip->pass[0] == '\0') && (cip->passphraseProc != NoGetPassphraseProc))
						(*cip->passphraseProc)(cip, &rp->msg, cip->pass, sizeof(cip->pass));
					ReInitResponse(cip, rp);
					result = RCmd(cip, rp, "PASS %s", cip->pass);
				} else if (cip->firewallType == kFirewallUserAtSite) {
					ReInitResponse(cip, rp);
					result = RCmd(cip, rp, "PASS %s", cip->pass);
				} else if (cip->firewallType == kFirewallUserAtUserPassAtPass) {
					ReInitResponse(cip, rp);
					result = RCmd(cip, rp, "PASS %s@%s", cip->pass, cip->firewallPass);
				} else if (cip->firewallType == kFirewallUserAtSiteFwuPassFwp) {
					ReInitResponse(cip, rp);
					result = RCmd(cip, rp, "PASS %s", cip->pass);
				} else if (cip->firewallType == kFirewallFwuAtSiteFwpUserPass) {
					/* only reached when !fwloggedin */
					ReInitResponse(cip, rp);
					result = RCmd(cip, rp, "PASS %s", cip->firewallPass);
				} else if (cip->firewallType > kFirewallNotInUse) {
					ReInitResponse(cip, rp);
					result = RCmd(cip, rp, "PASS %s", cip->firewallPass);
				} else {
					goto unknown;
				}
				sentpass++;
				break;

			case 332:	/* 332 Need account for login. */
			case 532: 	/* 532 Need account for storing files. */
				if ((cip->firewallType == kFirewallNotInUse) || (fwloggedin != 0)) {
					ReInitResponse(cip, rp);
					result = RCmd(cip, rp, "ACCT %s", cip->acct);
				} else if (cip->firewallType == kFirewallUserAtSiteFwuPassFwp) {
					ReInitResponse(cip, rp);
					result = RCmd(cip, rp, "ACCT %s", cip->firewallPass);
				} else {
					/* ACCT not supported on firewall. */
					goto unknown;
				}
				break;

			case 530:	/* Not logged in. */
				result = (sentpass != 0) ? kErrBadRemoteUserOrPassword : kErrBadRemoteUser;
				goto done;

			case 501:	/* Syntax error in parameters or arguments. */
			case 503:	/* Bad sequence of commands. */
			case 550:	/* Can't set guest privileges. */
				goto done;

			default:
			unknown:
				if (rp->msg.first == NULL) {
					Error(cip, kDontPerror, "Lost connection during login.\n");
				} else {
					Error(cip, kDontPerror, "Unexpected response: %s\n",
						rp->msg.first->line
					);
				}
				goto done;
		}
	}

okay:
	/* Do the application's connect message callback, if present. */
	if (cip->onLoginMsgProc != 0)
		(*cip->onLoginMsgProc)(cip, rp);
	DoneWithResponse(cip, rp);
	result = 0;
	cip->loggedIn = 1;

	/* Make a note of what our root directory is.
	 * This is often different from "/" when not
	 * logged in anonymously.
	 */
	if (cip->startingWorkingDirectory != NULL) {
		free(cip->startingWorkingDirectory);
		cip->startingWorkingDirectory = NULL;
	}
	if ((cip->doNotGetStartingWorkingDirectory == 0) &&
		(FTPGetCWD(cip, cwd, sizeof(cwd)) == kNoErr))
	{
		cip->startingWorkingDirectory = StrDup(cwd);
	}

	/* When a new site is opened, ASCII mode is assumed (by protocol). */
	cip->curTransferType = 'A';
	PrintF(cip, "Logged in to %s as %s.\n", cip->host, cip->user);

	/* Don't leave cleartext password in memory. */
	if ((anonLogin == 0) && (cip->leavePass == 0))
		(void) memset(cip->pass, '*', strlen(cip->pass));

	if (result < 0)
		cip->errNo = result;
	return result;

done:
	DoneWithResponse(cip, rp);

done2:
	/* Don't leave cleartext password in memory. */
	if ((anonLogin == 0) && (cip->leavePass == 0))
		(void) memset(cip->pass, '*', strlen(cip->pass));
	if (result < 0)
		cip->errNo = result;
	return result;
}