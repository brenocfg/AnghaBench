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
 int DatumGetBool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXTENSION_SO ; 
 int /*<<< orphan*/  load_external_function (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *) ; 

extern bool
ts_bgw_worker_reserve(void)
{
	PGFunction reserve = load_external_function(EXTENSION_SO, "ts_bgw_worker_reserve", true, NULL);

	return DatumGetBool(
		DirectFunctionCall1(reserve, BoolGetDatum(false))); /* no function call zero */
}