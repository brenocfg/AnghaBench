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
typedef  int /*<<< orphan*/  tosType ;
struct TYPE_3__ {int errNo; } ;
typedef  TYPE_1__* FTPCIPtr ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_IP ; 
 int /*<<< orphan*/  IP_TOS ; 
 int kErrSetTypeOfService ; 
 int kNoErr ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

int
SetTypeOfService(const FTPCIPtr cip, int sockfd, int tosType)
{
	/* Specify to the router what type of connection this is, so it
	 * can prioritize packets.
	 */
	if (setsockopt(sockfd, IPPROTO_IP, IP_TOS, (char *) &tosType, (int) sizeof(tosType)) < 0) {
		/* Error(cip, kDoPerror, "Could not set type of service.\n"); */
		cip->errNo = kErrSetTypeOfService;
		return (kErrSetTypeOfService);
	}
	return (kNoErr);
}