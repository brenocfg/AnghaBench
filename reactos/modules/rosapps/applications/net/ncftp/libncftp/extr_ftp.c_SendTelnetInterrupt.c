#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * cout; int /*<<< orphan*/  ctrlSocketW; } ;
typedef  TYPE_1__* FTPCIPtr ;

/* Variables and functions */
 int DM ; 
 int /*<<< orphan*/  Error (TYPE_1__* const,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ IAC ; 
 scalar_t__ IP ; 
 int /*<<< orphan*/  MSG_OOB ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  kDoPerror ; 
 int send (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 

void
SendTelnetInterrupt(const FTPCIPtr cip)
{
	char msg[4];

	/* 1. User system inserts the Telnet "Interrupt Process" (IP) signal
	 *    in the Telnet stream.
	 */

	if (cip->cout != NULL)
		(void) fflush(cip->cout);

	msg[0] = (char) (unsigned char) IAC;
	msg[1] = (char) (unsigned char) IP;
	(void) send(cip->ctrlSocketW, msg, 2, 0);

	/* 2. User system sends the Telnet "Sync" signal. */
#if 1
	msg[0] = (char) (unsigned char) IAC;
	msg[1] = (char) (unsigned char) DM;
	if (send(cip->ctrlSocketW, msg, 2, MSG_OOB) != 2)
		Error(cip, kDoPerror, "Could not send an urgent message.\n");
#else
	/* "Send IAC in urgent mode instead of DM because UNIX places oob mark
	 * after urgent byte rather than before as now is protocol," says
	 * the BSD ftp code.
	 */
	msg[0] = (char) (unsigned char) IAC;
	if (send(cip->ctrlSocketW, msg, 1, MSG_OOB) != 1)
		Error(cip, kDoPerror, "Could not send an urgent message.\n");
	(void) fprintf(cip->cout, "%c", DM);
	(void) fflush(cip->cout);
#endif
}