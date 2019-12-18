#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  close; int /*<<< orphan*/  control; int /*<<< orphan*/  display; int /*<<< orphan*/  prepare; TYPE_1__* cfg; TYPE_5__* sys; } ;
typedef  TYPE_4__ vout_display_t ;
struct TYPE_14__ {int ulMode; } ;
struct TYPE_19__ {scalar_t__ frame; scalar_t__ client; int /*<<< orphan*/  ack_event; int /*<<< orphan*/  i_result; int /*<<< orphan*/  hab; int /*<<< orphan*/  hmq; scalar_t__ is_mouse_hidden; int /*<<< orphan*/  p_old_frame; TYPE_3__* parent_window; TYPE_10__ kvac; scalar_t__ parent; int /*<<< orphan*/  b_fixt23; } ;
typedef  TYPE_5__ vout_display_sys_t ;
typedef  int /*<<< orphan*/  vout_display_cfg_t ;
typedef  int /*<<< orphan*/  video_format_t ;
struct open_init {int /*<<< orphan*/ * fmtp; int /*<<< orphan*/ * cfg; TYPE_4__* vd; } ;
typedef  int ULONG ;
struct TYPE_16__ {scalar_t__ hwnd; } ;
struct TYPE_17__ {scalar_t__ type; TYPE_2__ handle; } ;
struct TYPE_15__ {TYPE_3__* window; } ;
typedef  int /*<<< orphan*/  QMSG ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  scalar_t__ HWND ;

/* Variables and functions */
 int /*<<< orphan*/  COLOR_KEY ; 
 int CS_MOVENOTIFY ; 
 int CS_SIZEREDRAW ; 
 int /*<<< orphan*/  Close ; 
 int /*<<< orphan*/  CloseDisplay (TYPE_4__*) ; 
 int /*<<< orphan*/  Control ; 
 int /*<<< orphan*/  Display ; 
 int /*<<< orphan*/  DosPostEventSem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int FCF_MINMAX ; 
 int FCF_SIZEBORDER ; 
 int FCF_SYSMENU ; 
 int FCF_TASKLIST ; 
 int FCF_TITLEBAR ; 
 scalar_t__ HWND_DESKTOP ; 
 int KVAM_AUTO ; 
 int KVAM_DIVE ; 
 int KVAM_SNAP ; 
 int KVAM_VMAN ; 
 int KVAM_WO ; 
 int /*<<< orphan*/  MCW_EM ; 
 int /*<<< orphan*/  MorphToPM () ; 
 int /*<<< orphan*/  MyFrameWndProc ; 
 scalar_t__ NULLHANDLE ; 
 scalar_t__ OpenDisplay (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Prepare ; 
 int /*<<< orphan*/  QWL_STYLE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VLC_EGENERIC ; 
 int /*<<< orphan*/  VLC_SUCCESS ; 
 scalar_t__ VOUT_WINDOW_TYPE_HWND ; 
 int /*<<< orphan*/  WC_VLC_KVA ; 
 int WS_CLIPCHILDREN ; 
 int /*<<< orphan*/  WS_VISIBLE ; 
 int /*<<< orphan*/  WinCreateMsgQueue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ WinCreateStdWindow (scalar_t__,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,char*,long,scalar_t__,int,scalar_t__*) ; 
 int /*<<< orphan*/  WinDestroyMsgQueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WinDestroyWindow (scalar_t__) ; 
 int /*<<< orphan*/  WinDispatchMsg (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ WinGetMsg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WinInitialize (int /*<<< orphan*/ ) ; 
 int WinQueryWindowULong (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WinRegisterClass (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  WinSetVisibleRegionNotify (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WinSetWindowPtr (scalar_t__,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  WinSetWindowULong (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WinShowPointer (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WinSubclassWindow (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WinTerminate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WndProc ; 
 int /*<<< orphan*/  _control87 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  kvaCaps (TYPE_10__*) ; 
 int /*<<< orphan*/  kvaDisableScreenSaver () ; 
 int /*<<< orphan*/  kvaDone () ; 
 int /*<<< orphan*/  kvaEnableScreenSaver () ; 
 scalar_t__ kvaInit (int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_4__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Err (TYPE_4__*,char*) ; 
 int /*<<< orphan*/ * psz_video_mode ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  var_CreateGetBool (TYPE_4__*,char*) ; 
 char* var_CreateGetString (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  video_format_ApplyRotation (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void PMThread( void *arg )
{
    struct open_init *init = ( struct open_init * )arg;
    vout_display_t *vd = init->vd;
    vout_display_sys_t * sys = vd->sys;
    const vout_display_cfg_t * cfg = init->cfg;
    video_format_t *fmtp = init->fmtp;
    ULONG i_frame_flags;
    QMSG qm;
    char *psz_mode;
    ULONG i_kva_mode;

    /* */
    video_format_t fmt;
    video_format_ApplyRotation(&fmt, fmtp);

    /* */
    MorphToPM();

    sys->hab = WinInitialize( 0 );
    sys->hmq = WinCreateMsgQueue( sys->hab, 0);

    WinRegisterClass( sys->hab,
                      WC_VLC_KVA,
                      WndProc,
                      CS_SIZEREDRAW | CS_MOVENOTIFY,
                      sizeof( PVOID ));

    sys->b_fixt23 = var_CreateGetBool( vd, "kva-fixt23");

    if( !sys->b_fixt23 && vd->cfg->window->type == VOUT_WINDOW_TYPE_HWND )
        /* If an external window was specified, we'll draw in it. */
        sys->parent_window = vd->cfg->window;

    if( sys->parent_window )
    {
        sys->parent = ( HWND )sys->parent_window->handle.hwnd;

        ULONG i_style = WinQueryWindowULong( sys->parent, QWL_STYLE );
        WinSetWindowULong( sys->parent, QWL_STYLE,
                           i_style | WS_CLIPCHILDREN );

        i_frame_flags = FCF_TITLEBAR;
    }
    else
    {
        sys->parent = HWND_DESKTOP;

        i_frame_flags = FCF_SYSMENU    | FCF_TITLEBAR | FCF_MINMAX |
                        FCF_SIZEBORDER | FCF_TASKLIST;
    }

    sys->frame =
        WinCreateStdWindow( sys->parent,      /* parent window handle */
                            WS_VISIBLE,       /* frame window style */
                            &i_frame_flags,   /* window style */
                            WC_VLC_KVA,       /* class name */
                            "",               /* window title */
                            0L,               /* default client style */
                            NULLHANDLE,       /* resource in exe file */
                            1,                /* frame window id */
                            &sys->client );   /* client window handle */

    if( sys->frame == NULLHANDLE )
    {
        msg_Err( vd, "cannot create a frame window");

        goto exit_frame;
    }

    WinSetWindowPtr( sys->client, 0, vd );

    if( !sys->parent_window )
    {
        WinSetWindowPtr( sys->frame, 0, vd );
        sys->p_old_frame = WinSubclassWindow( sys->frame, MyFrameWndProc );
    }

    psz_mode = var_CreateGetString( vd, "kva-video-mode" );

    i_kva_mode = KVAM_AUTO;
    if( strcmp( psz_mode, "snap" ) == 0 )
        i_kva_mode = KVAM_SNAP;
    else if( strcmp( psz_mode, "wo" ) == 0 )
        i_kva_mode = KVAM_WO;
    else if( strcmp( psz_mode, "vman" ) == 0 )
        i_kva_mode = KVAM_VMAN;
    else if( strcmp( psz_mode, "dive" ) == 0 )
        i_kva_mode = KVAM_DIVE;

    free( psz_mode );

    if( kvaInit( i_kva_mode, sys->client, COLOR_KEY ))
    {
        msg_Err( vd, "cannot initialize KVA");

        goto exit_kva_init;
    }

    kvaCaps( &sys->kvac );

    msg_Dbg( vd, "selected video mode = %s",
             psz_video_mode[ sys->kvac.ulMode - 1 ]);

    if( OpenDisplay( vd, &fmt ) )
    {
        msg_Err( vd, "cannot open display");

        goto exit_open_display;
    }

    kvaDisableScreenSaver();

    /* Setup vout_display now that everything is fine */
    *fmtp       = fmt;

    vd->prepare = Prepare;
    vd->display = Display;
    vd->control = Control;
    vd->close = Close;

    /* Prevent SIG_FPE */
    _control87(MCW_EM, MCW_EM);

    sys->i_result = VLC_SUCCESS;
    DosPostEventSem( sys->ack_event );

    if( !sys->parent_window )
        WinSetVisibleRegionNotify( sys->frame, TRUE );

    while( WinGetMsg( sys->hab, &qm, NULLHANDLE, 0, 0 ))
        WinDispatchMsg( sys->hab, &qm );

    if( !sys->parent_window )
        WinSetVisibleRegionNotify( sys->frame, FALSE );

    kvaEnableScreenSaver();

    CloseDisplay( vd );

    /* fall through */

exit_open_display :
    kvaDone();

exit_kva_init :
    if( !sys->parent_window )
        WinSubclassWindow( sys->frame, sys->p_old_frame );

    WinDestroyWindow( sys->frame );

exit_frame :
    if( sys->is_mouse_hidden )
        WinShowPointer( HWND_DESKTOP, TRUE );

    WinDestroyMsgQueue( sys->hmq );
    WinTerminate( sys->hab );

    sys->i_result = VLC_EGENERIC;
    DosPostEventSem( sys->ack_event );
}