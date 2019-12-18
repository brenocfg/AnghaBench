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
struct TYPE_3__ {int /*<<< orphan*/  lastFTPCmdResultLL; } ;
typedef  int /*<<< orphan*/  CommandPtr ;
typedef  int /*<<< orphan*/  ArgvInfoPtr ;

/* Variables and functions */
 int /*<<< orphan*/  ARGSUSED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FTPCmd (TYPE_1__*,char*,char*) ; 
 int /*<<< orphan*/  PrintResp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STRNCAT (char*,char const*) ; 
 int /*<<< orphan*/  STRNCPY (char*,char const*) ; 
 TYPE_1__ gConn ; 
 int /*<<< orphan*/  gUnusedArg ; 

void
QuoteCmd(const int argc, const char **const argv, const CommandPtr cmdp, const ArgvInfoPtr aip)
{
	char cmdbuf[256];
	int i;

	ARGSUSED(gUnusedArg);
	(void) STRNCPY(cmdbuf, argv[1]);
	for (i=2; i<argc; i++) {
		(void) STRNCAT(cmdbuf, " ");
		(void) STRNCAT(cmdbuf, argv[i]);
	}
	(void) FTPCmd(&gConn, "%s", cmdbuf);
	PrintResp(&gConn.lastFTPCmdResultLL);
}