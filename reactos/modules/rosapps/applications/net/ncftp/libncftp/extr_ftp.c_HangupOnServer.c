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
typedef  int /*<<< orphan*/  FTPCIPtr ;

/* Variables and functions */
 int /*<<< orphan*/  CloseControlConnection (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  CloseDataConnection (int /*<<< orphan*/  const) ; 

void
HangupOnServer(const FTPCIPtr cip)
{
	/* Since we want to close both sides of the connection for each
	 * socket, we can just have them closed with close() instead of
	 * using shutdown().
	 */
	CloseControlConnection(cip);
	CloseDataConnection(cip);
}