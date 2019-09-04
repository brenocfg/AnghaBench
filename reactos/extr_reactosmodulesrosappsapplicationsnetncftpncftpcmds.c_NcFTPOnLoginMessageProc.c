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
struct TYPE_3__ {int /*<<< orphan*/  msg; } ;
typedef  TYPE_1__* ResponsePtr ;
typedef  int /*<<< orphan*/ * FTPCIPtr ;

/* Variables and functions */
 int /*<<< orphan*/  OpenMsg (char*) ; 
 int /*<<< orphan*/  PrintResp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gUnusedArg ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
NcFTPOnLoginMessageProc(const FTPCIPtr cipUNUSED, ResponsePtr rp)
{
	gUnusedArg = (cipUNUSED != NULL);
	(void) printf("\n");
	PrintResp(&rp->msg);
	OpenMsg("Logging in...");
}