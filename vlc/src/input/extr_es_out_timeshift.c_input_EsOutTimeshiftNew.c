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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  input_thread_t ;
struct TYPE_6__ {int /*<<< orphan*/ * cbs; } ;
typedef  TYPE_1__ es_out_t ;
struct TYPE_7__ {int b_input_paused; int b_input_paused_source; float input_rate; float input_rate_source; int b_delayed; int i_tmp_size_max; char* psz_tmp_path; TYPE_1__ out; int /*<<< orphan*/  pp_es; int /*<<< orphan*/  i_es; int /*<<< orphan*/ * p_ts; int /*<<< orphan*/  lock; TYPE_1__* p_out; int /*<<< orphan*/ * p_input; } ;
typedef  TYPE_2__ es_out_sys_t ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 char DIR_SEP_CHAR ; 
 void* FromWide (int /*<<< orphan*/ *) ; 
 void* GetTempPath (scalar_t__ const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAB_INIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int __MAX (int const,int) ; 
 int /*<<< orphan*/ * _wgetcwd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  es_out_timeshift_cbs ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 TYPE_2__* malloc (int) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,...) ; 
 char* strdup (char*) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  ts_cmd_add_t ; 
 int /*<<< orphan*/  ts_cmd_control_t ; 
 int /*<<< orphan*/  ts_cmd_del_t ; 
 int /*<<< orphan*/  ts_cmd_send_t ; 
 int /*<<< orphan*/  ts_cmd_t ; 
 int var_CreateGetInteger (int /*<<< orphan*/ *,char*) ; 
 char* var_InheritString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * vlc_alloc (scalar_t__ const,int) ; 
 int /*<<< orphan*/  vlc_mutex_init_recursive (int /*<<< orphan*/ *) ; 

es_out_t *input_EsOutTimeshiftNew( input_thread_t *p_input, es_out_t *p_next_out, float rate )
{
    es_out_sys_t *p_sys = malloc( sizeof(*p_sys) );
    if( !p_sys )
        return NULL;

    p_sys->out.cbs = &es_out_timeshift_cbs;

    /* */
    p_sys->b_input_paused = false;
    p_sys->b_input_paused_source = false;
    p_sys->p_input = p_input;
    p_sys->input_rate = rate;
    p_sys->input_rate_source = rate;

    p_sys->p_out = p_next_out;
    vlc_mutex_init_recursive( &p_sys->lock );

    p_sys->b_delayed = false;
    p_sys->p_ts = NULL;

    TAB_INIT( p_sys->i_es, p_sys->pp_es );

    /* */
    const int i_tmp_size_max = var_CreateGetInteger( p_input, "input-timeshift-granularity" );
    if( i_tmp_size_max < 0 )
        p_sys->i_tmp_size_max = 50*1024*1024;
    else
        p_sys->i_tmp_size_max = __MAX( i_tmp_size_max, 1*1024*1024 );
    msg_Dbg( p_input, "using timeshift granularity of %d MiB",
             (int)p_sys->i_tmp_size_max/(1024*1024) );

    p_sys->psz_tmp_path = var_InheritString( p_input, "input-timeshift-path" );
#if defined (_WIN32) && !VLC_WINSTORE_APP
    if( p_sys->psz_tmp_path == NULL )
    {
        const DWORD count = GetTempPath( 0, NULL );
        if( count > 0 )
        {
            WCHAR *path = vlc_alloc( count + 1, sizeof(WCHAR) );
            if( path != NULL )
            {
                DWORD ret = GetTempPath( count + 1, path );
                if( ret != 0 && ret <= count )
                    p_sys->psz_tmp_path = FromWide( path );
                free( path );
            }
        }
    }
    if( p_sys->psz_tmp_path == NULL )
    {
        wchar_t *wpath = _wgetcwd( NULL, 0 );
        if( wpath != NULL )
        {
            p_sys->psz_tmp_path = FromWide( wpath );
            free( wpath );
        }
    }
    if( p_sys->psz_tmp_path == NULL )
        p_sys->psz_tmp_path = strdup( "C:" );

    if( p_sys->psz_tmp_path != NULL )
    {
        size_t len = strlen( p_sys->psz_tmp_path );

        while( len > 0 && p_sys->psz_tmp_path[len - 1] == DIR_SEP_CHAR )
            len--;

        p_sys->psz_tmp_path[len] = '\0';
    }
#endif
    if( p_sys->psz_tmp_path != NULL )
        msg_Dbg( p_input, "using timeshift path: %s", p_sys->psz_tmp_path );
    else
        msg_Dbg( p_input, "using default timeshift path" );

#if 0
#define S(t) msg_Err( p_input, "SIZEOF("#t")=%d", sizeof(t) )
    S(ts_cmd_t);
    S(ts_cmd_control_t);
    S(ts_cmd_send_t);
    S(ts_cmd_del_t);
    S(ts_cmd_add_t);
#undef S
#endif

    return &p_sys->out;
}