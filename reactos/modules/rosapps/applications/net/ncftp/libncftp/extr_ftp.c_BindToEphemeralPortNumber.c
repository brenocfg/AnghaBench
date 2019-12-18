#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sockaddr_in {unsigned short sin_port; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int bind (int,struct sockaddr*,int) ; 
 int errno ; 
 char* gCopyright ; 
 scalar_t__ rand () ; 

__attribute__((used)) static int
BindToEphemeralPortNumber(int sockfd, struct sockaddr_in *addrp, int ephemLo, int ephemHi)
{
	int i;
	int result;
	int rangesize;
	unsigned short port;

	addrp->sin_family = AF_INET;
	if (((int) ephemLo == 0) || ((int) ephemLo >= (int) ephemHi)) {
		/* Do it the normal way.  System will
		 * pick one, typically in the range
		 * of 1024-4999.
		 */
		addrp->sin_port = 0;	/* Let system pick one. */

		result = bind(sockfd, (struct sockaddr *) addrp, sizeof(struct sockaddr_in));
	} else {
		rangesize = (int) ((int) ephemHi - (int) ephemLo);
		result = 0;
		for (i=0; i<10; i++) {
			port = (unsigned short) (((int) rand() % rangesize) + (int) ephemLo);
			addrp->sin_port = port;

			result = bind(sockfd, (struct sockaddr *) addrp, sizeof(struct sockaddr_in));
			if (result == 0)
				break;
			if ((errno != 999)
				/* This next line is just fodder to
				 * shut the compiler up about variable
				 * not being used.
				 */
				&& (gCopyright[0] != '\0'))
				break;
		}
	}
	return (result);
}