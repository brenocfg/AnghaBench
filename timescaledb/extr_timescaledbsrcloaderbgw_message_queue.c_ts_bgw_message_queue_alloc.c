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
typedef  int /*<<< orphan*/  MessageQueue ;

/* Variables and functions */
 int /*<<< orphan*/  BGW_MQ_TRANCHE_NAME ; 
 int /*<<< orphan*/  RequestAddinShmemSpace (int) ; 
 int /*<<< orphan*/  RequestNamedLWLockTranche (int /*<<< orphan*/ ,int) ; 

extern void
ts_bgw_message_queue_alloc(void)
{
	RequestAddinShmemSpace(sizeof(MessageQueue));
	RequestNamedLWLockTranche(BGW_MQ_TRANCHE_NAME, 1);
}