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
typedef  int /*<<< orphan*/  ulCmd ;
typedef  scalar_t__ ULONG ;
typedef  int /*<<< orphan*/  TID ;
typedef  int /*<<< orphan*/  HPIPE ;

/* Variables and functions */
 int /*<<< orphan*/  DCWW_WAIT ; 
 int /*<<< orphan*/  DosClose (int /*<<< orphan*/ ) ; 
 scalar_t__ DosOpen (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DosSleep (int) ; 
 int /*<<< orphan*/  DosWaitNPipe (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DosWaitThread (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DosWrite (int /*<<< orphan*/ ,scalar_t__*,int,scalar_t__*) ; 
 scalar_t__ ERROR_PIPE_BUSY ; 
 scalar_t__ IPC_CMD_QUIT ; 
 int OPEN_ACCESS_READWRITE ; 
 int /*<<< orphan*/  OPEN_ACTION_OPEN_IF_EXISTS ; 
 int OPEN_FLAGS_FAIL_ON_ERROR ; 
 int OPEN_SHARE_DENYREADWRITE ; 
 int /*<<< orphan*/  VLC_IPC_PIPE ; 
 scalar_t__ _gettid () ; 
 scalar_t__ tidIPCFirst ; 
 int /*<<< orphan*/  tidIPCHelper ; 

void system_End(void)
{
    if( tidIPCFirst == _gettid())
    {
        HPIPE hpipe;
        ULONG ulAction;
        ULONG cbActual;
        ULONG rc;

        do
        {
            rc = DosOpen( VLC_IPC_PIPE, &hpipe, &ulAction, 0, 0,
                          OPEN_ACTION_OPEN_IF_EXISTS,
                          OPEN_ACCESS_READWRITE | OPEN_SHARE_DENYREADWRITE |
                          OPEN_FLAGS_FAIL_ON_ERROR,
                          NULL );

            if( rc == ERROR_PIPE_BUSY )
                DosWaitNPipe( VLC_IPC_PIPE, -1 );
            else if( rc )
                DosSleep( 1 );
        } while( rc );

        /* Ask for IPCHelper to quit */
        ULONG ulCmd = IPC_CMD_QUIT;
        DosWrite( hpipe, &ulCmd, sizeof( ulCmd ), &cbActual );

        DosClose( hpipe );

        TID tid = tidIPCHelper;
        DosWaitThread( &tid, DCWW_WAIT );
    }
}