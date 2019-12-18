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
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  on ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 int /*<<< orphan*/  SO_REUSEPORT ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (unsigned short) ; 
 int const kReUseAddrNo ; 
 int /*<<< orphan*/  setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sleep (unsigned int) ; 

int
SBind(int sockfd, const int port, const int nTries, const int reuseFlag)
{
	unsigned int i;
	int on;
	int onsize;
	struct sockaddr_in localAddr;

	localAddr.sin_family = AF_INET;
	localAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	localAddr.sin_port = htons((unsigned short) port);

	if (reuseFlag != kReUseAddrNo) {
		/* This is mostly so you can quit the server and re-run it
		 * again right away.  If you don't do this, the OS may complain
		 * that the address is still in use.
		 */
		on = 1;
		onsize = (int) sizeof(on);
		(void) setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR,
			(char *) &on, onsize);

#ifdef SO_REUSEPORT
		/* Tells kernel that it's okay to have more
		 * than one process originating from this
		 * local port.
		 */
		on = 1;
		onsize = (int) sizeof(on);
		(void) setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT,
			(char *) &on, onsize);
#endif	/* SO_REUSEPORT */
	}

	for (i=1; ; i++) {
		/* Try binding a few times, in case we get Address in Use
		 * errors.
		 */
		if (bind(sockfd, (struct sockaddr *) &localAddr, sizeof(struct sockaddr_in)) == 0) {
			break;
		}
		if ((int) i == nTries) {
			return (-1);
		}
		/* Give the OS time to clean up the old socket,
		 * and then try again.
		 */
		sleep(i * 3);
	}

	return (0);
}