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
typedef  int /*<<< orphan*/  PGFunction ;

/* Variables and functions */
 int /*<<< orphan*/  BoolGetDatum (int) ; 
 int DatumGetInt32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXTENSION_SO ; 
 int /*<<< orphan*/  load_external_function (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *) ; 

extern int
ts_bgw_num_unreserved(void)
{
	PGFunction unreserved =
		load_external_function(EXTENSION_SO, "ts_bgw_num_unreserved", true, NULL);

	return DatumGetInt32(
		DirectFunctionCall1(unreserved, BoolGetDatum(false))); /* no function call zero */
}