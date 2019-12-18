#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * errLog; int /*<<< orphan*/  errLogProc; int /*<<< orphan*/ * debugLog; int /*<<< orphan*/  debugLogProc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DebugHook ; 
 int /*<<< orphan*/  ErrorHook ; 
 TYPE_1__ gConn ; 

void
UseTrace(void)
{
	gConn.debugLogProc = DebugHook;
	gConn.debugLog = NULL;
	gConn.errLogProc = ErrorHook;
	gConn.errLog = NULL;
}