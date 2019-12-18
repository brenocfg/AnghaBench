#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* sys; } ;
typedef  TYPE_1__ vout_window_t ;
struct TYPE_6__ {char* psz_title; int /*<<< orphan*/  hwnd; int /*<<< orphan*/  lock; } ;
typedef  TYPE_2__ vout_window_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  PostMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_VLC_CHANGE_TEXT ; 
 int /*<<< orphan*/  free (char*) ; 
 char* strdup (char const*) ; 
 char* var_InheritString (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void SetTitle(vout_window_t *wnd, const char *title)
{
    vout_window_sys_t *sys = wnd->sys;
    char *psz_title = var_InheritString( wnd, "video-title" );
    if( !psz_title )
        psz_title = strdup( title );
    if( !psz_title )
        return;

    vlc_mutex_lock( &sys->lock );
    free( sys->psz_title );
    sys->psz_title = psz_title;
    vlc_mutex_unlock( &sys->lock );

    PostMessage( sys->hwnd, WM_VLC_CHANGE_TEXT, 0, 0 );
}