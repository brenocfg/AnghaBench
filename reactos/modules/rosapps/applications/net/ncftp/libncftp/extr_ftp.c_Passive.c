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
struct sockaddr_in {int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_addr; } ;
struct TYPE_15__ {int errNo; } ;
struct TYPE_13__ {TYPE_1__* first; } ;
struct TYPE_14__ {int codeType; TYPE_2__ msg; } ;
struct TYPE_12__ {char* line; } ;
typedef  TYPE_3__* ResponsePtr ;
typedef  TYPE_4__* FTPCIPtr ;

/* Variables and functions */
 int /*<<< orphan*/  DoneWithResponse (TYPE_4__* const,TYPE_3__*) ; 
 int /*<<< orphan*/  Error (TYPE_4__* const,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_3__* InitResponse () ; 
 int RCmd (TYPE_4__* const,TYPE_3__*,char*) ; 
 scalar_t__ isdigit (int) ; 
 int /*<<< orphan*/  kDontPerror ; 
 int kErrMallocFailed ; 
 int kErrPASVFailed ; 
 int kNoErr ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int sscanf (char*,char*,int*,int*,int*,int*,int*,int*) ; 

__attribute__((used)) static int
Passive(const FTPCIPtr cip, struct sockaddr_in *saddr, int *weird)
{
	ResponsePtr rp;
	int i[6], j;
	unsigned char n[6];
	char *cp;
	int result;

	rp = InitResponse();
	if (rp == NULL) {
		Error(cip, kDontPerror, "Malloc failed.\n");
		cip->errNo = kErrMallocFailed;
		return (cip->errNo);
	}

	result = RCmd(cip, rp, "PASV");
	if (result < 0)
		goto done;

	if (rp->codeType != 2) {
		/* Didn't understand or didn't want passive port selection. */
		cip->errNo = result = kErrPASVFailed;
		goto done;
	}

	/* The other side returns a specification in the form of
	 * an internet address as the first four integers (each
	 * integer stands for 8-bits of the real 32-bit address),
	 * and two more integers for the port (16-bit port).
	 *
	 * It should give us something like:
	 * "Entering Passive Mode (129,93,33,1,10,187)", so look for
	 * digits with sscanf() starting 24 characters down the string.
	 */
	for (cp = rp->msg.first->line; ; cp++) {
		if (*cp == '\0') {
			Error(cip, kDontPerror, "Cannot parse PASV response: %s\n", rp->msg.first->line);
			goto done;
		}
		if (isdigit((int) *cp))
			break;
	}

	if (sscanf(cp, "%d,%d,%d,%d,%d,%d",
			&i[0], &i[1], &i[2], &i[3], &i[4], &i[5]) != 6) {
		Error(cip, kDontPerror, "Cannot parse PASV response: %s\n", rp->msg.first->line);
		goto done;
	}

	for (j=0, *weird = 0; j<6; j++) {
		/* Some ftp servers return bogus port octets, such as
		 * boombox.micro.umn.edu.  Let the caller know if we got a
		 * weird looking octet.
		 */
		if ((i[j] < 0) || (i[j] > 255))
			*weird = *weird + 1;
		n[j] = (unsigned char) (i[j] & 0xff);
	}

	(void) memcpy(&saddr->sin_addr, &n[0], (size_t) 4);
	(void) memcpy(&saddr->sin_port, &n[4], (size_t) 2);

	result = kNoErr;
done:
	DoneWithResponse(cip, rp);
	return (result);
}