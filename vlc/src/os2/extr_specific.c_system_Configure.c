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
typedef  int /*<<< orphan*/  libvlc_int_t ;
typedef  int /*<<< orphan*/  i_len ;
typedef  int /*<<< orphan*/  i_argc ;
typedef  scalar_t__ ULONG ;
typedef  int /*<<< orphan*/  HPIPE ;

/* Variables and functions */
 int /*<<< orphan*/  DosClose (int /*<<< orphan*/ ) ; 
 scalar_t__ DosCreateNPipe (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ DosOpen (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DosSetPriority (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DosWaitNPipe (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DosWrite (int /*<<< orphan*/ ,...) ; 
 scalar_t__ ERROR_PIPE_BUSY ; 
 int /*<<< orphan*/  IPCHelperThread ; 
 scalar_t__ IPC_CMD_ENQUEUE ; 
 scalar_t__ IPC_CMD_GO ; 
 int /*<<< orphan*/  NP_ACCESS_DUPLEX ; 
 int NP_READMODE_MESSAGE ; 
 int NP_TYPE_MESSAGE ; 
 int NP_WAIT ; 
 int OPEN_ACCESS_READWRITE ; 
 int /*<<< orphan*/  OPEN_ACTION_OPEN_IF_EXISTS ; 
 int OPEN_FLAGS_FAIL_ON_ERROR ; 
 int OPEN_SHARE_DENYREADWRITE ; 
 int /*<<< orphan*/  PRTYC_REGULAR ; 
 int /*<<< orphan*/  PRTYD_MAXIMUM ; 
 int /*<<< orphan*/  PRTYS_PROCESS ; 
 int /*<<< orphan*/  VLC_IPC_PIPE ; 
 int _beginthread (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int _gettid () ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  hpipeIPC ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msg_Info (int /*<<< orphan*/ *,char*) ; 
 char* strdup (char const* const) ; 
 int strlen (char*) ; 
 scalar_t__ strstr (char const* const,char*) ; 
 int /*<<< orphan*/  system_End () ; 
 int tidIPCFirst ; 
 int tidIPCHelper ; 
 scalar_t__ var_InheritBool (int /*<<< orphan*/ *,char*) ; 
 char* vlc_path2uri (char const* const,int /*<<< orphan*/ *) ; 

void system_Configure( libvlc_int_t *p_this, int i_argc, const char *const ppsz_argv[] )
{
    if( var_InheritBool( p_this, "high-priority" ) )
    {
        if( !DosSetPriority( PRTYS_PROCESS, PRTYC_REGULAR, PRTYD_MAXIMUM, 0 ) )
        {
            msg_Dbg( p_this, "raised process priority" );
        }
        else
        {
            msg_Dbg( p_this, "could not raise process priority" );
        }
    }

    if( var_InheritBool( p_this, "one-instance" )
        || ( var_InheritBool( p_this, "one-instance-when-started-from-file" )
             && var_InheritBool( p_this, "started-from-file" ) ) )
    {
        HPIPE hpipe;
        ULONG ulAction;
        ULONG rc;

        msg_Info( p_this, "one instance mode ENABLED");

        /* Use a named pipe to check if another instance is already running */
        for(;;)
        {
            rc = DosOpen( VLC_IPC_PIPE, &hpipe, &ulAction, 0, 0,
                          OPEN_ACTION_OPEN_IF_EXISTS,
                          OPEN_ACCESS_READWRITE | OPEN_SHARE_DENYREADWRITE |
                          OPEN_FLAGS_FAIL_ON_ERROR,
                          NULL );

            if( rc == ERROR_PIPE_BUSY )
                DosWaitNPipe( VLC_IPC_PIPE, -1 );
            else
                break;
        }

        if( rc )
        {
            rc = DosCreateNPipe( VLC_IPC_PIPE,  &hpipeIPC,
                                 NP_ACCESS_DUPLEX,
                                 NP_WAIT | NP_TYPE_MESSAGE |
                                 NP_READMODE_MESSAGE | 0x01,
                                 32768, 32768, 0 );
            if( rc )
            {
                /* Failed to create a named pipe. Just ignore the option and
                 * go on as normal. */
                msg_Err( p_this, "one instance mode DISABLED "
                         "(a named pipe couldn't be created)" );
                return;
            }

            /* We are the 1st instance. */

            /* Save the tid of the first instance */
            tidIPCFirst = _gettid();

            /* Run the helper thread */
            tidIPCHelper = _beginthread( IPCHelperThread, NULL, 1024 * 1024,
                                         p_this );
            if( tidIPCHelper == -1 )
            {
                msg_Err( p_this, "one instance mode DISABLED "
                         "(IPC helper thread couldn't be created)");

                tidIPCFirst = -1;
            }
        }
        else
        {
            /* Another instance is running */
            ULONG ulCmd = var_InheritBool( p_this, "playlist-enqueue") ?
                              IPC_CMD_ENQUEUE : IPC_CMD_GO;
            ULONG cbActual;

            /* Write a command */
            DosWrite( hpipe, &ulCmd, sizeof( ulCmd ), &cbActual );

            /* We assume that the remaining parameters are filenames
             * and their input options */

            /* Write a count of arguments */
            DosWrite( hpipe, &i_argc, sizeof( i_argc ), &cbActual );

            for( int i_opt = 0; i_opt < i_argc; i_opt++ )
            {
                /* We need to resolve relative paths in this instance */
                char *mrl;
                if( strstr( ppsz_argv[ i_opt ], "://" ))
                    mrl = strdup( ppsz_argv[ i_opt ] );
                else
                    mrl = vlc_path2uri( ppsz_argv[ i_opt ], NULL );

                if( !mrl )
                    mrl = ( char * )ppsz_argv[ i_opt ];

                size_t i_len = strlen( mrl ) + 1;

                /* Write a length of an argument */
                DosWrite( hpipe, &i_len, sizeof( i_len ), &cbActual );

                /* Write an argument */
                DosWrite( hpipe, mrl, i_len, &cbActual );

                if( mrl != ppsz_argv[ i_opt ])
                    free( mrl );
            }

            /* Close a named pipe of a client side */
            DosClose( hpipe );

            /* Bye bye */
            system_End();
            exit( 0 );
        }
    }
}