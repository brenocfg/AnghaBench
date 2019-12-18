#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG ;
struct TYPE_5__ {int /*<<< orphan*/  InputBuffer; } ;
typedef  scalar_t__* PULONG ;
typedef  int /*<<< orphan*/  PINPUT_RECORD ;
typedef  TYPE_1__* PCONSRV_CONSOLE ;
typedef  int /*<<< orphan*/  PCONSOLE ;
typedef  scalar_t__ NTSTATUS ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 scalar_t__ ConDrvWriteConsoleInput (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  PostprocessInput (TYPE_1__*) ; 
 scalar_t__ PreprocessInput (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ STATUS_SUCCESS ; 

__attribute__((used)) static NTSTATUS
ConioAddInputEvents(PCONSRV_CONSOLE Console,
                    PINPUT_RECORD InputRecords, // InputEvent
                    ULONG NumEventsToWrite,
                    PULONG NumEventsWritten,
                    BOOLEAN AppendToEnd)
{
    NTSTATUS Status = STATUS_SUCCESS;

    if (NumEventsWritten) *NumEventsWritten = 0;

    NumEventsToWrite = PreprocessInput(Console, InputRecords, NumEventsToWrite);
    if (NumEventsToWrite == 0) return STATUS_SUCCESS;

    // Status = ConDrvAddInputEvents(Console,
                                  // InputRecords,
                                  // NumEventsToWrite,
                                  // NumEventsWritten,
                                  // AppendToEnd);

    Status = ConDrvWriteConsoleInput((PCONSOLE)Console,
                                     &Console->InputBuffer,
                                     AppendToEnd,
                                     InputRecords,
                                     NumEventsToWrite,
                                     NumEventsWritten);

    // if (NT_SUCCESS(Status))
    if (Status == STATUS_SUCCESS) PostprocessInput(Console);

    return Status;
}