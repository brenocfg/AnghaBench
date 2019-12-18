#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int WriteTotalTimeoutConstant; } ;
struct TYPE_6__ {int /*<<< orphan*/  hFile; } ;
typedef  TYPE_1__* PLOCALMON_PORT ;
typedef  TYPE_2__ COMMTIMEOUTS ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetCommTimeouts (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int GetLPTTransmissionRetryTimeout () ; 
 int /*<<< orphan*/  SetCommTimeouts (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL
_SetTransmissionRetryTimeout(PLOCALMON_PORT pPort)
{
    COMMTIMEOUTS CommTimeouts;

    // Get the timeout from the port.
    if (!GetCommTimeouts(pPort->hFile, &CommTimeouts))
        return FALSE;

    // Set the timeout using the value from registry.
    CommTimeouts.WriteTotalTimeoutConstant = GetLPTTransmissionRetryTimeout() * 1000;
    SetCommTimeouts(pPort->hFile, &CommTimeouts);

    return TRUE;
}