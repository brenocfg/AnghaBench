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
struct sockaddr_in {int dummy; } ;
struct sockaddr {int dummy; } ;
struct TYPE_4__ {void* errNo; } ;
typedef  TYPE_1__* FTPCIPtr ;

/* Variables and functions */
 int /*<<< orphan*/  Error (TYPE_1__* const,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ getsockname (int,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  kDoPerror ; 
 void* kErrGetSockName ; 

__attribute__((used)) static int
GetSocketAddress(const FTPCIPtr cip, int sockfd, struct sockaddr_in *saddr)
{
	int len = (int) sizeof (struct sockaddr_in);
	int result = 0;

	if (getsockname(sockfd, (struct sockaddr *)saddr, &len) < 0) {
		Error(cip, kDoPerror, "Could not get socket name.\n");
		cip->errNo = kErrGetSockName;
		result = kErrGetSockName;
	}
	return (result);
}