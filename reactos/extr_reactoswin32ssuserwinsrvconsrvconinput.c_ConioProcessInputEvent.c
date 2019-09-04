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
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  PINPUT_RECORD ;
typedef  int /*<<< orphan*/  PCONSRV_CONSOLE ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ConioAddInputEvents (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

NTSTATUS
ConioProcessInputEvent(PCONSRV_CONSOLE Console,
                       PINPUT_RECORD InputEvent)
{
    ULONG NumEventsWritten;
    return ConioAddInputEvents(Console,
                               InputEvent,
                               1,
                               &NumEventsWritten,
                               TRUE);
}