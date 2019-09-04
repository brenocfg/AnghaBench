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
typedef  int /*<<< orphan*/  BackgroundWorkerHandle ;

/* Variables and functions */
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/ * bgw_handle ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 

void
ts_timer_mock_register_bgw_handle(BackgroundWorkerHandle *handle)
{
	elog(WARNING, "[TESTING] Registered new background worker");
	bgw_handle = handle;
}