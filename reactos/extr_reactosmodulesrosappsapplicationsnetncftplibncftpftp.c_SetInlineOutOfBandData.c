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
typedef  int /*<<< orphan*/  on ;
struct TYPE_4__ {int errNo; } ;
typedef  TYPE_1__* FTPCIPtr ;

/* Variables and functions */
 int /*<<< orphan*/  Error (TYPE_1__* const,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_OOBINLINE ; 
 int /*<<< orphan*/  kDoPerror ; 
 int kErrSetOutOfBandInline ; 
 int kNoErr ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

int
SetInlineOutOfBandData(const FTPCIPtr cip, int sockfd)
{
	int on = 1;

	if (setsockopt(sockfd, SOL_SOCKET, SO_OOBINLINE, (char *) &on, (int) sizeof(on)) < 0) {
		Error(cip, kDoPerror, "Could not set out of band inline mode.\n");
		cip->errNo = kErrSetOutOfBandInline;
		return (kErrSetOutOfBandInline);
	}
	return (kNoErr);
}