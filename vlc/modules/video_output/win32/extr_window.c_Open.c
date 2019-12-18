#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int has_double_click; } ;
struct TYPE_14__ {int /*<<< orphan*/ * hwnd; } ;
struct TYPE_16__ {TYPE_2__ info; int /*<<< orphan*/ * ops; TYPE_1__ handle; int /*<<< orphan*/  type; TYPE_4__* sys; } ;
typedef  TYPE_3__ vout_window_t ;
struct TYPE_17__ {int is_cursor_hidden; int b_ready; int b_done; int /*<<< orphan*/ * hwnd; int /*<<< orphan*/  lock; int /*<<< orphan*/  wait; int /*<<< orphan*/  thread; scalar_t__ vlc_icon; int /*<<< orphan*/  cursor_arrow; int /*<<< orphan*/  class_main; int /*<<< orphan*/  cursor_empty; int /*<<< orphan*/  hide_timeout; scalar_t__ button_pressed; } ;
typedef  TYPE_4__ vout_window_sys_t ;
typedef  scalar_t__ WNDPROC ;
struct TYPE_18__ {int style; int /*<<< orphan*/  hCursor; int /*<<< orphan*/  lpszClassName; scalar_t__ hIcon; int /*<<< orphan*/  hInstance; scalar_t__ lpfnWndProc; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_5__ WNDCLASS ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  HINSTANCE ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int CS_DBLCLKS ; 
 int CS_OWNDC ; 
 int /*<<< orphan*/  Close (TYPE_3__*) ; 
 int /*<<< orphan*/  DestroyIcon (scalar_t__) ; 
 int /*<<< orphan*/  EmptyCursor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EventThread ; 
 scalar_t__ ExtractIcon (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ GetModuleFileName (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  GetModuleHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDC_ARROW ; 
 int /*<<< orphan*/  LoadCursor (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  RegisterClass (TYPE_5__*) ; 
 int /*<<< orphan*/  TEXT (char*) ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int /*<<< orphan*/  VLC_OBJECT (TYPE_3__*) ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_THREAD_PRIORITY_LOW ; 
 int /*<<< orphan*/  VOUT_WINDOW_TYPE_HWND ; 
 scalar_t__ WinVoutEventProc ; 
 int /*<<< orphan*/  _snwprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_3__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ops ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_InheritInteger (TYPE_3__*,char*) ; 
 scalar_t__ vlc_clone (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_cond_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_4__* vlc_obj_calloc (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int Open(vout_window_t *wnd)
{
    vout_window_sys_t *sys = vlc_obj_calloc(VLC_OBJECT(wnd), 1, sizeof(vout_window_sys_t));
    if (unlikely(sys == NULL))
        return VLC_ENOMEM;

    _snwprintf( sys->class_main, ARRAY_SIZE(sys->class_main),
               TEXT("VLC standalone window %p"), (void *)sys );

    HINSTANCE hInstance = GetModuleHandle(NULL);

    WCHAR app_path[MAX_PATH];
    if( GetModuleFileName( NULL, app_path, MAX_PATH ) )
        sys->vlc_icon = ExtractIcon( hInstance, app_path    , 0 );

    sys->button_pressed = 0;
    sys->is_cursor_hidden = false;
    sys->hide_timeout = var_InheritInteger( wnd, "mouse-hide-timeout" );
    sys->cursor_arrow = LoadCursor(NULL, IDC_ARROW);
    sys->cursor_empty = EmptyCursor(hInstance);

    WNDCLASS wc = { 0 };
    /* Fill in the window class structure */
    wc.style         = CS_OWNDC|CS_DBLCLKS;           /* style: dbl click */
    wc.lpfnWndProc   = (WNDPROC)WinVoutEventProc;        /* event handler */
    wc.hInstance     = hInstance;                             /* instance */
    wc.hIcon         = sys->vlc_icon;            /* load the vlc big icon */
    wc.lpszClassName = sys->class_main;            /* use a special class */
    wc.hCursor       = sys->cursor_arrow;

    /* Register the window class */
    if( !RegisterClass(&wc) )
    {
        if( sys->vlc_icon )
            DestroyIcon( sys->vlc_icon );

        msg_Err( wnd, "RegisterClass FAILED (err=%lu)", GetLastError() );
        return VLC_EGENERIC;
    }
    vlc_mutex_init( &sys->lock );
    vlc_cond_init( &sys->wait );
    sys->b_ready = false;
    sys->b_done = false;

    wnd->sys = sys;
    if( vlc_clone( &sys->thread, EventThread, wnd, VLC_THREAD_PRIORITY_LOW ) )
    {
        Close(wnd);
        return VLC_EGENERIC;
    }

    vlc_mutex_lock( &sys->lock );
    while( !sys->b_ready )
    {
        vlc_cond_wait( &sys->wait, &sys->lock );
    }
    if (sys->hwnd == NULL)
    {
        vlc_mutex_unlock( &sys->lock );
        Close(wnd);
        return VLC_EGENERIC;
    }
    vlc_mutex_unlock( &sys->lock );

    wnd->sys = sys;
    wnd->type = VOUT_WINDOW_TYPE_HWND;
    wnd->handle.hwnd = sys->hwnd;
    wnd->ops = &ops;
    wnd->info.has_double_click = true;
    return VLC_SUCCESS;
}