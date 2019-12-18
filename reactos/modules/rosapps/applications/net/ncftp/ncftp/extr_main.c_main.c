#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int redialDelay; void* maxDials; int /*<<< orphan*/  acct; int /*<<< orphan*/  pass; int /*<<< orphan*/  user; void* port; } ;

/* Variables and functions */
 int /*<<< orphan*/  CommandShell () ; 
 int /*<<< orphan*/  DumpFirewallPrefsTemplate () ; 
 int Getopt (int,char const** const,char*) ; 
 int /*<<< orphan*/  GetoptReset () ; 
 int /*<<< orphan*/  LoadFirewallPrefs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OpenURL () ; 
 int /*<<< orphan*/  PostInit () ; 
 int /*<<< orphan*/  PostShell () ; 
 int /*<<< orphan*/  PreInit () ; 
 int /*<<< orphan*/  STRNCPY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetStartupURL (char const*) ; 
 int /*<<< orphan*/  Usage () ; 
 void* atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 TYPE_1__ gConn ; 
 int /*<<< orphan*/  gOptArg ; 
 int gOptInd ; 
 scalar_t__ gStartupUrlParameterGiven ; 

int
main(int argc, const char **const argv)
{
	int c;
	int n;

	PreInit();
	while ((c = Getopt(argc, argv, "P:u:p:J:rd:g:FVLD")) > 0) switch(c) {
		case 'P':
		case 'u':
		case 'p':
		case 'J':
			gStartupUrlParameterGiven = 1;
			break;
		case 'r':
		case 'g':
		case 'd':
		case 'V':
		case 'L':
		case 'D':
		case 'F':
			break;
		default:
			Usage();
	}

	if (gOptInd < argc) {
		LoadFirewallPrefs(0);
		SetStartupURL(argv[gOptInd]);
	} else if (gStartupUrlParameterGiven != 0) {
		/* One of the flags they specified
		 * requires a URL or hostname to
		 * open.
		 */
		Usage();
	}

	GetoptReset();
	/* Allow command-line parameters to override
	 * bookmark settings.
	 */

	while ((c = Getopt(argc, argv, "P:u:p:j:J:rd:g:FVLD")) > 0) switch(c) {
		case 'P':
			gConn.port = atoi(gOptArg);
			break;
		case 'u':
			(void) STRNCPY(gConn.user, gOptArg);
			break;
		case 'p':
			(void) STRNCPY(gConn.pass, gOptArg);	/* Don't recommend doing this! */
			break;
		case 'J':
		case 'j':
			(void) STRNCPY(gConn.acct, gOptArg);
			break;
		case 'r':
			/* redial is always on */
			break;
		case 'g':
			gConn.maxDials = atoi(gOptArg);
			break;
		case 'd':
			n = atoi(gOptArg);
			if (n >= 10)
				gConn.redialDelay = n;
			break;
		case 'F':
			DumpFirewallPrefsTemplate();
			exit(0);
			/*NOTREACHED*/
			break;
		case 'V':
			/*FALLTHROUGH*/
		case 'L':
			/*FALLTHROUGH*/
		case 'D':
			/* silently ignore these legacy options */
			break;
		default:
			Usage();
	}

	PostInit();
	OpenURL();
	CommandShell();
	PostShell();
	exit(0);
}